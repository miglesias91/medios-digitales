#include <twitter/include/Tweet.h>

// stl
#include <chrono>
#include <iomanip>
#include <sstream>
#include <iostream>

// herramientas
#include <utiles/include/Conversiones.h>

namespace medios {
    namespace twitter {

Tweet::Tweet() : tweet_retweeteado(NULL), es_retweet(false) {}

Tweet::Tweet(const uintmax_t id_tweet, const uintmax_t & id_usuario, const herramientas::utiles::Fecha & fecha_creacion, const std::string & texto_tweet)
: id_tweet(id_tweet), id_usuario(id_usuario), fecha_creacion(fecha_creacion), texto_tweet(texto_tweet) {}

Tweet::~Tweet() {
    if (NULL != this->tweet_retweeteado)
    {
        delete this->tweet_retweeteado;
        this->tweet_retweeteado = NULL;
    }
}

// GETTERS

uintmax_t Tweet::getIdTweet() {
    return this->id_tweet;
}

herramientas::utiles::Fecha Tweet::getFechaCreacion() {
    return this->fecha_creacion;
}

std::string Tweet::getTextoTweet() {
    return this->texto_tweet;
}

uintmax_t Tweet::getIdUsuario() {
    return this->id_usuario;
}

std::vector<std::string> Tweet::getHashtags() {
    return this->hashtags;
}

Tweet * Tweet::getTweetRetweeteado() {
    return this->tweet_retweeteado;
}

// SETTERS

void Tweet::setIdTweet(const uintmax_t & id_tweet) {
    this->id_tweet = id_tweet;
}

void Tweet::setFechaCreacion(const herramientas::utiles::Fecha & fecha_creacion) {
    this->fecha_creacion = fecha_creacion;
}

void Tweet::setTextoTweet(const std::string & texto_tweet) {
    this->texto_tweet = texto_tweet;
}

void Tweet::setIdUsuario(const uintmax_t & id_usuario) {
    this->id_usuario = id_usuario;
}

void Tweet::setHashtags(const std::vector<std::string> & hashtags) {
    this->hashtags = hashtags;
}

void Tweet::setTweetRetweeteado(Tweet * tweet_retweeteado) {
    if (NULL != this->tweet_retweeteado)
    {
        delete this->tweet_retweeteado;
        this->tweet_retweeteado = NULL;
    }

    this->tweet_retweeteado = tweet_retweeteado;
}

// METODOS

void Tweet::agregarHashtags(const std::string & hashtag) {
    this->hashtags.push_back(hashtag);
}

// CONSULTAS

bool Tweet::contieneHashtag(const std::string & hashtag) {

    if (this->hashtags.end() == std::find(this->hashtags.begin(), this->hashtags.end(), hashtag)) {
        return false;
    }
    return true;
}

bool Tweet::esRetweet() {
    return this->es_retweet;
}

void Tweet::esRetweet(bool es_retweet) {
    this->es_retweet = es_retweet;
}

// OPERADORES

// METODOS PRIVADOS

}
}
