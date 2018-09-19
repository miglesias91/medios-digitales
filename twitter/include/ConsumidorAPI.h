#pragma once

// casablanca wrapper
#include <casablanca_wrapper/include/cliente.h>
#include <casablanca_wrapper/include/solicitud.h>

// protocolos
#include <protocolos/include/OAuth2Consumidor.h>

namespace medios {
    namespace twitter {

class ConsumidorAPI {
public:
    ConsumidorAPI(std::string clave_publica, std::string clave_privada);
    virtual ~ConsumidorAPI();

    // GETTERS

    // SETTERS

    // METODOS

    bool obtenerTokenDeAcceso();

    herramientas::cpprest::respuesta * realizarSolicitud(herramientas::cpprest::solicitud * solicitud);

    // CONSULTAS

private:

    // ATRIBUTOS

    herramientas::protocolos::OAuth2Consumidor consumidor_oauth2;

    herramientas::cpprest::cliente cliente_twitter;
};

    };
};