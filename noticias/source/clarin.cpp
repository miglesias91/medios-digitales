#include <noticias/include/clarin.h>

// utiles
#include <utiles/include/FuncionesString.h>

// pugixml
#include <pugixml.hpp>

// utiles
#include <utiles/include/FuncionesString.h>
#include <utiles/include/FuncionesSistemaArchivos.h>
#include <utiles/include/Json.h>

// feed
#include <feed/include/rss.h>

// noticias
#include <noticias/include/config.h>

namespace medios { namespace noticias {

clarin::clarin() : portal() {
    for (config_canal config : config::clarin.canales) {
        std::unordered_map<std::string, std::string> subcategorias;
        for(config_subcategoria config_subcatego : config.subcategorias) {
            subcategorias[config_subcatego.subcategoria] = config_subcatego.recurso_url;
        }
        feed::canal * canal = new medios::feed::rss(config.link, config.categoria, subcategorias);
        this->canales_portal[canal->seccion()] = canal;
    }
}

clarin::~clarin() {}

std::string clarin::web() {
    return config::clarin.web;
}

portal * clarin::clon() {
    portal * nuevo_portal = new clarin();
    nuevo_portal->nuevas_noticias(this->noticias_portal);
    return nuevo_portal;
}

bool clarin::extraer_contenido_de_html(const std::string & contenido_html, std::string * contenido) {

    std::string elemento_nota = "";
    this->extraer_elemento_xml(contenido_html, "div", "<div class=\"body-nota", &elemento_nota);
    this->eliminar_etiqueta_xml(&elemento_nota, "strong");
    this->eliminar_etiqueta_xml(&elemento_nota, "br");
    this->eliminar_etiqueta_xml(&elemento_nota, "a");
    this->eliminar_etiqueta_xml(&elemento_nota, "em");
    herramientas::utiles::FuncionesString::eliminarOcurrencias(elemento_nota, "&nbsp;");

    std::vector<std::string> elementos_p;
    this->extraer_elementos_xml(elemento_nota, "p", "<p", &elementos_p);

    if (elementos_p.empty()) {
        return false;
    }

    *contenido = herramientas::utiles::FuncionesString::unir(elementos_p, "", "");

    return true;
}

}
}