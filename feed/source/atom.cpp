#include <feed/include/atom.h>

// stl
#include <algorithm>
#include <codecvt>

// pugixml
#include <pugixml.hpp>

// utiles
#include <utiles/include/FuncionesString.h>

namespace medios {
    namespace feed {

atom::atom(const std::string & string_uri, const std::string & seccion) : canal(string_uri, seccion) {}

atom::~atom() {}

pugi::xml_object_range<pugi::xml_named_node_iterator> atom::historias_xml(const pugi::xml_document & xml_feed) {
    return xml_feed.child("feed").children("entry");
}

bool atom::parsear_historia(const pugi::xml_node & xml_historia, historia * histo) {
    std::string titulo = xml_historia.child("title").text().as_string();
    std::string string_fecha = xml_historia.child_value("updated");
    std::string link = xml_historia.child_value("id");

    herramientas::utiles::Fecha fecha;
    herramientas::utiles::Fecha::parsear(string_fecha, "%Y-%m-%dT%H:%M:%S", &fecha);

    histo->titulo(titulo);
    histo->fecha(fecha);
    histo->link(link);

    return true;
}

bool atom::extraer_respuesta(const web::http::http_response & rta, std::string * contenido_respuesta) {
    std::vector<unsigned char> extraccion = rta.extract_vector().get();

    *contenido_respuesta = std::string(extraccion.begin(), extraccion.end());

    return true;
}

    }
}