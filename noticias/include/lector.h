#pragma once

// noticias
#include <noticias/include/portal.h>

namespace medios::noticias {

class lector {
public:
    lector();
    virtual ~lector();

    void leer(portal * portal);

};

};