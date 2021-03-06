#include <feed/include/canal.h>

// cpprest

namespace medios {
    namespace feed {

canal::canal(const std::string & string_uri, const std::string & seccion_canal, const std::unordered_map<std::string, std::string> & subcategorias) :
    peticion_activa(false),
    uri(utility::conversions::to_string_t(string_uri)),
    seccion_canal(seccion_canal),
    descripciones_subcategorias(subcategorias),
    cliente_canal(uri.scheme() + utility::conversions::to_string_t("://") + uri.host()) {}

canal::~canal() {}

bool canal::historias_ya(std::vector<historia*> & historias, const herramientas::utiles::Fecha & desde, const herramientas::utiles::Fecha & hasta) {

    web::http::http_response rta;
    if (this->peticion_activa) {
        this->tarea_peticion.wait();
        rta = this->tarea_peticion.get();
    }
    else {
        rta = this->cliente_canal.request(web::http::methods::GET, this->uri.path()).get();
    }

    std::vector<unsigned char> extraccion = rta.extract_vector().get();
    return this->parsear(std::string(extraccion.begin(), extraccion.end()), historias, desde, hasta);
}

bool canal::pedir_historias() {

    if (this->peticion_activa) {
        return false;
    }

    this->peticion_activa = true;

    this->tarea_peticion = this->cliente_canal.request(web::http::methods::GET, this->uri.path());
    this->tarea_peticion.then([this](pplx::task<web::http::http_response> tarea) {
        this->peticion_activa = false;
    });
    return true;
}

bool canal::historias(std::vector<historia*> & historias, const herramientas::utiles::Fecha & desde, const herramientas::utiles::Fecha & hasta) {

    if (this->peticion_activa) {
        return false;
    }

    std::vector<unsigned char> extraccion = this->respuesta.extract_vector().get();
    return this->parsear(std::string(extraccion.begin(), extraccion.end()), historias, desde, hasta);
}

std::string canal::seccion() const {
    return this->seccion_canal;
}

std::unordered_map<std::string, std::string> canal::subcategorias() const {
    return this->descripciones_subcategorias;
}

bool canal::parsear(const std::string & contenido_xml, std::vector<historia*> & historias,
    const herramientas::utiles::Fecha & desde, const herramientas::utiles::Fecha & hasta) {
    pugi::xml_document xml_feed;
    pugi::xml_parse_result resultado = xml_feed.load_string(contenido_xml.c_str());

    uint32_t cantidad_total_de_historias = 0;
    uint32_t cantidad_de_historias_descargadas = 0;
    uint32_t cantidad_de_historias_fallidas = 0;
    for (pugi::xml_node item : this->historias_xml(xml_feed)) {

        historia * nueva = new historia();
        if (false == this->parsear_historia(item, nueva)) {
            delete nueva;
            continue;
        }

        if (desde <= nueva->fecha() && nueva->fecha() <= hasta) {
            if (this->descargar_y_guardar_historia(nueva, historias, cantidad_de_historias_descargadas, cantidad_de_historias_fallidas)) {
                cantidad_total_de_historias++;
            }
        }
        else {
            delete nueva;
        }

        if (cantidad_total_de_historias >= (cantidad_de_historias_descargadas + cantidad_de_historias_fallidas + 25)) {  // si hay en espera mas de 25 descargas, entonces
            while ((cantidad_de_historias_descargadas + cantidad_de_historias_fallidas) != cantidad_total_de_historias) {  // espero a que se hayan procesado las 20 descargas.
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
            }
        }

        //if (cantidad_total_de_historias >= 40) break;
    }

    while ((cantidad_de_historias_descargadas + cantidad_de_historias_fallidas) != cantidad_total_de_historias) {
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }

    return true;
}

bool canal::descargar_y_guardar_historia(historia * nueva, std::vector<historia*> & historias, uint32_t & cantidad_de_historias_descargadas, uint32_t & cantidad_de_historias_fallidas) {

    if (false == web::uri::validate(utility::conversions::to_string_t(nueva->link()))) {
        delete nueva;
        return false;
    }

    web::uri uri_historia(utility::conversions::to_string_t(nueva->link()));
    web::http::client::http_client cliente_historia(uri_historia.scheme() + utility::conversions::to_string_t("://") + uri_historia.host());

    cliente_historia.request(web::http::methods::GET, uri_historia.path()).then([nueva, &historias, &cantidad_de_historias_descargadas, &cantidad_de_historias_fallidas](pplx::task<web::http::http_response> tarea) {
        try {
            std::string string_html = tarea.get().extract_utf8string().get();

            nueva->html(string_html);
            historias.push_back(nueva);
            cantidad_de_historias_descargadas++;
        }
        catch (const std::exception & e) {
            delete nueva;
            std::cout << "error: " << e.what() << std::endl;
            cantidad_de_historias_fallidas++;
        }
    });

    return true;
}

}}