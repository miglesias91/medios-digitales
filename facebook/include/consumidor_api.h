#pragma once

// casablanca wrapper
#include <casablanca_wrapper/include/HTTPCliente.h>
#include <casablanca_wrapper/include/HTTPSolicitud.h>

// protocolos
#include <protocolos/include/OAuth2Consumidor.h>

namespace medios::facebook {

class consumidor_api {
public:
    consumidor_api(std::string clave_publica, std::string clave_privada);
    virtual ~consumidor_api();

    // GETTERS

    herramientas::protocolos::OAuth2Consumidor getConsumidorOAuth2();

    // SETTERS

    // METODOS

    bool pedir_token();

    herramientas::cpprest::HTTPRespuesta * consumir(herramientas::cpprest::HTTPSolicitud * solicitud);

    // CONSULTAS

private:

    // ATRIBUTOS

    herramientas::protocolos::OAuth2Consumidor consumidor_oauth2;

    herramientas::cpprest::HTTPCliente cliente_facebook;
};

};