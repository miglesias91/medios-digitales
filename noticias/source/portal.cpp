#include <noticias/include/portal.h>

// stl
#include <algorithm>

namespace medios::noticias {

portal::portal() {}

portal::~portal() {
    std::for_each(this->canales_portal.begin(), this->canales_portal.end(), [](std::pair<std::string, medios::feed::canal*> seccion_canal) { delete seccion_canal.second; });
    std::for_each(this->noticias_portal.begin(), this->noticias_portal.end(), [=](std::pair<std::string, std::vector<noticia*>> noticias_de_seccion) {
        std::for_each(noticias_de_seccion.second.begin(), noticias_de_seccion.second.end(), [=](noticia * noticia_de_seccion) {
            delete noticia_de_seccion;
        });
    });
}

void portal::canal(medios::feed::canal * canal, const std::string & seccion) {
    canal = this->canales_portal[seccion];
}

void portal::canales(std::vector<medios::feed::canal*> * canales) {

    std::for_each(this->canales_portal.begin(), this->canales_portal.end(), [=](std::pair<std::string, medios::feed::canal*> seccion_canal) {
        canales->push_back(seccion_canal.second);
    });
}

bool portal::noticias(std::vector<noticia*> * noticias, const std::string & seccion) {

    if (0 == this->noticias_portal.count(seccion)) {
        return false;
    }

    if (seccion.empty()) {
        std::for_each(this->noticias_portal.begin(), this->noticias_portal.end(), [=](std::pair<std::string, std::vector<noticia*>> noticias_de_seccion) {
            std::for_each(noticias_de_seccion.second.begin(), noticias_de_seccion.second.end(), [=](noticia * noticia_de_seccion) {
                noticias->push_back(noticia_de_seccion);
            });
        });

        return true;
    }

    noticias = &this->noticias_portal[seccion];

    return true;
}

bool portal::nueva_noticia(const medios::feed::historia & historia, const std::string & seccion) {

    noticia * nueva_noticia = new noticia(historia.titulo(), "", seccion, historia.fecha());

    std::string contenido_noticia = "";
    if (false == this->extraer_contenido_de_html(historia.html(), contenido_noticia)) {
        return false;
    }

    nueva_noticia->contenido(contenido_noticia);

    this->noticias_portal[seccion].push_back(nueva_noticia);

    return true;
}

}