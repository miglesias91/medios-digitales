#include <twitter/include/SolicitudUltimosTweets.h>

namespace medios {
    namespace twitter {
        namespace comunicacion {

SolicitudUltimosTweets::SolicitudUltimosTweets(medios::twitter::Cuenta * cuenta, const uintmax_t & id_desde, const uint32_t & cantidad_de_tweets) {
    // creo y armo la solicitud para el token de acceso
    this->setSolicitud(new web::http::http_request());

    // armo la uri.
    std::string uri = "/1.1/statuses/user_timeline.json?screen_name=" + cuenta->getNombre() + "&count=" + std::to_string(cantidad_de_tweets);

    // si tiene ultimo tweet analizado, entonces lo agrego como parametro.
    if (0 != id_desde)
    {
        uri += "&since_id=" + std::to_string(id_desde);
    }

    uri += "&trim_user=true&tweet_mode=extended";

    this->setURI(uri);

    this->setGET();
}

SolicitudUltimosTweets::~SolicitudUltimosTweets() {}

}
}
}
