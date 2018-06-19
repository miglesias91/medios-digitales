#include <noticias/include/la_nacion.h>

// utiles
#include <utiles/include/FuncionesString.h>

// pugixml
#include <pugixml.hpp>

// feed
#include <feed/include/atom.h>

struct simple_walker : pugi::xml_tree_walker
{
    virtual bool for_each(pugi::xml_node& node)
    {
        for (int i = 0; i < depth(); ++i) std::cout << "  "; // indentation

        std::cout << node.type() << ": name='" << node.name() << "', value='" << node.value() << "'\n";

        return true; // continue traversal
    }
};

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

    // ELIMINAR ETIQUETAS <a

    pugi::xml_document xml_nota;
    xml_nota.load_string(elemento_section_cuerpo.c_str());

    simple_walker w;
    xml_nota.traverse(w);

    for (pugi::xml_node item : xml_nota.child("section").children("p")) {
        std::string t = item.text().as_string();
    }
    //size_t comienzo_parrafo = html_con_texto.find("<p");
    //size_t fin_parrafo = html_con_texto.find("</p");
    //size_t tamanio_tag_p = std::string("</p").size();

    //while (pos_fin_span > fin_parrafo) {
    //    std::string parrafo = html_con_texto.substr(comienzo_parrafo + tamanio_tag_p, fin_parrafo - comienzo_parrafo - tamanio_tag_p);

    //    if (false == parrafo.empty()) {
    //        contenido += parrafo;
    //    }

    //    comienzo_parrafo = html_con_texto.find("<p", fin_parrafo + tamanio_tag_p);
    //    fin_parrafo = html_con_texto.find("</p", fin_parrafo + tamanio_tag_p);
    //}

    //if (contenido.empty()) {
    //    return false;
    //}

    return true;
}

}