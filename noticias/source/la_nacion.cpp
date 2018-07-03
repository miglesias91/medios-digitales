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
    // TODO: hacer que esta config de canales las levante de un json.
    //medios::feed::canal * politica = new medios::feed::atom("http://contenidos.lanacion.com.ar/herramientas/rss-categoria_id=30", "politica");
    //medios::feed::canal * economia = new medios::feed::atom("http://contenidos.lanacion.com.ar/herramientas/rss-categoria_id=272", "economia");
    //medios::feed::canal * lo_ultimo = new medios::feed::atom("http://contenidos.lanacion.com.ar/herramientas/rss-origen=2", "lo ultimo");

    //this->canales_portal[politica->seccion()] = politica;
    //this->canales_portal[economia->seccion()] = economia;
    //this->canales_portal[lo_ultimo->seccion()] = lo_ultimo;

    for (config_canal config : config::la_nacion.canales) {
        feed::canal * canal = new medios::feed::atom(config.link, config.categoria);
        this->canales_portal[canal->seccion()] = canal;
    }
}

la_nacion::~la_nacion() {}

std::string la_nacion::web() {
    return "la_nacion.com";
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