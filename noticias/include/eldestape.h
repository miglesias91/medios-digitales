#pragma once

// noticias
#include <noticias/include/portal.h>

namespace medios {
    namespace noticias {

class eldestape : public portal {
public:
    eldestape();
    virtual ~eldestape();

    virtual std::string web();

    virtual portal * clon();

    virtual bool extraer_contenido_de_html(const std::string & contenido_html, std::string * contenido) override;
    virtual bool nueva_noticia(const medios::feed::historia & historia, const std::string & seccion) override;
protected:

private:
    bool extraer_datos_de_historia(const std::string & contenido_html, noticia * noti);
};

    };
};