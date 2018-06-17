#pragma once

// pugixml
#include <pugixml.hpp>

// utiles
#include <utiles/include/Fecha.h>

namespace medios::feed {

class historia {
public:
    historia();
    historia(const std::string & titulo, const std::string & link, herramientas::utiles::Fecha fecha, const std::string & contenido_html);
    virtual ~historia();

    void titulo(const std::string & titulo);
    std::string titulo() const;

    void link(const std::string &  link);
    std::string link() const;

    void fecha(herramientas::utiles::Fecha fecha);
    herramientas::utiles::Fecha fecha() const;

    void html(const std::string &  string_html);
    std::string html() const;

protected:

    std::string titulo_historia, link_web, string_html;
    herramientas::utiles::Fecha fecha_creacion;
};

};