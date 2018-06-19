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

bool portal::extraer_elemento_xml(const std::string & contenido_html, const std::string & nombre_elemento, const std::string & etiqueta_inicial, std::string & elemento_extraido) {
    size_t primer_comienzo = contenido_html.find(etiqueta_inicial);

    if (primer_comienzo == SIZE_MAX) {
        return false;
    }

    size_t tamanio_tag = std::string("</" + nombre_elemento).size();

    size_t pos_ultimo_comienzo_elemento = contenido_html.find("<" + nombre_elemento, primer_comienzo + tamanio_tag);
    size_t pos_ultimo_fin_elemento = contenido_html.find("</" + nombre_elemento, primer_comienzo);

    while (pos_ultimo_fin_elemento > pos_ultimo_comienzo_elemento) {
        // si entra al if, entonces quiere decir que se abrio otro elemento "span" en el medio
        pos_ultimo_comienzo_elemento = contenido_html.find("<" + nombre_elemento, pos_ultimo_comienzo_elemento + tamanio_tag);
        pos_ultimo_fin_elemento = contenido_html.find("</" + nombre_elemento, pos_ultimo_fin_elemento + tamanio_tag);  // actualizo la posicion del ultimo span encontrado.
    }

    if (pos_ultimo_fin_elemento == SIZE_MAX) {
        return false;
    }

    elemento_extraido = contenido_html.substr(primer_comienzo, pos_ultimo_fin_elemento + tamanio_tag - primer_comienzo);

    return true;
}

bool portal::eliminar_elemento_xml(std::string & contenido_html, const std::string & nombre_elemento, const std::string & etiqueta_inicial) {
    size_t primer_comienzo = contenido_html.find(etiqueta_inicial);

    if (primer_comienzo == SIZE_MAX) {
        return false;
    }

    size_t tamanio_tag = std::string("</" + nombre_elemento).size();

    size_t pos_ultimo_comienzo_elemento = contenido_html.find("<" + nombre_elemento, primer_comienzo + tamanio_tag);
    size_t pos_ultimo_fin_elemento = contenido_html.find("</" + nombre_elemento, primer_comienzo);

    while (pos_ultimo_fin_elemento > pos_ultimo_comienzo_elemento) {
        // si entra al if, entonces quiere decir que se abrio otro elemento "span" en el medio
        pos_ultimo_comienzo_elemento = contenido_html.find("<" + nombre_elemento, pos_ultimo_comienzo_elemento + tamanio_tag);
        pos_ultimo_fin_elemento = contenido_html.find("</" + nombre_elemento, pos_ultimo_fin_elemento + tamanio_tag);  // actualizo la posicion del ultimo span encontrado.
    }

    if (pos_ultimo_fin_elemento == SIZE_MAX) {
        return false;
    }

    contenido_html.erase(primer_comienzo, pos_ultimo_fin_elemento + tamanio_tag - primer_comienzo);

    return true;
}

}