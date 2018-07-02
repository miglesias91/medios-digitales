#include <feed/include/rss.h>

// stl
#include <algorithm>
#include <execution>

// pugixml
#include <pugixml.hpp>

namespace medios {
    namespace feed {

rss::rss(const std::string & string_uri, const std::string & seccion) : canal(string_uri, seccion) {}

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

    return true;
}

    }
}