#pragma once

// herramientas
#include <utiles/include/Fecha.h>

namespace medios::twitter {


class Tweet
{
public:

    Tweet();
	virtual ~Tweet();

    // GETTERS

    unsigned long long int getIdTweet();

    herramientas::utiles::Fecha getFechaCreacion();

    std::string getTextoTweet();

    unsigned long long int getIdUsuario();

    std::vector<std::string> getHashtags();

    Tweet * getTweetRetweeteado();

    // SETTERS

    void setIdTweet(unsigned long long int id);

    void setFechaCreacion(herramientas::utiles::Fecha fecha_creacion);

    void setTextoTweet(std::string texto_tweet);

    void setIdUsuario(unsigned long long int id_usuario);

    void setHashtags(std::vector<std::string> hashtags);
    
    void setTweetRetweeteado(Tweet * tweet_retweeteado);

    // METODOS

    void agregarHashtags(std::string hashtag);

    // CONSULTAS

    bool contieneHashtag(std::string hashtag);

    bool esRetweet();

    // OPERADORES

private:

    // METODOS PRIVADOS

    herramientas::utiles::Fecha parsearFechaEnFormatoTwitter(std::string fecha_formato_twitter);

    // ATRIBUTOS

    unsigned long long int id_tweet;

    herramientas::utiles::Fecha fecha_creacion;

    // esta en formato UTF8 xq obtiene el valor del Json (rapidjson) que contiene.
    // (ir al test 'GettersYSettersCodificaciones' de 'herramientas_desarrollo' para ver como funciona.
    std::string texto_tweet;

    unsigned long long int id_usuario;

    std::vector<std::string> hashtags;

    bool es_retweet;

    Tweet * tweet_retweeteado;
};

};

