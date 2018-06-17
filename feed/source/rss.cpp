#include <feed/include/rss.h>

// stl
#include <algorithm>
#include <execution>

// pugixml
#include <pugixml.hpp>

namespace medios::feed {

rss::rss(const std::string & string_uri, const std::string & seccion) : canal(string_uri, seccion) {}

rss::~rss() {}

pugi::xml_object_range<pugi::xml_named_node_iterator> rss::historias_xml(const pugi::xml_document & xml_feed) {
    return xml_feed.child("rss").child("channel").children("item");
}

bool rss::parsear_historia(const pugi::xml_node & xml_historia, historia * histo) {
    std::string titulo = xml_historia.child_value("title");
    std::string string_fecha = xml_historia.child_value("pubDate");
    std::string link = xml_historia.child_value("link");

    herramientas::utiles::Fecha fecha;

    histo->titulo(titulo);
    histo->fecha(fecha);
    histo->link(link);

    return true;
}

}