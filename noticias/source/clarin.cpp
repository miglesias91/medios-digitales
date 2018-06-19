#include <noticias/include/clarin.h>

// utiles
#include <utiles/include/FuncionesString.h>

// pugixml
#include <pugixml.hpp>

// feed
#include <feed/include/rss.h>

struct simple_walker : pugi::xml_tree_walker {
    virtual bool for_each(pugi::xml_node& node) {

        for (int i = 0; i < depth(); ++i) std::cout << "  "; // indentation

        std::cout << node.type() << ": name='" << node.name() << "', value='" << node.value() << "'\n";

        return true; // continue traversal
    }

};

namespace medios::noticias {

clarin::clarin() : portal() {
    // TODO: hacer que esta config de canales las levante de un json.
    medios::feed::canal * politica = new medios::feed::rss("https://www.clarin.com/rss/politica/", "politica");
    medios::feed::canal * economia = new medios::feed::rss("https://www.clarin.com/rss/economia/", "economia");
    medios::feed::canal * lo_ultimo = new medios::feed::rss("https://www.clarin.com/rss/lo-ultimo/", "lo ultimo");

    this->canales_portal[politica->seccion()] = politica;
    this->canales_portal[economia->seccion()] = economia;
    this->canales_portal[lo_ultimo->seccion()] = lo_ultimo;
}

clarin::~clarin() {}

bool clarin::extraer_contenido_de_html(const std::string & contenido_html, std::string & contenido) {

    size_t primer_comienzo = contenido_html.find("<span itemprop=\"articleBody\">");
    size_t pos_fin_span = contenido_html.find("</span", primer_comienzo);
    size_t tamanio_tag_span = std::string("<span").size();

    size_t comienzo = primer_comienzo + tamanio_tag_span;
    while (pos_fin_span > contenido_html.find("<span", comienzo)) {
        // si entra al if, entonces quiere decir que se abrio otro elemento "span" en el medio
        comienzo = pos_fin_span + tamanio_tag_span;
        pos_fin_span = contenido_html.find("</span", comienzo);  // actualizo la posicion del ultimo span encontrado.
    }

     std::string html_con_texto = contenido_html.substr(primer_comienzo, pos_fin_span + std::string("</span>").size() - primer_comienzo);
     herramientas::utiles::FuncionesString::eliminarOcurrencias(html_con_texto, "<strong>");
     herramientas::utiles::FuncionesString::eliminarOcurrencias(html_con_texto, "</strong>");
     herramientas::utiles::FuncionesString::eliminarOcurrencias(html_con_texto, "<br>");
     herramientas::utiles::FuncionesString::eliminarOcurrencias(html_con_texto, "</br>");

     size_t comienzo_parrafo = html_con_texto.find("<p");
     size_t fin_parrafo = html_con_texto.find("</p");
     size_t tamanio_tag_p = std::string("</p").size();

     while (pos_fin_span > fin_parrafo) {
         std::string parrafo = html_con_texto.substr(comienzo_parrafo + tamanio_tag_p, fin_parrafo - comienzo_parrafo - tamanio_tag_p);

         if (false == parrafo.empty()) {
             contenido += parrafo;
         }

         comienzo_parrafo = html_con_texto.find("<p", fin_parrafo + tamanio_tag_p);
         fin_parrafo = html_con_texto.find("</p", fin_parrafo + tamanio_tag_p);
     }

     if (contenido.empty()) {
         return false;
     }

    return true;
}

}