#include <feed/include/canal.h>

namespace medios::feed {

canal::canal(const std::string & string_uri, const std::string & seccion_canal) :
    peticion_activa(false),
    uri(utility::conversions::to_string_t(string_uri)),
    seccion_canal(seccion_canal),
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

    return this->parsear(rta.extract_utf8string().get(), historias, desde, hasta);
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

    return this->parsear(this->respuesta.extract_utf8string().get(), historias, desde, hasta);
}

std::string canal::seccion() const {
    return this->seccion_canal;
}

bool canal::parsear(const std::string & contenido_xml, std::vector<historia*> & historias,
    const herramientas::utiles::Fecha & desde, const herramientas::utiles::Fecha & hasta) {
    pugi::xml_document xml_feed;
    pugi::xml_parse_result resultado = xml_feed.load_string(contenido_xml.c_str());

    uint32_t cantidad_total_de_historias = 0;
    uint32_t cantidad_de_historias_descargadas = 0;
    for (pugi::xml_node item : this->historias_xml(xml_feed)) {

        historia * nueva = new historia();
        this->parsear_historia(item, nueva);

        if (desde <= nueva->fecha() && nueva->fecha() <= hasta) {
            if (this->descargar_y_guardar_historia(nueva, historias, cantidad_de_historias_descargadas)) {
                cantidad_total_de_historias++;
            }
        }
        else {
            delete nueva;
        }
    }

    while (cantidad_de_historias_descargadas != cantidad_total_de_historias) {
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }

    return true;
}

bool canal::descargar_y_guardar_historia(historia * nueva, std::vector<historia*> & historias, uint32_t & cantidad_de_historias_descargadas) {

    if (false == web::uri::validate(utility::conversions::to_string_t(nueva->link()))) {
        delete nueva;
        return false;
    }

    web::uri uri_historia(utility::conversions::to_string_t(nueva->link()));
    web::http::client::http_client cliente_historia(uri_historia.scheme() + utility::conversions::to_string_t("://") + uri_historia.host());

    cliente_historia.request(web::http::methods::GET, uri_historia.path()).then([nueva, &historias, &cantidad_de_historias_descargadas](pplx::task<web::http::http_response> tarea) {
        try {
            std::cout << "extrayendo html" << std::endl;

            std::string string_html = tarea.get().extract_utf8string().get();

            std::cout << "cargando historia" << std::endl;
            nueva->html(string_html);
            historias.push_back(nueva);
            
            std::cout << "historias descargadas: " << cantidad_de_historias_descargadas << std::endl;
        }
        catch (const std::exception & e) {
            delete nueva;
            std::cout << "error: " << e.what() << std::endl;
        }
        cantidad_de_historias_descargadas++;
    });

    return true;
}

}