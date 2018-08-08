#pragma once

// noticias
#include <noticias/include/portal.h>

namespace medios {
    namespace noticias {

class clarin : public portal {
public:
    clarin();
    virtual ~clarin();

    virtual std::string web();

    virtual portal * clon();

    virtual bool extraer_contenido_de_html(const std::string & contenido_html, std::string * contenido);
protected:
};

    };
};