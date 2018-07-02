#include <facebook/include/Publicacion.h>

// stl
#include <chrono>
#include <iomanip>
#include <sstream>
#include <iostream>

// herramientas
#include <utiles/include/Conversiones.h>
#include <utiles/include/FuncionesString.h>

namespace medios {
    namespace facebook {

Publicacion::Publicacion() {
}

Publicacion::Publicacion(const uintmax_t & id_publicacion, const herramientas::utiles::Fecha & fecha_creacion, const std::string & texto_publicacion, const uintmax_t & id_pagina)
: id_publicacion(id_publicacion), fecha_creacion(fecha_creacion), texto_publicacion(texto_publicacion), id_pagina(id_pagina) {
}

Publicacion::~Publicacion() {}

// GETTERS

uintmax_t Publicacion::getIdPublicacion() {
    return this->id_publicacion;
}

uintmax_t Publicacion::getIdPagina() {
    return this->id_pagina;
}

herramientas::utiles::Fecha Publicacion::getFechaCreacion() {
    return this->fecha_creacion;
}

std::string Publicacion::getTextoPublicacion() {
    return this->texto_publicacion;
}

// SETTERS

void Publicacion::setIdPublicacion(const uintmax_t & id_publicacion) {
    this->id_publicacion = id_publicacion;
}

void Publicacion::setIdPagina(const uintmax_t & id_pagina) {
    this->id_pagina = id_pagina;
}

void Publicacion::setFechaCreacion(const herramientas::utiles::Fecha & fecha_creacion) {
    this->fecha_creacion = fecha_creacion;
}

void Publicacion::setTextoPublicacion(const std::string & texto_publicacion) {
    this->texto_publicacion = texto_publicacion;
}

// METODOS

// CONSULTAS

// OPERADORES

// METODOS PRIVADOS

herramientas::utiles::Fecha Publicacion::parsearFechaEnFormatoFacebook(std::string fecha_formato_facebook) {
    herramientas::utiles::Fecha fecha;
    // la fecha viene en formato "2015-06-28T11:24:43+0000" --> le borro los "+0000 "
    // para que me quede "2015-06-28T11:24:43" y la pueda parsear bien.
    size_t posicion_signo_mas = fecha_formato_facebook.find_first_of('+');

    fecha_formato_facebook.erase(posicion_signo_mas, 5);

    std::stringstream stream_fecha(fecha_formato_facebook);

    std::tm t = {};
    stream_fecha >> std::get_time(&t, "%Y-%m-%dT%H:%M:%S");

    if (stream_fecha.fail())
    {
        std::cout << "Fecha formato error.\n";
    }
    else
    {
        fecha.setAnio(t.tm_year + 1900);
        fecha.setMes(t.tm_mon + 1);
        fecha.setDia(t.tm_mday);

        fecha.setHoras(t.tm_hour);
        fecha.setMinutos(t.tm_min);
        fecha.setSegundos(t.tm_sec);
    }

    return fecha;
}

    }
}