#pragma once

// noticias
#include <noticias/include/portal.h>

namespace medios {
    namespace noticias {

class la_nacion : public portal {
public:
    la_nacion();
    virtual ~la_nacion();

    virtual std::string web();

    virtual portal * clon();

    virtual bool extraer_contenido_de_html(const std::string & contenido_html, std::string * contenido);
protected:
};

    };
};