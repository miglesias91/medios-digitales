#include <facebook/include/aplicacion.h>

// utiles
#include <utiles/include/FuncionesString.h>

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

std::string aplicacion::id() const {

    return this->consumidor_api->getConsumidorOAuth2().getClavePublica();
}

std::string aplicacion::clave_privada() const {

    return this->consumidor_api->getConsumidorOAuth2().getClavePrivada();
}

// SETTERS

// METODOS

bool aplicacion::parsear(herramientas::utiles::Json * json_publicacion, Publicacion * publicacion) {

    if (nullptr == json_publicacion || nullptr == publicacion) {
        return false;
    }

    std::string id_pagina_id_publicacion = json_publicacion->getAtributoValorString("id");
    std::string fecha_creacion_formato_facebook = json_publicacion->getAtributoValorString("created_time");

    std::string texto = "";
    if (json_publicacion->contieneAtributo("message")) {
        texto = json_publicacion->getAtributoValorString("message");
    }

    std::vector<std::string> ids = herramientas::utiles::FuncionesString::separar(id_pagina_id_publicacion, "_");

    publicacion->setIdPublicacion(std::stoull(ids[1]));

    herramientas::utiles::Fecha fecha;
    if (herramientas::utiles::Fecha::parsear(fecha_creacion_formato_facebook, "%Y-%m-%dT%H:%M:%S", &fecha)) {
        publicacion->setFechaCreacion(fecha);
    }
    else {
        return false;
    }

    publicacion->setTextoPublicacion(texto);
    publicacion->setIdPagina(std::stoull(ids[0]));
    return true;
}

//std::vector<Publicacion*> aplicacion::leer(Pagina * pagina, unsigned int cantidad_de_publicaciones_maximo) const {
//
//    medios::facebook::comunicacion::SolicitudUltimasPublicaciones solicitud_ultimas_publicaciones(pagina, this->id(), this->clave_privada(), cantidad_de_publicaciones_maximo);
//
//    herramientas::cpprest::HTTPRespuesta * respuetas_con_publicaciones = this->consumidor_api->consumir(&solicitud_ultimas_publicaciones);
//
//    std::vector<herramientas::utiles::Json*> publicaciones_json = respuetas_con_publicaciones->getJson()->getAtributoArrayJson("data");
//
//    std::vector<Publicacion*> publicaciones;
//    for (std::vector<herramientas::utiles::Json*>::iterator it = publicaciones_json.begin(); it != publicaciones_json.end(); it++) {
//        Publicacion * nueva_publicacion = new Publicacion();
//        parsear(*it, nueva_publicacion);
//        publicaciones.push_back(nueva_publicacion);
//
//        delete *it;
//    }
//
//    delete respuetas_con_publicaciones;
//
//    return publicaciones;
//}

std::vector<Publicacion*> aplicacion::leer(Pagina * pagina, const herramientas::utiles::Fecha & desde, const herramientas::utiles::Fecha & hasta, const uint32_t & cantidad_de_publicaciones_maximo) const {
    medios::facebook::comunicacion::SolicitudPublicaciones solicitud_ultimas_publicaciones(pagina, this->id(), this->clave_privada(), desde, hasta, cantidad_de_publicaciones_maximo);

    herramientas::cpprest::HTTPRespuesta * respuetas_con_publicaciones = this->consumidor_api->consumir(&solicitud_ultimas_publicaciones);

    std::vector<herramientas::utiles::Json*> publicaciones_json = respuetas_con_publicaciones->getJson()->getAtributoArrayJson("data");

    std::vector<Publicacion*> publicaciones;
    for (std::vector<herramientas::utiles::Json*>::iterator it = publicaciones_json.begin(); it != publicaciones_json.end(); it++) {
        Publicacion * nueva_publicacion = new Publicacion();
        parsear(*it, nueva_publicacion);
        publicaciones.push_back(nueva_publicacion);

        delete *it;
    }

    delete respuetas_con_publicaciones;

    return publicaciones;
}

}