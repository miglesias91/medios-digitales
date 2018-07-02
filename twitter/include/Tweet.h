#pragma once

// herramientas
#include <utiles/include/Fecha.h>

namespace medios {
    namespace twitter {

class Tweet {
public:

    Tweet();
    Tweet(const uintmax_t id_tweet, const uintmax_t & id_usuario, const herramientas::utiles::Fecha & fecha_creacion, const std::string & texto_tweet);
	virtual ~Tweet();

    // GETTERS

    uintmax_t getIdTweet();

    herramientas::utiles::Fecha getFechaCreacion();

    std::string getTextoTweet();

    uintmax_t getIdUsuario();

    std::vector<std::string> getHashtags();

    Tweet * getTweetRetweeteado();

    // SETTERS

    void setIdTweet(const uintmax_t & id);

    void setFechaCreacion(const herramientas::utiles::Fecha & fecha_creacion);

    void setTextoTweet(const std::string & texto_tweet);

    void setIdUsuario(const uintmax_t & id_usuario);

    void setHashtags(const std::vector<std::string> & hashtags);
    
    void setTweetRetweeteado(Tweet * tweet_retweeteado);

    // METODOS

    void agregarHashtags(const std::string & hashtag);

    // CONSULTAS

    bool contieneHashtag(const std::string & hashtag);

    bool esRetweet();
    void esRetweet(bool es_retweet);

    // OPERADORES

private:

    // METODOS PRIVADOS

    // ATRIBUTOS

    uintmax_t id_tweet, id_usuario;

    herramientas::utiles::Fecha fecha_creacion;

    // esta en formato UTF8 xq obtiene el valor del Json (rapidjson) que contiene.
    // (ir al test 'GettersYSettersCodificaciones' de 'herramientas_desarrollo' para ver como funciona.
    std::string texto_tweet;

    std::vector<std::string> hashtags;

    bool es_retweet;

    Tweet * tweet_retweeteado;
};

};
};