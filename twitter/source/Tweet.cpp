#include <twitter/include/Tweet.h>

// stl
#include <chrono>
#include <iomanip>
#include <sstream>
#include <iostream>

// herramientas
#include <utiles/include/Conversiones.h>

namespace medios::twitter {

Tweet::Tweet() : tweet_retweeteado(NULL), es_retweet(false)
{
    //unsigned long long int id_tweet = this->getJson()->getAtributoValorUint("id");
    //std::string fecha_creacion_formato_twitter = this->getJson()->getAtributoValorString("created_at");
    //std::string texto = this->getJson()->getAtributoValorString("full_text");

    //if ("RT" == texto.substr(0, 2))
    //{// si el texto comienza con "RT" entonces es un retweet.
    //    this->tweet_retweeteado = new Tweet(this->getJson()->getAtributoValorJson("retweeted_status"));
    //    texto = this->tweet_retweeteado->getTexto();
    //    this->es_retweet = true;
    //}

    //herramientas::utiles::Json * user_json = this->getJson()->getAtributoValorJson("user");
    //unsigned long long int id_usuario = user_json->getAtributoValorUint("id");
    //delete user_json;

    //herramientas::utiles::Json * entidades_json = this->getJson()->getAtributoValorJson("entities");
    //std::vector<herramientas::utiles::Json*> hashtags_json = entidades_json->getAtributoArrayJson("hashtags");
    //std::vector<std::string> hashtags;
    //for (std::vector<herramientas::utiles::Json*>::iterator it = hashtags_json.begin(); it != hashtags_json.end(); it++)
    //{
    //    std::string hashtag = (*it)->getAtributoValorString("text");
    //    hashtags.push_back(hashtag);
    //}

    //for (std::vector<herramientas::utiles::Json*>::iterator it = hashtags_json.begin(); it != hashtags_json.end(); it++)
    //{
    //    delete *it;
    //}

    //delete entidades_json;

    //this->setIdTweet(id_tweet);
    //this->setFechaCreacion(this->parsearFechaEnFormatoTwitter(fecha_creacion_formato_twitter));
    //this->setTextoTweet(texto);
    //this->setIdUsuario(id_usuario);
    //this->setHashtags(hashtags);
}

Tweet::~Tweet()
{
    if (NULL != this->tweet_retweeteado)
    {
        delete this->tweet_retweeteado;
        this->tweet_retweeteado = NULL;
    }
}

// GETTERS

unsigned long long int Tweet::getIdTweet()
{
    return this->id_tweet;
}

herramientas::utiles::Fecha Tweet::getFechaCreacion()
{
    return this->fecha_creacion;
}

std::string Tweet::getTextoTweet()
{
    return this->texto_tweet;
}

unsigned long long int Tweet::getIdUsuario()
{
    return this->id_usuario;
}

std::vector<std::string> Tweet::getHashtags()
{
    return this->hashtags;
}

Tweet * Tweet::getTweetRetweeteado()
{
    return this->tweet_retweeteado;
}

// SETTERS

void Tweet::setIdTweet(unsigned long long int id_tweet)
{
    this->id_tweet = id_tweet;
}

void Tweet::setFechaCreacion(herramientas::utiles::Fecha fecha_creacion)
{
    this->fecha_creacion = fecha_creacion;
}

void Tweet::setTextoTweet(std::string texto_tweet)
{
    this->texto_tweet = texto_tweet;
}

void Tweet::setIdUsuario(unsigned long long int id_usuario)
{
    this->id_usuario = id_usuario;
}

void Tweet::setHashtags(std::vector<std::string> hashtags)
{
    this->hashtags = hashtags;
}

void Tweet::setTweetRetweeteado(Tweet * tweet_retweeteado)
{
    if (NULL != this->tweet_retweeteado)
    {
        delete this->tweet_retweeteado;
        this->tweet_retweeteado = NULL;
    }

    this->tweet_retweeteado = tweet_retweeteado;
}

// METODOS

void Tweet::agregarHashtags(std::string hashtag)
{
    this->hashtags.push_back(hashtag);
}

// CONSULTAS

bool Tweet::contieneHashtag(std::string hashtag)
{
    if (this->hashtags.end() == std::find(this->hashtags.begin(), this->hashtags.end(), hashtag))
    {
        return false;
    }
    return true;
}

bool Tweet::esRetweet()
{
    return this->es_retweet;
}

// OPERADORES

// METODOS PRIVADOS

herramientas::utiles::Fecha Tweet::parsearFechaEnFormatoTwitter(std::string fecha_formato_twitter)
{
    herramientas::utiles::Fecha fecha;
    // la fecha viene en formato "Fri Dec 08 20:33:39 +0000 2017" --> le borro los "+0000 "
    // para que me quede "Fri Dec 08 20:33:39 2017" y la pueda parsear bien.
    size_t posicion_signo_mas = fecha_formato_twitter.find_first_of('+');

    fecha_formato_twitter.erase(posicion_signo_mas, 6);

    std::stringstream stream_fecha(fecha_formato_twitter);

    std::tm t = {};
    stream_fecha >> std::get_time(&t, "%a %b %d %H:%M:%S %Y");

    if (stream_fecha.fail())
    {
        std::cout << "Fecha formato error.\n";
    }
    else
    {
        fecha.setAnio(t.tm_year + 1900);
        fecha.setMes(t.tm_mon + 1);
        fecha.setDia(t.tm_mday);

        fecha.setHoras(t.tm_hour);
        fecha.setMinutos(t.tm_min);
        fecha.setSegundos(t.tm_sec);
    }

    return fecha;
}

}