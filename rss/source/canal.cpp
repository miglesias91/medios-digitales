#include <rss/include/canal.h>

namespace medios::rss {

canal::canal(const std::string & string_uri) : uri(utility::conversions::to_string_t(string_uri)), cliente_canal(nullptr) {

    this->cliente_canal = new web::http::client::http_client(uri);
}

canal::~canal() {
    delete cliente_canal;
}

bool canal::feeds_ya(std::vector<feed> & feeds) {
    web::http::http_request http_solicitud(web::http::methods::GET);
    http_solicitud.set_request_uri(this->uri.path());
    http_solicitud.headers().add(utility::conversions::to_string_t("Accept"), utility::conversions::to_string_t("text/xml"));
    http_solicitud.headers().add(utility::conversions::to_string_t("Content-Type"), utility::conversions::to_string_t("text/xml"));

    web::http::http_response http_respuesta = this->cliente_canal->request(http_solicitud).get();

    return this->parsear(http_respuesta.extract_utf8string().get(), feeds);
}

bool canal::pedir_feeds() {
    return false;
}

bool canal::feeds(std::vector<feed>& feeds) {
    return false;
}

bool canal::parsear(const std::string & contenido_xml, std::vector<feed> & feeds) {
    return false;
}

}