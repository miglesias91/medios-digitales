#pragma once

// cpprest wrapper
#include <casablanca_wrapper/include/HTTPSolicitud.h>

// twitter
#include <twitter/include/Cuenta.h>

namespace medios::twitter::comunicacion {


class SolicitudUltimosTweets : public herramientas::cpprest::HTTPSolicitud
{
public:
    SolicitudUltimosTweets(medios::twitter::Cuenta * cuenta, unsigned int cantidad_de_tweets);
    virtual ~SolicitudUltimosTweets();
};

};
};
};


