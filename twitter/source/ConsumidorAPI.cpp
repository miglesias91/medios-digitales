#include <twitter/include/ConsumidorAPI.h>

// protocolos
#include <protocolos/include/OAuth2.h>

namespace medios {
    namespace twitter {

ConsumidorAPI::ConsumidorAPI(std::string clave_publica, std::string clave_privada) :
    cliente_twitter("https://api.twitter.com"), consumidor_oauth2(clave_publica, clave_privada)
{
}

ConsumidorAPI::~ConsumidorAPI()
{
}

bool ConsumidorAPI::obtenerTokenDeAcceso() {

    bool exito = herramientas::protocolos::OAuth2::solicitarTokenAcceso(&this->consumidor_oauth2, this->cliente_twitter.uri());

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

herramientas::cpprest::respuesta * ConsumidorAPI::realizarSolicitud(herramientas::cpprest::solicitud * solicitud)
{
    std::string header_token_acceso = "Bearer " + this->consumidor_oauth2.getTokenAcceso();

    solicitud->nuevo_encabezado("Authorization", header_token_acceso);

    std::string string_encabezados = "";

    std::vector<std::string> encabezados = solicitud->encabezados();
    for (std::vector<std::string>::iterator it = encabezados.begin(); it != encabezados.end(); it++)
    {
        string_encabezados += "," + *it;
    }

    std::string log_solicitud = solicitud->uri() + " - " + string_encabezados + " - " + solicitud->nombre_metodo() + " - " + solicitud->cuerpo();

#ifdef DEBUG || _DEBUG
    log_solicitud = utility::conversions::to_utf8string(solicitud->getSolicitud()->to_string());
#endif // DEBUG || _DEBUG

    //scraping::Logger::debug("realizarSolicitud: { " + log_solicitud + "}");

    herramientas::cpprest::respuesta * rta = this->cliente_twitter.solicitar(solicitud);

    //scraping::Logger::debug("realizarSolicitud: { razon respuesta: " + rta->getRazon() + "}");

    return rta;
}

    // GETTERS

    // SETTERS

    // METODOS

    // CONSULTAS

    }
}