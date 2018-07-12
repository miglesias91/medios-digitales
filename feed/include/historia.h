#pragma once

// pugixml
#include <pugixml.hpp>

// utiles
#include <utiles/include/Fecha.h>

namespace medios {
    namespace feed {

class historia {
public:
    historia();
    historia(const std::string & titulo, const std::string & seccion, const std::string & link, herramientas::utiles::Fecha fecha, const std::string & contenido_html,
        const std::string & contenido_historia = "");
    virtual ~historia();

    void titulo(const std::string & titulo);
    std::string titulo() const;

    void link(const std::string & link);
    std::string link() const;

    void seccion(const std::string & seccion);
    std::string seccion() const;

    void fecha(herramientas::utiles::Fecha fecha);
    herramientas::utiles::Fecha fecha() const;

    void html(const std::string &  string_html);
    std::string html() const;

    void contenido(const std::string &  contenido_historia);
    std::string contenido() const;

protected:

    std::string titulo_historia, link_web, seccion_historia, string_html, contenido_historia;
    herramientas::utiles::Fecha fecha_creacion;
};

    };
};