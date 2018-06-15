#include <feed/include/historia.h>

// stl
#include <sstream>

namespace medios::feed {

historia::historia() : titulo_historia(""), link_web("") {}

historia::historia(std::string titulo, std::string link, herramientas::utiles::Fecha fecha, std::string string_html) :
titulo_historia(titulo), link_web(link), fecha_creacion(fecha), string_html(string_html) {}

historia::~historia() {}

void historia::titulo(std::string titulo) {
    this->titulo_historia = titulo;
}

std::string historia::titulo() {
    return this->titulo_historia;
}

void historia::link(std::string link) {
    this->link_web = link;
}

std::string historia::link() {
    return this->link_web;
}

void historia::fecha(herramientas::utiles::Fecha fecha) {
    this->fecha_creacion = fecha;
}

herramientas::utiles::Fecha historia::fecha() {
    return this->fecha_creacion;
}

void historia::html(std::string string_html) {
    this->string_html = string_html;
}

std::string historia::html() {
    return string_html;
}

}