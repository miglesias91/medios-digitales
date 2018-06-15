#pragma once

// pugixml
#include <pugixml.hpp>

// utiles
#include <utiles/include/Fecha.h>

namespace medios::feed {

class historia {
public:
    historia();
    historia(std::string titulo, std::string link, herramientas::utiles::Fecha fecha, std::string contenido_html);
    virtual ~historia();

    void titulo(std::string titulo);
    std::string titulo();

    void link(std::string link);
    std::string link();

    void fecha(herramientas::utiles::Fecha fecha);
    herramientas::utiles::Fecha fecha();

    void html(std::string string_html);
    std::string html();

protected:

    std::string titulo_historia, link_web, string_html;
    herramientas::utiles::Fecha fecha_creacion;
};

};