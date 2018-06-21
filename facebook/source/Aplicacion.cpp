#include <facebook/include/aplicacion.h>

// twitter
#include <facebook/include/SolicitudUltimasPublicaciones.h>
#include <facebook/include/SolicitudPublicaciones.h>

namespace medios::facebook {

aplicacion::aplicacion(medios::facebook::consumidor_api * consumidor_api) : consumidor_api(consumidor_api) {}

aplicacion::~aplicacion() {

    if (NULL != this->consumidor_api) {
        delete this->consumidor_api;
        this->consumidor_api = NULL;
    }
}

// GETTERS

std::string aplicacion::id() {

    return this->consumidor_api->getConsumidorOAuth2().getClavePublica();
}

std::string aplicacion::clave_privada() {

    return this->consumidor_api->getConsumidorOAuth2().getClavePrivada();
}

// SETTERS

// METODOS

std::vector<Publicacion*> aplicacion::leer(Pagina * pagina, unsigned int cantidad_de_publicaciones_maximo) {

    medios::facebook::comunicacion::SolicitudUltimasPublicaciones solicitud_ultimas_publicaciones(pagina, this->id(), this->clave_privada(), cantidad_de_publicaciones_maximo);

    herramientas::cpprest::HTTPRespuesta * respuetas_con_publicaciones = this->consumidor_api->consumir(&solicitud_ultimas_publicaciones);

    std::vector<herramientas::utiles::Json*> publicaciones_json = respuetas_con_publicaciones->getJson()->getAtributoArrayJson("data");

    std::vector<Publicacion*> publicaciones;
    for (std::vector<herramientas::utiles::Json*>::iterator it = publicaciones_json.begin(); it != publicaciones_json.end(); it++) {
        //Publicacion * nueva_publicacion = new Publicacion(*it);
        Publicacion * nueva_publicacion = new Publicacion();

        //scraping::Logger::debug("leerUltimasPublicaciones: publicacion creada{ " + scraping::Logger::getDebugLog(nueva_publicacion) + " }");

        publicaciones.push_back(nueva_publicacion);
    }

    delete respuetas_con_publicaciones;

    return publicaciones;
}

std::vector<Publicacion*> aplicacion::leer(Pagina * pagina, herramientas::utiles::Fecha desde, herramientas::utiles::Fecha hasta, unsigned int cantidad_de_publicaciones_maximo)
{
    medios::facebook::comunicacion::SolicitudPublicaciones solicitud_ultimas_publicaciones(pagina, desde, hasta, this->id(), this->clave_privada(), cantidad_de_publicaciones_maximo);

    herramientas::cpprest::HTTPRespuesta * respuetas_con_publicaciones = this->consumidor_api->consumir(&solicitud_ultimas_publicaciones);

    std::vector<herramientas::utiles::Json*> publicaciones_json = respuetas_con_publicaciones->getJson()->getAtributoArrayJson("data");

    std::vector<Publicacion*> publicaciones;
    for (std::vector<herramientas::utiles::Json*>::iterator it = publicaciones_json.begin(); it != publicaciones_json.end(); it++) {
        //Publicacion * nueva_publicacion = new Publicacion(*it);
        Publicacion * nueva_publicacion = new Publicacion();

        //scraping::Logger::debug("leerUltimasPublicaciones: publicacion creada{ " + scraping::Logger::getDebugLog(nueva_publicacion) + " }");

        publicaciones.push_back(nueva_publicacion);
    }

    delete respuetas_con_publicaciones;

    return publicaciones;
}

}