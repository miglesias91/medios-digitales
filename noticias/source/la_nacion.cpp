#include <noticias/include/la_nacion.h>

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
    pugi::xml_document html;
    html.load_string(contenido_html.c_str());

    return true;
}

}