#pragma once

// utiles
#include <utiles/include/Json.h>
#include <utiles/include/FuncionesSistemaArchivos.h>

// noticias
#include <noticias/include/portal.h>

namespace medios {
    namespace noticias {

class lector {
public:
    lector();
    virtual ~lector();

    void leer(portal * portal,
        const herramientas::utiles::Fecha & desde = herramientas::utiles::Fecha(0, 0, 0),
        const herramientas::utiles::Fecha & hasta = herramientas::utiles::Fecha::getFechaActual()) const;

};

    };
};