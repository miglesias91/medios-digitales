#pragma once

// stl
#include <vector>

// casablanca
#include <cpprest/http_client.h>

// rss
#include <rss/include/historia.h>

namespace medios::rss {

class canal {
public:
    canal(const std::string & uri = "");
    virtual ~canal();

    // se conecta SINCRONICAMENTE al canal y devuelve los feeds disponibles.
    bool historias_ya(std::vector<historia> & historias);

    // se conecta ASINCRONICAMENTE al canal y recupera los feeds disponibles. Si ya hay una conexion en espera, entonces no se realiza la conexion.
    bool pedir_historias();

    // devuelve los feeds que se recuperaron de la llamada ASINCRONICA 'pedir_feeds'.
    // si no hubo una llamada previa, entonces se devuelve 'false'.
    bool historias(std::vector<historia> & historias);

private:

    bool parsear(const std::string & contenido_xml, std::vector<historia> & historias);

    web::uri uri;
    web::http::client::http_client * cliente_canal;

    pplx::task<web::http::http_response> peticion;

};

};