#include <feed/include/rss.h>

// pugixml
#include <pugixml.hpp>

namespace medios::feed {

rss::rss(const std::string & string_uri) : canal(string_uri) {}

rss::~rss() {}

bool rss::parsear(const std::string & contenido_xml, std::vector<historia>& historias) {

    pugi::xml_document xml_rss;
    pugi::xml_parse_result resultado = xml_rss.load_string(contenido_xml.c_str());

    std::string hola = xml_rss.value();

    for (pugi::xml_node item : xml_rss.child("rss").child("channel").children("item")) {
        
        std::string titulo = item.child_value("title");
        std::string fecha = item.child_value("pubDate");
        std::string link = item.child_value("link");
    }

    return true;
}


}