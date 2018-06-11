#pragma once

// cpprest wrapper
#include <casablanca_wrapper/include/HTTPSolicitud.h>

// twitter
#include <facebook/include/Pagina.h>

namespace medios::facebook::comunicacion {

class SolicitudPublicaciones : public herramientas::cpprest::HTTPSolicitud {
public:
    SolicitudPublicaciones(medios::facebook::Pagina * cuenta, herramientas::utiles::Fecha desde, herramientas::utiles::Fecha hasta, std::string id_app, std::string clave_secreta_app, unsigned int cantidad_de_publicaciones_max = 100);
    virtual ~SolicitudPublicaciones();
};

};
