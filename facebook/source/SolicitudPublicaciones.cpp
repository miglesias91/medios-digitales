#include <facebook/include/SolicitudPublicaciones.h>

namespace medios {
    namespace facebook {
        namespace comunicacion {

SolicitudPublicaciones::SolicitudPublicaciones(medios::facebook::Pagina * pagina,
    std::string id_app, std::string clave_secreta_app,
    const herramientas::utiles::Fecha & desde, const herramientas::utiles::Fecha & hasta,
    unsigned int cantidad_de_publicaciones_max) {
    // creo y armo la solicitud para el token de acceso
    this->setSolicitud(new web::http::http_request());

    // armo la uri.
    std::string uri = "/v2.12/" + pagina->getNombre() + "/feed?limit=" + std::to_string(cantidad_de_publicaciones_max);

    if (herramientas::utiles::Fecha(0, 0, 0) != desde)
    {
        uri += "&since=" + desde.getStringAAAAMMDDHHmmSS("-", "T", ":");
    }

    if (herramientas::utiles::Fecha(0, 0, 0) != hasta)
    {
        uri += "&until=" + hasta.getStringAAAAMMDDHHmmSS("-", "T", ":");
    }

    uri += "&access_token=" + id_app + "%7C" + clave_secreta_app; // '%7C' es la codificacion requerida por las URI para el caracter '|'.

    this->setURI(uri);

    this->setGET();
}

SolicitudPublicaciones::~SolicitudPublicaciones() {}

        }
    }
}
