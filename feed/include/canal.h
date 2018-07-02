#pragma once

// stl
#include <vector>

// casablanca
#include <cpprest/http_client.h>

// feed
#include <feed/include/historia.h>

namespace medios {
    namespace feed {

class canal {
public:
    canal(const std::string & uri, const std::string & seccion);
    virtual ~canal();

    // Si HAY una peticion en curso, entonces espera hasta que termine y devuelve la historias.
    // Si NO HAY una peticion en curso, entonces hace la peticion y espera a que termine para devolver las historias.
    bool historias_ya(std::vector<historia*> & historias,
        const herramientas::utiles::Fecha & desde = herramientas::utiles::Fecha(0, 0, 0),
        const herramientas::utiles::Fecha & hasta = herramientas::utiles::Fecha::getFechaActual());

    // se conecta ASINCRONICAMENTE y cuando termina la peticion almacena las historias disponibles. Si ya hay una conexion en espera, entonces no se realiza la peticion.
    bool pedir_historias();

    // devuelve las historias que se recuperaron de la llamada ASINCRONICA 'pedir_historias'.
    // si hay una llamada en curso, se devuelve 'false'.
    bool historias(std::vector<historia*> & historias,
        const herramientas::utiles::Fecha & desde = herramientas::utiles::Fecha(0, 0, 0),
        const herramientas::utiles::Fecha & hasta = herramientas::utiles::Fecha::getFechaActual());

    // devuelve el nombre de la seccion a la que pertenece el canal.
    std::string seccion() const;

protected:

    virtual pugi::xml_object_range<pugi::xml_named_node_iterator> historias_xml(const pugi::xml_document & xml_feed) = 0;

    virtual bool parsear_historia(const pugi::xml_node & entrada, historia * historia) = 0;

    virtual bool parsear(const std::string & contenido_xml, std::vector<historia*> & historias,
        const herramientas::utiles::Fecha & desde, const herramientas::utiles::Fecha & hasta);

    virtual bool descargar_y_guardar_historia(historia * nueva, std::vector<historia*> & historias, uint32_t & cantidad_de_historias_descargadas);

    web::uri uri;
    web::http::client::http_client cliente_canal;

    bool peticion_activa;
    pplx::task<web::http::http_response> tarea_peticion;
    web::http::http_response respuesta;

    std::string seccion_canal;
};

    };
};