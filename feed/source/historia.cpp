#include <feed/include/historia.h>

namespace medios::feed {

historia::historia(const std::string & titulo, const std::string & link, const herramientas::utiles::Fecha & fecha, const std::string & contenido_html) :
titulo(titulo), link(link), fecha(fecha) {
    this->html.load_string(contenido_html.c_str());
}

historia::~historia() {
    delete this->html;
}

}