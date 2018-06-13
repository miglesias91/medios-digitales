#include <feed/include/atom.h>

// pugixml
#include <pugixml.hpp>

namespace medios::feed {

atom::atom(const std::string & string_uri) : canal(string_uri) {}

atom::~atom() {}

bool atom::parsear(const std::string & contenido_xml, std::vector<historia> & historias) {

    pugi::xml_document xml_atom;
    pugi::xml_parse_result resultado = xml_atom.load_string(contenido_xml.c_str());

    for (pugi::xml_node entrada : xml_atom.child("feed").children("entry")) {

        std::string titulo = entrada.child_value("title");
        std::string string_fecha = entrada.child_value("updated");
        std::string link = entrada.child_value("id");

        web::uri uri(utility::conversions::to_string_t(link));
        web::http::client::http_client cliente_historia(uri.scheme() + utility::conversions::to_string_t("://") + uri.host());
        cliente_historia.request(web::http::methods::GET, this->uri.path()).then([titulo, string_fecha, link, &historias](pplx::task<web::http::http_response> tarea) {
            std::string string_html = tarea.get().extract_utf8string().get();

            herramientas::utiles::Fecha fecha;

            pugi::xml_document html;
            html.load_string(string_html.c_str());
            historia nueva(titulo, link, fecha, html);

            historias.push_back(nueva);
        });
    }

    return true;
}

}