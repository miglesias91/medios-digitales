#include <twitter/include/ConsumidorAPI.h>

// protocolos
#include <protocolos/include/OAuth2.h>

namespace medios::twitter {

ConsumidorAPI::ConsumidorAPI(std::string clave_publica, std::string clave_privada) :
    cliente_twitter("https://api.twitter.com"), consumidor_oauth2(clave_publica, clave_privada)
{
}

ConsumidorAPI::~ConsumidorAPI()
{
}

bool ConsumidorAPI::obtenerTokenDeAcceso() {

    bool exito = herramientas::protocolos::OAuth2::solicitarTokenAcceso(&this->consumidor_oauth2, this->cliente_twitter.getURI());

    if (exito)
    {
        //scraping::Logger::info("obtenerTokenAcceso: exitoso!");
    }
    else
    {
        //scraping::Logger::error("obtenerTokenAcceso: NO SE OBTUVO");
    }

    return exito;
}

herramientas::cpprest::HTTPRespuesta * ConsumidorAPI::realizarSolicitud(herramientas::cpprest::HTTPSolicitud * solicitud)
{
    std::string header_token_acceso = "Bearer " + this->consumidor_oauth2.getTokenAcceso();

    solicitud->agregarEncabezado("Authorization", header_token_acceso);

    std::string string_encabezados = "";

    std::vector<std::string> encabezados = solicitud->getEncabezados();
    for (std::vector<std::string>::iterator it = encabezados.begin(); it != encabezados.end(); it++)
    {
        string_encabezados += "," + *it;
    }

    std::string log_solicitud = solicitud->getURI() + " - " + string_encabezados + " - " + solicitud->getMetodo() + " - " + solicitud->getCuerpo();

#ifdef DEBUG || _DEBUG
    log_solicitud = utility::conversions::to_utf8string(solicitud->getSolicitud()->to_string());
#endif // DEBUG || _DEBUG

    //scraping::Logger::debug("realizarSolicitud: { " + log_solicitud + "}");

    herramientas::cpprest::HTTPRespuesta * rta = this->cliente_twitter.solicitar(solicitud);

    //scraping::Logger::debug("realizarSolicitud: { razon respuesta: " + rta->getRazon() + "}");

    return rta;
}

    // GETTERS

    // SETTERS

    // METODOS

    // CONSULTAS

}