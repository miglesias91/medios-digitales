#pragma once

// stl
#include <vector>

// feed
#include <feed/include/canal.h>

namespace medios { namespace feed {

class atom : public canal {
public:
    atom(const std::string & uri, const std::string & seccion, const std::unordered_map<std::string, std::string> & subcategorias = {});
    virtual ~atom();

protected:
    virtual pugi::xml_object_range<pugi::xml_named_node_iterator> historias_xml(const pugi::xml_document & xml_feed);

    virtual bool parsear_historia(const pugi::xml_node & xml_historia, historia * histo);

    virtual bool extraer_respuesta(const web::http::http_response & rta, std::string * contenido_respuesta);
};

};
};