#pragma once

// stl
#include <string>

// herramientas
#include <utiles/include/Fecha.h>

namespace medios {
    namespace facebook {

class Pagina {
public:
    Pagina(const std::string & nombre = "");
    virtual ~Pagina();

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
};


