#include <feed/include/atom.h>

// stl
#include <algorithm>
#include <execution>

// pugixml
#include <pugixml.hpp>

namespace medios {
    namespace feed {

atom::atom(const std::string & string_uri, const std::string & seccion) : canal(string_uri, seccion) {}

atom::~atom() {}

pugi::xml_object_range<pugi::xml_named_node_iterator> atom::historias_xml(const pugi::xml_document & xml_feed) {
    return xml_feed.child("feed").children("entry");
}

bool atom::parsear_historia(const pugi::xml_node & xml_historia, historia * histo) {
    std::string titulo = xml_historia.child_value("title");
    std::string string_fecha = xml_historia.child_value("updated");
    std::string link = xml_historia.child_value("id");

    herramientas::utiles::Fecha fecha;
    herramientas::utiles::Fecha::parsear(string_fecha, "%Y-%m-%dT%H:%M:%S", &fecha);

    histo->titulo(titulo);
    histo->fecha(fecha);
    histo->link(link);

    return true;
}

    }
}