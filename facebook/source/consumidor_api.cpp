#include <facebook/include/consumidor_api.h>

// protocolos
#include <protocolos/include/OAuth2.h>

namespace medios {
    namespace facebook {

consumidor_api::consumidor_api(std::string clave_publica, std::string clave_privada) :
    cliente_facebook("https://graph.facebook.com"), consumidor_oauth2(clave_publica, clave_privada) {}

consumidor_api::~consumidor_api() {}

herramientas::protocolos::OAuth2Consumidor consumidor_api::getConsumidorOAuth2() {
    return this->consumidor_oauth2;
}

bool consumidor_api::pedir_token() {

    return herramientas::protocolos::OAuth2::solicitarTokenAcceso(&this->consumidor_oauth2, this->cliente_facebook.uri());
}

herramientas::cpprest::respuesta * consumidor_api::consumir(herramientas::cpprest::solicitud * solicitud) {
    //std::string header_token_acceso = "Bearer " + this->consumidor_oauth2.getTokenAcceso();

    //solicitud->agregarEncabezado("Authorization", header_token_acceso);

    std::string string_encabezados = "";

    std::vector<std::string> encabezados = solicitud->encabezados();
    for (std::vector<std::string>::iterator it = encabezados.begin(); it != encabezados.end(); it++)
    {
        string_encabezados += "," + *it;
    }

    std::string log_solicitud = solicitud->uri() + " - " + string_encabezados + " - " + solicitud->nombre_metodo() + " - " + solicitud->cuerpo();

#if defined(DEBUG) || defined(_DEBUG)
    log_solicitud = utility::conversions::to_utf8string(solicitud->getSolicitud()->to_string());
#endif // DEBUG || _DEBUG

    herramientas::cpprest::respuesta * rta = this->cliente_facebook.solicitar(solicitud);

    return rta;
}
// GETTERS

// SETTERS

// METODOS

// CONSULTAS
    }
}