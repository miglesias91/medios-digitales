#pragma once

// cpprest wrapper
#include <casablanca_wrapper/include/solicitud.h>

// twitter
#include <facebook/include/Pagina.h>

namespace medios {
    namespace facebook {
        namespace comunicacion {

class SolicitudPublicaciones : public herramientas::cpprest::solicitud {
public:
    SolicitudPublicaciones(medios::facebook::Pagina * cuenta,
        std::string id_app, std::string clave_secreta_app,
        const herramientas::utiles::Fecha & desde = herramientas::utiles::Fecha(0, 0, 0),
        const herramientas::utiles::Fecha & hasta = herramientas::utiles::Fecha(0, 0, 0), unsigned int cantidad_de_publicaciones_max = 100);
    virtual ~SolicitudPublicaciones();
};

        };
    };
};
