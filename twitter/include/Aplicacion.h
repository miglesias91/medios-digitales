#pragma once

// twitter
#include <twitter/include/ConsumidorAPI.h>
#include <twitter/include/Cuenta.h>
#include <twitter/include/Tweet.h>

namespace medios {
    namespace twitter {

class Aplicacion {
public:
    Aplicacion(medios::twitter::ConsumidorAPI * consumidor_api = NULL);
    virtual ~Aplicacion();

    // GETTERS

    // SETTERS

    // METODOS

    static bool parsear(herramientas::utiles::Json * json_tweet, Tweet * tweet);
    
    static bool existe(const std::string & nombre_cuenta);

    // se almacena memoria para los tweets pero no se libera, entonces los tweets deben ser ELIMINADOS luego de ser usados.
    std::vector<Tweet*> leerUltimosTweets(Cuenta * cuenta, const uintmax_t & id_desde = 0, unsigned int cantidad_de_tweets = 300) const;

private:

    medios::twitter::ConsumidorAPI * consumidor_api;
};

    };
};