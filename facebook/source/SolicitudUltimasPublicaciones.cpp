#include <facebook/include/SolicitudUltimasPublicaciones.h>

namespace medios::facebook::comunicacion {

SolicitudUltimasPublicaciones::SolicitudUltimasPublicaciones(medios::facebook::Pagina * pagina, std::string id_app, std::string clave_secreta_app, unsigned int cantidad_de_publicaciones_max) {
    // creo y armo la solicitud para el token de acceso
    this->setSolicitud(new web::http::http_request());

    // armo la uri.
    std::string uri = "/v2.12/" + pagina->getNombre() + "/feed?limit=" + std::to_string(cantidad_de_publicaciones_max);

    // si tiene ultima publicacion analizada, reemplazo el valor de since.
    auto fecha_ultima_publicacion_actualizada = pagina->getFechaUltimaPublicacionAnalizada();
    if (herramientas::utiles::Fecha(0, 0, 0) != fecha_ultima_publicacion_actualizada)
    {
        uri += "&since=" + pagina->getFechaUltimaPublicacionAnalizada().getStringAAAAMMDDHHmmSS("-", "T", ":");
    }

    uri += "&access_token=" + id_app + "%7C" + clave_secreta_app; // '%7C' es la codificacion requerida por las URI para el caracter '|'.

    this->setURI(uri);

    this->setGET();
}

SolicitudUltimasPublicaciones::~SolicitudUltimasPublicaciones() {}

}