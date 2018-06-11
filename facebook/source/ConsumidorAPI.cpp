#include <facebook/include/ConsumidorAPI.h>

// protocolos
#include <protocolos/include/OAuth2.h>

namespace medios::facebook {

ConsumidorAPI::ConsumidorAPI(std::string clave_publica, std::string clave_privada) :
    cliente_facebook("https://graph.facebook.com"), consumidor_oauth2(clave_publica, clave_privada) {}

ConsumidorAPI::~ConsumidorAPI() {}

herramientas::protocolos::OAuth2Consumidor ConsumidorAPI::getConsumidorOAuth2() {
    return this->consumidor_oauth2;
}

bool ConsumidorAPI::obtenerTokenDeAcceso() {

    return herramientas::protocolos::OAuth2::solicitarTokenAcceso(&this->consumidor_oauth2, this->cliente_facebook.getURI());
}

herramientas::cpprest::HTTPRespuesta * ConsumidorAPI::realizarSolicitud(herramientas::cpprest::HTTPSolicitud * solicitud) {
    //std::string header_token_acceso = "Bearer " + this->consumidor_oauth2.getTokenAcceso();

    //solicitud->agregarEncabezado("Authorization", header_token_acceso);

    std::string string_encabezados = "";

    std::vector<std::string> encabezados = solicitud->getEncabezados();
    for (std::vector<std::string>::iterator it = encabezados.begin(); it != encabezados.end(); it++)
    {
        string_encabezados += "," + *it;
    }

    std::string log_solicitud = solicitud->getURI() + " - " + string_encabezados + " - " + solicitud->getMetodo() + " - " + solicitud->getCuerpo();

#if defined(DEBUG) || defined(_DEBUG)
    log_solicitud = utility::conversions::to_utf8string(solicitud->getSolicitud()->to_string());
#endif // DEBUG || _DEBUG

    herramientas::cpprest::HTTPRespuesta * rta = this->cliente_facebook.solicitar(solicitud);

    return rta;
}

}
// GETTERS

// SETTERS

// METODOS

// CONSULTAS