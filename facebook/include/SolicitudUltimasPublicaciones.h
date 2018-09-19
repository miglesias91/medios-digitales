#pragma once

// cpprest wrapper
#include <casablanca_wrapper/include/solicitud.h>

// herramientas
#include <utiles/include/Fecha.h>

// twitter
#include <facebook/include/Pagina.h>

namespace medios {
    namespace facebook {
        namespace comunicacion {

class SolicitudUltimasPublicaciones : public herramientas::cpprest::solicitud {
public:
    SolicitudUltimasPublicaciones(medios::facebook::Pagina * cuenta, std::string id_app, std::string clave_secreta_app, unsigned int cantidad_de_publicaciones_max = 100);
    virtual ~SolicitudUltimasPublicaciones();
};

        };
    };
};


