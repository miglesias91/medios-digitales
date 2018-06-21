#pragma once

// herramientas
#include <utiles/include/Fecha.h>

// twitter
#include <facebook/include/consumidor_api.h>
#include <facebook/include/Pagina.h>
#include <facebook/include/Publicacion.h>

namespace medios::facebook {

class aplicacion {
public:
    aplicacion(medios::facebook::consumidor_api * consumidor_api = NULL);
    virtual ~aplicacion();

    // GETTERS

    // la clave publica del consumidor_api hace las veces de id publico de la app.
    std::string id();

    // la clave privada del consumidor_api hace las veces de la clave privada de la app.
    std::string clave_privada();

    // SETTERS

    // METODOS

    // se almacena memoria para las publicaciones pero no se libera, entonces deben ser ELIMINADAS luego de ser usadas.
    std::vector<Publicacion*> leer(Pagina * cuenta, unsigned int cantidad_de_publicaciones = 100);

    // se almacena memoria para las publicaciones pero no se libera, entonces deben ser ELIMINADAS luego de ser usadas.
    std::vector<Publicacion*> leer(Pagina * cuenta, herramientas::utiles::Fecha desde, herramientas::utiles::Fecha hasta, unsigned int cantidad_de_publicaciones = 100);

private:

    medios::facebook::consumidor_api * consumidor_api;
};

};