#pragma once

// herramientas
#include <utiles/include/IContieneJson.h>
#include <utiles/include/Fecha.h>

namespace medios {
    namespace facebook {

class Publicacion {
public:

    Publicacion();
    Publicacion(const uintmax_t & id_publicacion, const herramientas::utiles::Fecha & fecha_creacion, const std::string & texto, const uintmax_t & id_pagina);
	virtual ~Publicacion();

    // GETTERS

    unsigned long long int getIdPublicacion();

    unsigned long long int getIdPagina();

    herramientas::utiles::Fecha getFechaCreacion();

    std::string getTextoPublicacion();

    // SETTERS

    void setIdPublicacion(const uintmax_t & id_publicacion);

    void setIdPagina(const uintmax_t & id_pagina);

    void setFechaCreacion(const herramientas::utiles::Fecha & fecha_creacion);

    void setTextoPublicacion(const std::string & texto_publicacion);

    // METODOS

    // CONSULTAS

    // OPERADORES

private:

    // METODOS PRIVADOS

    herramientas::utiles::Fecha parsearFechaEnFormatoFacebook(std::string fecha_formato_facebook);

    // ATRIBUTOS

    uintmax_t id_publicacion, id_pagina;

    herramientas::utiles::Fecha fecha_creacion;

    // esta en formato UTF8 xq obtiene el valor del Json (rapidjson) que contiene.
    // (ir al test 'GettersYSettersCodificaciones' de 'herramientas_desarrollo' para ver como funciona.
    std::string texto_publicacion;
};

    };
};
