#include <noticias/include/clarin.h>

// pugixml
#include <pugixml.hpp>

// feed
#include <feed/include/rss.h>

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
    pugi::xml_document html;
    html.load_string(contenido_html.c_str());

    unsigned int pos = contenido_html.find("articleBody");

     std::string prueba = contenido_html.substr(pos, 50);
    //for (pugi::xml_node parrafo : t.nodo_con_parrafos.children("p")) {

    //    std::string p = parrafo.text().as_string();
    //}

    return true;
}

}