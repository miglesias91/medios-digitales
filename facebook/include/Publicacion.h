#pragma once

// herramientas
#include <utiles/include/IContieneJson.h>
#include <utiles/include/Fecha.h>

namespace medios::facebook {

class Publicacion {
public:

    Publicacion();
	virtual ~Publicacion();

    // GETTERS

    unsigned long long int getIdPublicacion();

    unsigned long long int getIdPagina();

    herramientas::utiles::Fecha getFechaCreacion();

    std::string getTextoPublicacion();

    // SETTERS

    void setIdPublicacion(unsigned long long int id_publicacion);

    void setIdPagina(unsigned long long int id_pagina);

    void setFechaCreacion(herramientas::utiles::Fecha fecha_creacion);

    void setTextoPublicacion(std::string texto_tweet);

    // METODOS

    // CONSULTAS

    // OPERADORES

private:

    // METODOS PRIVADOS

    herramientas::utiles::Fecha parsearFechaEnFormatoFacebook(std::string fecha_formato_facebook);

    // ATRIBUTOS

    unsigned long long int id_publicacion;

    unsigned long long int id_pagina;

    herramientas::utiles::Fecha fecha_creacion;

    // esta en formato UTF8 xq obtiene el valor del Json (rapidjson) que contiene.
    // (ir al test 'GettersYSettersCodificaciones' de 'herramientas_desarrollo' para ver como funciona.
    std::string texto_publicacion;
};

};
