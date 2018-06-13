#pragma once

// pugixml
#include <pugixml.hpp>

// utiles
#include <utiles/include/Fecha.h>

namespace medios::feed {

class historia {
public:
    historia(const std::string & titulo, const std::string & link, const herramientas::utiles::Fecha & fecha, const pugi::xml_document & html);
    virtual ~historia();


};

};