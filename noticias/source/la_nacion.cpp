#include <noticias/include/la_nacion.h>

// utiles
#include <utiles/include/FuncionesString.h>

// pugixml
#include <pugixml.hpp>

// feed
#include <feed/include/atom.h>

// noticias
#include <noticias/include/config.h>

namespace medios {
    namespace noticias {

la_nacion::la_nacion() : portal() {
    for (config_canal config : config::la_nacion.canales) {
        std::unordered_map<std::string, std::string> subcategorias;
        for(config_subcategoria config_subcatego : config.subcategorias) {
            subcategorias[config_subcatego.subcategoria] = config_subcatego.recurso_url;
        }
        feed::canal * canal = new medios::feed::atom(config.link, config.categoria, subcategorias);
        this->canales_portal[canal->seccion()] = canal;
    }
}

la_nacion::~la_nacion() {}

std::string la_nacion::web() {
    return config::la_nacion.web;
}

portal * la_nacion::clon() {
    portal * nuevo_portal = new la_nacion();
    nuevo_portal->nuevas_noticias(this->noticias_portal);
    return nuevo_portal;
}

bool la_nacion::extraer_contenido_de_html(const std::string & contenido_html, std::string * contenido) {
    
    std::string elemento_section_cuerpo = "";
    this->extraer_elemento_xml(contenido_html, "section", "<section id=\"cuerpo\" data-module=\"nota-cuerpo\">", &elemento_section_cuerpo);
    this->eliminar_elemento_xml(&elemento_section_cuerpo, "figure", "<figure");
    this->eliminar_elemento_xml(&elemento_section_cuerpo, "div", "<div class=\"barra\">");
    this->eliminar_elemento_xml(&elemento_section_cuerpo, "div", "<div class=\"temas\">");
    this->eliminar_elemento_xml(&elemento_section_cuerpo, "div", "<div class=\"fin-cuerpo\">");
    this->eliminar_etiqueta_xml(&elemento_section_cuerpo, "a");
    this->eliminar_etiqueta_xml(&elemento_section_cuerpo, "!--");

    herramientas::utiles::FuncionesString::eliminarOcurrencias(elemento_section_cuerpo, "&nbsp;");

    pugi::xml_document xml_nota;
    xml_nota.load_string(elemento_section_cuerpo.c_str());

    for (pugi::xml_node parrafo : xml_nota.child("section").children("p")) {
        std::string texto = parrafo.text().as_string();
        *contenido += texto;
    }

    herramientas::utiles::FuncionesString::eliminarOcurrencias(*contenido, "\n");
    herramientas::utiles::FuncionesString::eliminarEspaciosRedundantes(*contenido);

    return true;
}

    }
}