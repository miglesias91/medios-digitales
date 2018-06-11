#include <twitter/include/Aplicacion.h>

// scraping
#include <scraping/include/Logger.h>

// twitter
#include <twitter/include/SolicitudUltimosTweets.h>

namespace medios::twitter {

Aplicacion::Aplicacion(ConsumidorAPI * consumidor_api) : consumidor_api(consumidor_api) {}

Aplicacion::~Aplicacion() {

    if (NULL != this->consumidor_api) {
        delete this->consumidor_api;
        this->consumidor_api = NULL;
    }
}

std::vector<Tweet*> Aplicacion::leerUltimosTweets(Cuenta * cuenta, unsigned int cantidad_de_tweets) {

    comunicacion::SolicitudUltimosTweets solicitud_ultimos_tweets(cuenta, cantidad_de_tweets);

    herramientas::cpprest::HTTPRespuesta * respuetas_con_tweets = this->consumidor_api->realizarSolicitud(&solicitud_ultimos_tweets);

    std::vector<herramientas::utiles::Json*> tweets_json = respuetas_con_tweets->getJson()->getAtributoArrayJson();

    std::vector<Tweet*> tweets;
    for (std::vector<herramientas::utiles::Json*>::iterator it = tweets_json.begin(); it != tweets_json.end(); it++)
    {
        //Tweet * nuevo_tweet = this->parsear_json(*it);
        Tweet * nuevo_tweet = new Tweet();
        tweets.push_back(nuevo_tweet);
    }

    delete respuetas_con_tweets;

    return tweets;
}

}