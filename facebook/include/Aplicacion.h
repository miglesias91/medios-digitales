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
    std::string id() const;

    // la clave privada del consumidor_api hace las veces de la clave privada de la app.
    std::string clave_privada() const;

    // SETTERS

    // METODOS

    static bool parsear(herramientas::utiles::Json * json_publicacion, Publicacion * publicacion);

    // se almacena memoria para las publicaciones pero no se libera, entonces deben ser ELIMINADAS luego de ser usadas.
    //std::vector<Publicacion*> leer(Pagina * pagina, unsigned int cantidad_de_publicaciones = 100) const;

    // se almacena memoria para las publicaciones pero no se libera, entonces deben ser ELIMINADAS luego de ser usadas.
    std::vector<Publicacion*> leer(Pagina * pagina,
        const herramientas::utiles::Fecha & desde = herramientas::utiles::Fecha(0, 0, 0),
        const herramientas::utiles::Fecha & hasta = herramientas::utiles::Fecha::getFechaActual(),
        const uint32_t & cantidad_de_publicaciones = 100) const;

private:

    medios::facebook::consumidor_api * consumidor_api;
};

};