#include <noticias/include/noticia.h>

namespace medios {
    namespace noticias {

noticia::noticia() : titulo_noticia(""), contenido_noticia("") {}

noticia::noticia(const std::string & titulo, const std::string & contenido_noticia, const std::string & seccion, herramientas::utiles::Fecha fecha) :
titulo_noticia(titulo), contenido_noticia(contenido_noticia), seccion_noticia(seccion), fecha_creacion(fecha) {}

noticia::~noticia() {}

void noticia::titulo(const std::string & titulo) {
    this->titulo_noticia = titulo;
}

std::string noticia::titulo() {
    return this->titulo_noticia;
}

void noticia::contenido(const std::string & contenido) {
    this->contenido_noticia = contenido;
}

std::string noticia::contenido() {
    return this->contenido_noticia;
}

void noticia::seccion(const std::string & seccion_noticia) {
    this->seccion_noticia = seccion_noticia;
}

std::string noticia::seccion() {
    return this->seccion_noticia;
}

void noticia::fecha(herramientas::utiles::Fecha fecha) {
    this->fecha_creacion = fecha;
}

herramientas::utiles::Fecha noticia::fecha() {
    return this->fecha_creacion;
}

    }
}