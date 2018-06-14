#include <feed/include/atom.h>

// stl
#include <algorithm>
#include <execution>

// pugixml
#include <pugixml.hpp>

namespace medios::feed {

atom::atom(const std::string & string_uri) : canal(string_uri) {}

atom::~atom() {}

bool atom::parsear(const std::string & contenido_xml, std::vector<historia> & historias) {

    pugi::xml_document xml_atom;
    pugi::xml_parse_result resultado = xml_atom.load_string(contenido_xml.c_str());

    uint32_t cantidad_total_de_historias = 0;
    uint32_t cantidad_de_historias_descargadas = 0;
    for (pugi::xml_node entrada : xml_atom.child("feed").children("entry")) {

        std::string titulo = entrada.child_value("title");
        std::string string_fecha = entrada.child_value("updated");
        std::string link = entrada.child_value("id");

        web::uri uri_historia(utility::conversions::to_string_t(link));
        web::http::client::http_client cliente_historia(uri_historia.scheme() + utility::conversions::to_string_t("://") + uri_historia.host());

        cliente_historia.request(web::http::methods::GET, uri_historia.path()).then([titulo, string_fecha, link, &historias, &cantidad_de_historias_descargadas](pplx::task<web::http::http_response> tarea) {
            try {
                std::cout << "extrayendo html" << std::endl;

                std::string string_html = tarea.get().extract_utf8string().get();

                std::cout << "cargando historia" << std::endl;
                herramientas::utiles::Fecha fecha;
                historia nueva(titulo, link, fecha, string_html);

                historias.push_back(nueva);

                std::cout << "entrys descargados: " << cantidad_de_historias_descargadas << std::endl;
            } catch (const std::exception & e) {
                std::cout << "error: " << e.what() << std::endl;
            }
            cantidad_de_historias_descargadas++;
        });

        cantidad_total_de_historias++;
    }

    while (cantidad_de_historias_descargadas != cantidad_total_de_historias) {
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }

    return true;
}

}