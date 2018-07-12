#include <noticias/include/infobae.h>

// utiles
#include <utiles/include/FuncionesString.h>
#include <utiles/include/FuncionesSistemaArchivos.h>
#include <utiles/include/Json.h>

// pugixml
#include <pugixml.hpp>

// feed
#include <feed/include/rss.h>

// noticias
#include <noticias/include/config.h>

namespace medios {
    namespace noticias {

infobae::infobae() : portal() {
    std::unordered_map<std::string, std::string> subcategorias;
    for(config_subcategoria config_subcatego : config::infobae.canales[0].subcategorias) {
        subcategorias[config_subcatego.subcategoria] = config_subcatego.recurso_url;
    }
    medios::feed::canal * canal = new medios::feed::rss_infobae(config::infobae.canales[0].link, config::infobae.canales[0].categoria, subcategorias);
    this->canales_portal[canal->seccion()] = canal;
}

infobae::~infobae() {}

//bool infobae::nueva_noticia(const medios::feed::historia & historia, const std::string & seccion) {
//
//    std::string recurso_url = "";
//    this->reconocer_seccion(historia.link(), &recurso_url);
//
//    return this->portal::nueva_noticia(historia, recurso_url);
//}

std::string infobae::web() {
    return "infobae.com";
}

portal * infobae::clon() {
    portal * nuevo_portal = new infobae();
    nuevo_portal->nuevas_noticias(this->noticias_portal);
    return nuevo_portal;
}

bool infobae::extraer_contenido_de_html(const std::string & contenido_html, std::string * contenido) {

    *contenido = contenido_html;
    this->eliminar_elemento_xml(contenido, "div", "<div ");
    this->eliminar_elemento_xml(contenido, "span", "<span ");
    this->eliminar_elemento_xml(contenido, "a", "<a ");
    this->eliminar_etiqueta_xml(contenido, "em");
    this->eliminar_etiqueta_xml(contenido, "img");
    this->eliminar_etiqueta_xml(contenido, "strong");
    this->eliminar_etiqueta_xml(contenido, "em");
    this->eliminar_etiqueta_xml(contenido, "p");
    this->eliminar_etiqueta_xml(contenido, "br");
    this->eliminar_etiqueta_xml(contenido, "caption");
    this->eliminar_etiqueta_xml(contenido, "iframe");

    herramientas::utiles::FuncionesString::eliminarOcurrencias(*contenido, "&nbsp;");
    herramientas::utiles::FuncionesString::eliminarOcurrencias(*contenido, "<br/>");

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
}