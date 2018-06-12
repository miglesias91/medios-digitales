#include <rss/include/canal.h>

namespace medios::rss {

canal::canal(const std::string & string_uri) :
    respuesta(""),
    peticion_activa(false),
    uri(utility::conversions::to_string_t(string_uri)),
    cliente_canal(uri.scheme() + utility::conversions::to_string_t("://") + uri.host()) {}

canal::~canal() {}

bool canal::historias_ya(std::vector<historia> & historias) {

    std::string rta = "";
    if (this->peticion_activa) {
        return false;
    }
    else {
        rta = this->cliente_canal.request(web::http::methods::GET, this->uri.path()).get().extract_utf8string().get();
    }

    return this->parsear(rta, historias);
}

bool canal::pedir_historias() {

    if (this->peticion_activa) {
        return false;
    }

    this->peticion_activa = true;

    this->tarea_peticion = this->cliente_canal.request(web::http::methods::GET, this->uri.path());
    this->tarea_peticion.then([this](pplx::task<web::http::http_response> tarea) {
        this->respuesta = tarea.get().extract_utf8string().get();
        this->peticion_activa = false;
    });
}

bool canal::historias(std::vector<historia> & historias) {

    if (false == this->tarea_peticion.is_done()) {
        return false;
    }

    return this->parsear(this->respuesta, historias);
}

bool canal::parsear(const std::string & contenido_xml, std::vector<historia> & historias) {
    return true;
}

}