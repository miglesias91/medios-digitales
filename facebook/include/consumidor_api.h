#pragma once

// casablanca wrapper
#include <casablanca_wrapper/include/cliente.h>
#include <casablanca_wrapper/include/solicitud.h>

// protocolos
#include <protocolos/include/OAuth2Consumidor.h>

namespace medios { namespace facebook {

class consumidor_api {
public:
    consumidor_api(std::string clave_publica, std::string clave_privada);
    virtual ~consumidor_api();

    // GETTERS

    herramientas::protocolos::OAuth2Consumidor getConsumidorOAuth2();

    // SETTERS

    // METODOS

    bool pedir_token();

    herramientas::cpprest::respuesta * consumir(herramientas::cpprest::solicitud * solicitud);

    // CONSULTAS

private:

    // ATRIBUTOS

    herramientas::protocolos::OAuth2Consumidor consumidor_oauth2;

    herramientas::cpprest::cliente cliente_facebook;
};

};
};