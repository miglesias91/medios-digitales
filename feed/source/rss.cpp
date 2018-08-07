#include <feed/include/rss.h>

// stl
#include <algorithm>

// pugixml
#include <pugixml.hpp>

namespace medios {
    namespace feed {

rss::rss(const std::string & string_uri, const std::string & seccion, const std::unordered_map<std::string, std::string> & subcategorias) : canal(string_uri, seccion, subcategorias) {}

rss::~rss() {}

pugi::xml_object_range<pugi::xml_named_node_iterator> rss::historias_xml(const pugi::xml_document & xml_feed) {
    return xml_feed.child("rss").child("channel").children("item");
}

bool rss::parsear_historia(const pugi::xml_node & xml_historia, historia * histo) {
    std::string titulo = xml_historia.child_value("title");
    std::string string_fecha = xml_historia.child_value("pubDate");
    std::string link = xml_historia.child_value("link");
    std::string contenido = xml_historia.child_value("content:encoded");

    herramientas::utiles::Fecha fecha;
    herramientas::utiles::Fecha::parsear(string_fecha, "%a, %d %b %Y %H:%M:%S", &fecha);

    histo->titulo(titulo);
    histo->fecha(fecha);
    histo->link(link);
    histo->contenido(contenido);
    histo->seccion(this->seccion());

    return true;
}

bool rss::extraer_respuesta(const web::http::http_response & rta, std::string * contenido_respuesta) {
    //std::vector<unsigned char> extraccion = rta.extract_vector().get();


    //std::string a(extraccion.begin(), extraccion.end());


    *contenido_respuesta = rta.extract_utf8string().get();
    return true;
}

    }
}