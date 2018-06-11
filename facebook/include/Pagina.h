#pragma once

// stl
#include <string>

// herramientas
#include <utiles/include/Fecha.h>

namespace medios::facebook {

class Pagina {
public:
    Pagina(std::string nombre = "");
    virtual ~Pagina();

    // GETTERS

    std::string getNombre();

    herramientas::utiles::Fecha getFechaUltimaPublicacionAnalizada();

    // SETTERS

    void setNombre(std::string nombre);

    void setFechaUltimaPublicacionAnalizada(herramientas::utiles::Fecha fecha_ultima_publicacion_analizada);

    // METODOS

    // CONSULTAS

private:

    // ATRIBUTOS

    std::string nombre;

    herramientas::utiles::Fecha fecha_ultima_publicacion_analizada;
};

};


