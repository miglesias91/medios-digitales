#pragma once

// twitter
#include <twitter/include/ConsumidorAPI.h>
#include <twitter/include/Cuenta.h>
#include <twitter/include/Tweet.h>

namespace medios::twitter {

class Aplicacion {
public:
    Aplicacion(medios::twitter::ConsumidorAPI * consumidor_api = NULL);
    virtual ~Aplicacion();

    // GETTERS

    // SETTERS

    // METODOS

    // se almacena memoria para los tweets pero no se libera, entonces los tweets deben ser ELIMINADOS luego de ser usados.
    std::vector<Tweet*> leerUltimosTweets(Cuenta * cuenta, unsigned int cantidad_de_tweets = 300);

private:

    medios::twitter::ConsumidorAPI * consumidor_api;
};

};