#include <twitter/include/Cuenta.h>

namespace medios {
    namespace twitter {

Cuenta::Cuenta(std::string nombre) : nombre(nombre) {}

Cuenta::~Cuenta() {}

// GETTERS

std::string Cuenta::getNombre() {
    return this->nombre;
}

// SETTERS

void Cuenta::setNombre(std::string nombre) {
    this->nombre = nombre;
}

// METODOS

// CONSULTAS

    }
}