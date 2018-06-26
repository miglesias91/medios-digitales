#pragma once

// stl
#include <string>

namespace medios::twitter {

class Cuenta {
public:
    Cuenta(std::string nombre = "");
    virtual ~Cuenta();

    // GETTERS

    std::string getNombre();

    // SETTERS

    void setNombre(std::string nombre);

    // METODOS

    // CONSULTAS

private:

    // ATRIBUTOS

    std::string nombre;
};

};