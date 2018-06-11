#pragma once

// stl
#include <vector>

// casablanca
#include <cpprest/http_client.h>

// rss
#include <rss/include/feed.h>

namespace medios::rss {

class canal {
public:
    canal(const std::string & uri = "");
    virtual ~canal();

    // se conecta SINCRONICAMENTE al canal y devuelve los feeds disponibles.
    bool feeds_ya(std::vector<feed> & feeds);

    // se conecta ASINCRONICAMENTE al canal y recupera los feeds disponibles. Si ya hay una conexion en espera, entonces no se realiza la conexion.
    bool pedir_feeds();

    // devuelve los feeds que se recuperaron de la llamada ASINCRONICA 'pedir_feeds'.
    // si no hubo una llamada previa, entonces se devuelve 'false'.
    bool feeds(std::vector<feed> & feeds);

private:

    bool parsear(const std::string & contenido_xml, std::vector<feed> & feeds);

    web::uri uri;
    web::http::client::http_client * cliente_canal;

    pplx::task<web::http::http_response> peticion;

};

};