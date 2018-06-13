#include <feed/include/canal.h>

namespace medios::feed {

canal::canal(const std::string & string_uri) :
    peticion_activa(false),
    uri(utility::conversions::to_string_t(string_uri)),
    cliente_canal(uri.scheme() + utility::conversions::to_string_t("://") + uri.host()) {}

canal::~canal() {}

bool canal::historias_ya(std::vector<historia> & historias) {

    web::http::http_response rta;
    if (this->peticion_activa) {
        this->tarea_peticion.wait();
        rta = this->tarea_peticion.get();
    }
    else {
        rta = this->cliente_canal.request(web::http::methods::GET, this->uri.path()).get();
    }

    return this->parsear(rta.extract_utf8string().get(), historias);
}

bool canal::pedir_historias() {

    if (this->peticion_activa) {
        return false;
    }

    this->peticion_activa = true;

    this->tarea_peticion = this->cliente_canal.request(web::http::methods::GET, this->uri.path());
    this->tarea_peticion.then([this](pplx::task<web::http::http_response> tarea) {
        this->peticion_activa = false;
    });
    return true;
}

bool canal::historias(std::vector<historia> & historias) {

    if (this->peticion_activa) {
        return false;
    }

    return this->parsear(this->respuesta.extract_utf8string().get(), historias);
}

}