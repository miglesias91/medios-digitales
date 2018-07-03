#pragma once

// stl
#include <unordered_map>

// stl
#include <memory>

// feed
#include <feed/include/canal.h>

// noticias
#include <noticias/include/noticia.h>
#include <noticias/include/la_nacion.h>
#include <noticias/include/clarin.h>
#include <noticias/include/infobae.h>

namespace medios {
    namespace noticias {

class fabrica_portales {
public:
    static std::shared_ptr<portal> nuevo(const std::string & web_portal);

private:
    static std::unordered_map<std::string, portal*> portales;
};

    };
};