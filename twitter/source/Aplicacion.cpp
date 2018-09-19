#include <twitter/include/Aplicacion.h>

// twitter
#include <twitter/include/SolicitudUltimosTweets.h>

namespace medios {
    namespace twitter {

Aplicacion::Aplicacion(ConsumidorAPI * consumidor_api) : consumidor_api(consumidor_api) {}

Aplicacion::~Aplicacion() {

    if (NULL != this->consumidor_api) {
        delete this->consumidor_api;
        this->consumidor_api = NULL;
    }
}

bool Aplicacion::parsear(herramientas::utiles::Json * json_tweet, Tweet * tweet) {
    
    if (nullptr == json_tweet || nullptr == tweet) {
        return false;
    }

    unsigned long long int id_tweet = json_tweet->getAtributoValorUint("id");
    std::string fecha_creacion_formato_twitter = json_tweet->getAtributoValorString("created_at");
    std::string texto = json_tweet->getAtributoValorString("full_text");

    if ("RT" == texto.substr(0, 2)) {
        // si el texto comienza con "RT" entonces es un retweet.

        Tweet * tweet_retweeteado = new Tweet();
        herramientas::utiles::Json * json_retweet = json_tweet->getAtributoValorJson("retweeted_status");
        parsear(json_retweet, tweet_retweeteado);
        delete json_retweet;
        tweet->setTweetRetweeteado(tweet_retweeteado);
        tweet->esRetweet(true);

        texto = tweet_retweeteado->getTextoTweet();
    }

    herramientas::utiles::Json * user_json = json_tweet->getAtributoValorJson("user");
    unsigned long long int id_usuario = user_json->getAtributoValorUint("id");
    delete user_json;

    herramientas::utiles::Json * entidades_json = json_tweet->getAtributoValorJson("entities");
    std::vector<herramientas::utiles::Json*> hashtags_json = entidades_json->getAtributoArrayJson("hashtags");
    std::vector<std::string> hashtags;
    for (std::vector<herramientas::utiles::Json*>::iterator it = hashtags_json.begin(); it != hashtags_json.end(); it++) {
        std::string hashtag = (*it)->getAtributoValorString("text");
        hashtags.push_back(hashtag);
    }

    for (std::vector<herramientas::utiles::Json*>::iterator it = hashtags_json.begin(); it != hashtags_json.end(); it++) {
        delete *it;
    }

    delete entidades_json;

    tweet->setIdTweet(id_tweet);

    herramientas::utiles::Fecha fecha_creacion;
    if (herramientas::utiles::Fecha::parsear(fecha_creacion_formato_twitter, "%a %b %d %H:%M:%S +0000 %Y", &fecha_creacion)) {
        tweet->setFechaCreacion(fecha_creacion);
    }
    else {
        return false;
    }

    tweet->setTextoTweet(texto);
    tweet->setIdUsuario(id_usuario);
    tweet->setHashtags(hashtags);
}

bool Aplicacion::existe(const std::string & nombre_cuenta) {
    if (nombre_cuenta.size() > 15) {
        return false;
    }

    web::http::client::http_client cliente_twitter(web::uri(utility::conversions::to_string_t("https://twitter.com/users/username_available?username=" + nombre_cuenta)));

    web::http::http_response rta = cliente_twitter.request(web::http::methods::GET).get();

    return false == rta.extract_json().get().at(utility::conversions::to_string_t("valid")).as_bool();
}

std::vector<Tweet*> Aplicacion::leerUltimosTweets(Cuenta * cuenta, const uintmax_t & id_desde, unsigned int cantidad_de_tweets) const {

    comunicacion::SolicitudUltimosTweets solicitud_ultimos_tweets(cuenta, id_desde, cantidad_de_tweets);

    herramientas::cpprest::respuesta * respuetas_con_tweets = this->consumidor_api->realizarSolicitud(&solicitud_ultimos_tweets);

    std::vector<herramientas::utiles::Json*> tweets_json = respuetas_con_tweets->getJson()->getAtributoArrayJson();

    std::vector<Tweet*> tweets;
    for (std::vector<herramientas::utiles::Json*>::iterator it = tweets_json.begin(); it != tweets_json.end(); it++) {
        Tweet * nuevo_tweet = new Tweet();
        parsear(*it, nuevo_tweet);
        tweets.push_back(nuevo_tweet);
        delete *it;
    }

    delete respuetas_con_tweets;

    return tweets;
}

}
}