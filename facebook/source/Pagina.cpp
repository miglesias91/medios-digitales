#include <facebook/include/Pagina.h>

namespace medios {
    namespace facebook {

Pagina::Pagina(const std::string & nombre) : nombre(nombre) {}

Pagina::~Pagina() {}

// GETTERS

std::string Pagina::getNombre() {
    return this->nombre;
}

// SETTERS

void Pagina::setNombre(std::string nombre) {
    this->nombre = nombre;
}

// METODOS

// CONSULTAS
    }
}