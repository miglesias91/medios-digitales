#include <facebook/include/Pagina.h>

using namespace medios::facebook;

namespace medios::facebook {

Pagina::Pagina(std::string nombre) : nombre(nombre), fecha_ultima_publicacion_analizada(0, 0, 0) {}

Pagina::~Pagina() {}

// GETTERS

std::string Pagina::getNombre() {
    return this->nombre;
}

herramientas::utiles::Fecha Pagina::getFechaUltimaPublicacionAnalizada() {
    return this->fecha_ultima_publicacion_analizada;
}

// SETTERS

void Pagina::setNombre(std::string nombre) {
    this->nombre = nombre;
}

void Pagina::setFechaUltimaPublicacionAnalizada(herramientas::utiles::Fecha fecha_ultima_publicacion_analizada) {
    this->fecha_ultima_publicacion_analizada = fecha_ultima_publicacion_analizada;
}

// METODOS

// CONSULTAS
}