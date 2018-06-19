#include <noticias/include/la_nacion.h>

// utiles
#include <utiles/include/FuncionesString.h>

// pugixml
#include <pugixml.hpp>

// feed
#include <feed/include/atom.h>

namespace medios::noticias {

la_nacion::la_nacion() : portal() {
    // TODO: hacer que esta config de canales las levante de un json.
    medios::feed::canal * politica = new medios::feed::atom("http://contenidos.lanacion.com.ar/herramientas/rss-categoria_id=30", "politica");
    medios::feed::canal * economia = new medios::feed::atom("http://contenidos.lanacion.com.ar/herramientas/rss-categoria_id=272", "economia");
    medios::feed::canal * lo_ultimo = new medios::feed::atom("http://contenidos.lanacion.com.ar/herramientas/rss-origen=2", "lo ultimo");

    this->canales_portal[politica->seccion()] = politica;
    this->canales_portal[economia->seccion()] = economia;
    this->canales_portal[lo_ultimo->seccion()] = lo_ultimo;
}

la_nacion::~la_nacion() {}

bool la_nacion::extraer_contenido_de_html(const std::string & contenido_html, std::string & contenido) {
    
    std::string elemento_section_cuerpo = "";
    this->extraer_elemento_xml(contenido_html, "section", "<section id=\"cuerpo\" data-module=\"nota-cuerpo\">", elemento_section_cuerpo);
    this->eliminar_elemento_xml(elemento_section_cuerpo, "figure", "<figure");
    this->eliminar_elemento_xml(elemento_section_cuerpo, "div", "<div class=\"barra\">");
    this->eliminar_elemento_xml(elemento_section_cuerpo, "div", "<div class=\"temas\">");
    this->eliminar_elemento_xml(elemento_section_cuerpo, "div", "<div class=\"fin-cuerpo\">");
    this->eliminar_etiqueta_xml(elemento_section_cuerpo, "a");
    this->eliminar_etiqueta_xml(elemento_section_cuerpo, "!--");

    pugi::xml_document xml_nota;
    xml_nota.load_string(elemento_section_cuerpo.c_str());

    for (pugi::xml_node parrafo : xml_nota.child("section").children("p")) {
        std::string texto = parrafo.text().as_string();
        contenido += texto;
    }

    herramientas::utiles::FuncionesString::eliminarOcurrencias(contenido, "\n");
    herramientas::utiles::FuncionesString::eliminarEspaciosRedundantes(contenido);

    return true;
}

}