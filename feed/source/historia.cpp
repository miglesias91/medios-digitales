#include <feed/include/historia.h>

// stl
#include <sstream>

namespace medios::feed {

historia::historia() : titulo_historia(""), link_web("") {}

historia::historia(const std::string & titulo, const std::string & link, herramientas::utiles::Fecha fecha, const std::string & string_html) :
titulo_historia(titulo), link_web(link), fecha_creacion(fecha), string_html(string_html) {}

historia::~historia() {}

void historia::titulo(const std::string & titulo) {
    this->titulo_historia = titulo;
}

std::string historia::titulo() const {
    return this->titulo_historia;
}

void historia::link(const std::string & link) {
    this->link_web = link;
}

std::string historia::link() const {
    return this->link_web;
}

void historia::fecha(herramientas::utiles::Fecha fecha) {
    this->fecha_creacion = fecha;
}

herramientas::utiles::Fecha historia::fecha() const {
    return this->fecha_creacion;
}

void historia::html(const std::string & string_html) {
    this->string_html = string_html;
}

std::string historia::html() const {
    return string_html;
}

}