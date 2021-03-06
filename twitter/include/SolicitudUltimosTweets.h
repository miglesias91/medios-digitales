#pragma once

// cpprest wrapper
#include <casablanca_wrapper/include/solicitud.h>

// twitter
#include <twitter/include/Cuenta.h>

namespace medios {
    namespace twitter {
        namespace comunicacion {

class SolicitudUltimosTweets : public herramientas::cpprest::solicitud {
public:
    SolicitudUltimosTweets(medios::twitter::Cuenta * cuenta, const uintmax_t & id_desde = 0, const uint32_t & cantidad_de_tweets = 200);
    virtual ~SolicitudUltimosTweets();
};

        };
    };
};
