#include <noticias/include/infobae.h>

// utiles
#include <utiles/include/FuncionesString.h>

// pugixml
#include <pugixml.hpp>

// feed
#include <feed/include/rss.h>

namespace medios::noticias {

infobae::infobae() : portal() {
    // TODO: hacer que esta config de canales las levante de un json.
    medios::feed::canal * lo_ultimo = new medios::feed::rss_infobae("https://www.infobae.com/feeds/rss/", "lo ultimo");

    this->canales_portal[lo_ultimo->seccion()] = lo_ultimo;
}

infobae::~infobae() {}

bool infobae::nueva_noticia(const medios::feed::historia & historia, const std::string & seccion) {

    std::string seccion_de_url = "";
    this->reconocer_seccion(historia.link(), &seccion_de_url);

    return this->portal::nueva_noticia(historia, seccion_de_url);
}

bool infobae::extraer_contenido_de_html(const std::string & contenido_html, std::string * contenido) {

    *contenido = contenido_html;
    this->eliminar_elemento_xml(contenido, "div", "<div ");
    this->eliminar_elemento_xml(contenido, "span", "<span ");
    this->eliminar_elemento_xml(contenido, "a", "<a ");
    this->eliminar_etiqueta_xml(contenido, "img");
    this->eliminar_etiqueta_xml(contenido, "strong");
    this->eliminar_etiqueta_xml(contenido, "em");
    this->eliminar_etiqueta_xml(contenido, "p");

    herramientas::utiles::FuncionesString::eliminarEspaciosRedundantes(*contenido);

    return true;
}

bool infobae::reconocer_seccion(const std::string & string_url, std::string * seccion) {

    web::uri url(utility::conversions::to_string_t(string_url));

    std::string path = utility::conversions::to_utf8string(url.path());

    std::vector<std::string> recursos = herramientas::utiles::FuncionesString::separar(path, "/");
    recursos.erase(recursos.begin());

    if ("america" == recursos[0]) {
        *seccion = recursos[1];
    }
    else {
        *seccion = recursos[0];
    }

    if (herramientas::utiles::FuncionesString::empiezaCon(*seccion, "deportes")) {
        *seccion = "deportes";
    }

    return true;
}

}