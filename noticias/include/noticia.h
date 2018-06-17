#pragma once

// utiles
#include <utiles/include/Fecha.h>

namespace medios::noticias {

class noticia {
public:
    noticia();
    noticia(const std::string & titulo, const std::string & contenido, const std::string & seccion, herramientas::utiles::Fecha fecha);
    virtual ~noticia();

    void titulo(const std::string & titulo);
    std::string titulo();

    void contenido(const std::string & contenido);
    std::string contenido();

    void seccion(const std::string & seccion);
    std::string seccion();

    void fecha(herramientas::utiles::Fecha fecha);
    herramientas::utiles::Fecha fecha();

protected:

    std::string titulo_noticia, contenido_noticia, seccion_noticia;
    herramientas::utiles::Fecha fecha_creacion;
};

};