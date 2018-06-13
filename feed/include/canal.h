#pragma once

// stl
#include <vector>

// casablanca
#include <cpprest/http_client.h>

// feed
#include <feed/include/historia.h>

namespace medios::feed {

class canal {
public:
    canal(const std::string & uri);
    virtual ~canal();

    // Si HAY una peticion en curso, entonces espera hasta que termine y devuelve la historias.
    // Si NO HAY una peticion en curso, entonces hace la peticion y espera a que termine para devolver las historias.
    bool historias_ya(std::vector<historia> & historias);

    // se conecta ASINCRONICAMENTE y cuando termina la peticion almacena las historias disponibles. Si ya hay una conexion en espera, entonces no se realiza la peticion.
    bool pedir_historias();

    // devuelve las historias que se recuperaron de la llamada ASINCRONICA 'pedir_historias'.
    // si hay una llamada en curso, se devuelve 'false'.
    bool historias(std::vector<historia> & historias);

protected:

    virtual bool parsear(const std::string & contenido_xml, std::vector<historia> & historias) = 0;

    web::uri uri;
    web::http::client::http_client cliente_canal;

    bool peticion_activa;
    pplx::task<web::http::http_response> tarea_peticion;
    web::http::http_response respuesta;

};

};