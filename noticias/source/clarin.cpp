#include <noticias/include/clarin.h>

// utiles
#include <utiles/include/FuncionesString.h>

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

bool clarin::extraer_contenido_de_html(const std::string & contenido_html, std::string * contenido) {

    std::string elemento_span_articulo = "";
    this->extraer_elemento_xml(contenido_html, "span", "<span itemprop=\"articleBody\">", &elemento_span_articulo);
    this->eliminar_etiqueta_xml(&elemento_span_articulo, "strong");
    this->eliminar_etiqueta_xml(&elemento_span_articulo, "br");

    std::vector<std::string> elementos_p;
    this->extraer_elementos_xml(elemento_span_articulo, "p", "<p", &elementos_p);

    if (elementos_p.empty()) {
        return false;
    }

    *contenido = herramientas::utiles::FuncionesString::unir(elementos_p, "", "");

    return true;
}

}