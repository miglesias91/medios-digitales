
// catch2
#include <catch.hpp>

// twitter
#include <twitter/include/Aplicacion.h>

TEST_CASE("existe cuenta", "twitter[.]") {
    REQUIRE(true == medios::twitter::Aplicacion::existe("mauriciomacri"));
    REQUIRE(false == medios::twitter::Aplicacion::existe("cuentadetwitterconnombremuylargo"));
    REQUIRE(false == medios::twitter::Aplicacion::existe("truchixmal"));
}

TEST_CASE("descargar tweets", "twitter[.]") {
    medios::twitter::ConsumidorAPI * consumidor_api_twitter = new medios::twitter::ConsumidorAPI("aXPpXInb16k0jKIswOYuUS3ly", "MhuDBpN9EtnafrIUHvJEbleJ3WKiFCSBIulwRVNvZTWoXGs2eV");
    consumidor_api_twitter->obtenerTokenDeAcceso();

    medios::twitter::Aplicacion app(consumidor_api_twitter);

    medios::twitter::Cuenta clarin("clarincom");

    std::vector<medios::twitter::Tweet*> tweets = app.leerUltimosTweets(&clarin);

    REQUIRE(200 == tweets.size());

    std::for_each(tweets.begin(), tweets.end(), [](medios::twitter::Tweet* tweet) { delete tweet; });
}

TEST_CASE("parsear tweets", "twitter[.]") {
    std::ifstream archivo_tweets("tweets_de_prueba.txt");

    std::stringstream sstream;
    sstream << archivo_tweets.rdbuf();

    std::string string_tweets(sstream.str());

    herramientas::utiles::Json json_tweets(string_tweets);

    std::vector<herramientas::utiles::Json*> tweets_json = json_tweets.getAtributoArrayJson();

    std::vector<medios::twitter::Tweet*> tweets;
    medios::twitter::Tweet* nuevo_tweet = NULL;
    for (std::vector<herramientas::utiles::Json*>::iterator it = tweets_json.begin(); it != tweets_json.end(); it++)
    {
        nuevo_tweet = new medios::twitter::Tweet();
        medios::twitter::Aplicacion::parsear(*it, nuevo_tweet);
        tweets.push_back(nuevo_tweet);
        delete *it;
    }

    unsigned long long int id_parseado_tweet_1 = tweets[0]->getIdTweet();
    std::string texto_parseado_tweet_1 = tweets[0]->getTextoTweet();
    herramientas::utiles::Fecha fecha_de_creacion_parseada_tweet_1 = tweets[0]->getFechaCreacion();
    unsigned long long int id_usuario_parseado_tweet_1 = tweets[0]->getIdUsuario();
    unsigned int tamanio_vector_hashtags_parseado_tweet_1 = tweets[0]->getHashtags().size();

    unsigned long long int id_correcto_tweet_1 = 708067963060916224;
    std::string texto_correcto_tweet_1 = u8"@jeremycloud Who would win in a battle between a Barred Owl and a Cooper's Hawk? https://t.co/FamikDro2h";
    herramientas::utiles::Fecha fecha_de_creacion_correcta_tweet_1(10, 1, 2016, 23, 12, 12);
    unsigned long long int id_usuario_correcto_tweet_1 = 4449621923;
    unsigned int tamanio_vector_hashtags_correcto_tweet_1 = 0;

    for (std::vector<medios::twitter::Tweet*>::iterator it = tweets.begin(); it != tweets.end(); it++)
    {
        delete *it;
    }

    REQUIRE(id_correcto_tweet_1 == id_parseado_tweet_1);
    REQUIRE(texto_correcto_tweet_1 == texto_parseado_tweet_1);
    REQUIRE(true == (fecha_de_creacion_correcta_tweet_1 == fecha_de_creacion_parseada_tweet_1));
    REQUIRE(id_usuario_correcto_tweet_1 == id_usuario_parseado_tweet_1);
    REQUIRE(tamanio_vector_hashtags_correcto_tweet_1 == tamanio_vector_hashtags_parseado_tweet_1);
}

