#include <noticias/include/fabrica_portales.h>

// stl
#include <algorithm>

namespace medios {
    namespace noticias {

std::shared_ptr<portal> fabrica_portales::nuevo(const std::string & web_portal) {
    clarin c;
    infobae inf;
    la_nacion lana;
    paginadoce pagina;
    eldestape eldestapeweb;

    if (web_portal == c.web()) { return std::make_shared<clarin>(); }
    if (web_portal == inf.web()) { return std::make_shared<infobae>(); }
    if (web_portal == lana.web()) { return std::make_shared<la_nacion>(); }
    if (web_portal == pagina.web()) { return std::make_shared<paginadoce>(); }
    if (web_portal == eldestapeweb.web()) { return std::make_shared<eldestape>(); }

    return nullptr;
}

    }
}