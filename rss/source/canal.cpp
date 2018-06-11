#include <rss/include/canal.h>

namespace medios::rss {

canal::canal(const std::string & string_uri) : uri(utility::conversions::to_string_t(string_uri)), cliente_canal(nullptr) {

    this->cliente_canal = new web::http::client::http_client(uri.scheme() + utility::conversions::to_string_t("://") + uri.host());
}

canal::~canal() {
    delete cliente_canal;
}

bool canal::historias_ya(std::vector<historia> & historias) {
    web::http::http_request http_solicitud(web::http::methods::GET);
    http_solicitud.set_request_uri(this->uri.path());
    http_solicitud.headers().add(utility::conversions::to_string_t("Accept"), utility::conversions::to_string_t("text/html,application/xhtml+xml,application/xml;charset=utf-8"));


    web::http::http_response http_respuesta = this->cliente_canal->request(http_solicitud).get();

    return this->parsear(http_respuesta.extract_utf8string().get(), historias);
}

bool canal::pedir_historias() {
    return false;
}

bool canal::historias(std::vector<historia>& historias) {
    return false;
}

bool canal::parsear(const std::string & contenido_xml, std::vector<historia> & historias) {
    return false;
}

}