TEST_CASE("parsear retweets", "twitter[.]") {
    std::ifstream archivo_tweets("retweets_de_prueba.txt");

    std::stringstream sstream;
    sstream << archivo_tweets.rdbuf();

    std::string string_tweets(sstream.str());

    herramientas::utiles::Json json_tweets(string_tweets);

    std::vector<herramientas::utiles::Json*> tweets_json = json_tweets.getAtributoArrayJson();

    std::vector<medios::twitter::Tweet*> tweets;
    medios::twitter::Tweet* nuevo_tweet = NULL;
    for (std::vector<herramientas::utiles::Json*>::iterator it = tweets_json.begin(); it != tweets_json.end(); it++)
    {
        nuevo_tweet = new medios::twitter::Tweet();
        medios::twitter::Aplicacion::parsear(*it, nuevo_tweet);
        tweets.push_back(nuevo_tweet);
        delete *it;
    }

    // datos tweet
    unsigned long long int id_parseado_tweet_1 = tweets[0]->getIdTweet();
    std::string texto_parseado_tweet_1 = tweets[0]->getTextoTweet();
    herramientas::utiles::Fecha fecha_de_creacion_parseada_tweet_1 = tweets[0]->getFechaCreacion();
    unsigned long long int id_usuario_parseado_tweet_1 = tweets[0]->getIdUsuario();
    unsigned int tamanio_vector_hashtags_parseado_tweet_1 = tweets[0]->getHashtags().size();

    unsigned long long int id_correcto_tweet_1 = 958491763248893952;
    std::string texto_correcto_tweet_1 = u8"#YCRT Dirigentes sindicales y políticos santacruceños se reunieron con @CFKArgentina para \nanalizar el estado de situación que atraviesa el yacimiento, tras los más de 400 despidos dispuestos por la intervención del Gobierno Nacional  \nhttps://t.co/ptle5JWGte https://t.co/rM23gXjjqg";
    herramientas::utiles::Fecha fecha_de_creacion_correcta_tweet_1(31, 1, 2018, 0, 6, 58);
    unsigned long long int id_usuario_correcto_tweet_1 = 138814032;
    unsigned int tamanio_vector_hashtags_correcto_tweet_1 = 1;

    // datos retweet
    unsigned long long int id_parseado_retweet_1 = tweets[0]->getTweetRetweeteado()->getIdTweet();
    std::string texto_parseado_retweet_1 = tweets[0]->getTweetRetweeteado()->getTextoTweet();
    herramientas::utiles::Fecha fecha_de_creacion_parseada_retweet_1 = tweets[0]->getTweetRetweeteado()->getFechaCreacion();
    unsigned long long int id_usuario_parseado_retweet_1 = tweets[0]->getTweetRetweeteado()->getIdUsuario();
    unsigned int tamanio_vector_hashtags_parseado_retweet_1 = tweets[0]->getTweetRetweeteado()->getHashtags().size();

    unsigned long long int id_correcto_retweet_1 = 958483263634444292;
    std::string texto_correcto_retweet_1 = u8"#YCRT Dirigentes sindicales y políticos santacruceños se reunieron con @CFKArgentina para \nanalizar el estado de situación que atraviesa el yacimiento, tras los más de 400 despidos dispuestos por la intervención del Gobierno Nacional  \nhttps://t.co/ptle5JWGte https://t.co/rM23gXjjqg";
    herramientas::utiles::Fecha fecha_de_creacion_correcta_retweet_1(30, 1, 2018, 23, 33, 12);
    unsigned long long int id_usuario_correcto_retweet_1 = 884164880114343937;
    unsigned int tamanio_vector_hashtags_correcto_retweet_1 = 1;

    for (std::vector<medios::twitter::Tweet*>::iterator it = tweets.begin(); it != tweets.end(); it++) {
        delete *it;
    }

    REQUIRE(id_correcto_tweet_1 == id_parseado_tweet_1);
    REQUIRE(texto_correcto_tweet_1 == texto_parseado_tweet_1);
    REQUIRE(true == (fecha_de_creacion_correcta_tweet_1 == fecha_de_creacion_parseada_tweet_1));
    REQUIRE(id_usuario_correcto_tweet_1 == id_usuario_parseado_tweet_1);
    REQUIRE(tamanio_vector_hashtags_correcto_tweet_1 == tamanio_vector_hashtags_parseado_tweet_1);

    REQUIRE(id_correcto_retweet_1 == id_parseado_retweet_1);
    REQUIRE(texto_correcto_retweet_1 == texto_parseado_retweet_1);
    REQUIRE(true == (fecha_de_creacion_correcta_retweet_1 == fecha_de_creacion_parseada_retweet_1));
    REQUIRE(id_usuario_correcto_retweet_1 == id_usuario_parseado_retweet_1);
    REQUIRE(tamanio_vector_hashtags_correcto_retweet_1 == tamanio_vector_hashtags_parseado_retweet_1);
}

