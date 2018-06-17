#pragma once

// noticias
#include <noticias/include/portal.h>

namespace medios::noticias {

class la_nacion : public portal {
public:
    la_nacion();
    virtual ~la_nacion();

protected:
    virtual bool extraer_contenido_de_html(const std::string & contenido_html, std::string & contenido);
};

};