#include <noticias/include/paginadoce.h>

// utiles
#include <utiles/include/FuncionesString.h>

// pugixml
#include <pugixml.hpp>

// utiles
#include <utiles/include/FuncionesString.h>
#include <utiles/include/FuncionesSistemaArchivos.h>
#include <utiles/include/Json.h>

// feed
#include <feed/include/urlset.h>

// noticias
#include <noticias/include/config.h>

namespace medios { namespace noticias {

paginadoce::paginadoce() : portal() {
    for (config_canal config : config::paginadoce.canales) {
        std::unordered_map<std::string, std::string> subcategorias;
        for(config_subcategoria config_subcatego : config.subcategorias) {
            subcategorias[config_subcatego.subcategoria] = config_subcatego.recurso_url;
        }
        feed::canal * canal = new medios::feed::urlset_paginadoce(config.link, config.categoria, subcategorias);
        this->canales_portal[canal->seccion()] = canal;
    }
}

paginadoce::~paginadoce() {}

std::string paginadoce::web() {
    return config::paginadoce.web;
}

portal * paginadoce::clon() {
    portal * nuevo_portal = new paginadoce();
    nuevo_portal->nuevas_noticias(this->noticias_portal);
    return nuevo_portal;
}

bool paginadoce::extraer_contenido_de_html(const std::string & contenido_html, std::string * contenido) {

    std::string elemento_nota = "";
    this->extraer_elemento_xml(contenido_html, "div", "<div class=\"article-text\">", &elemento_nota);
    this->eliminar_etiqueta_xml(&elemento_nota, "strong");
    this->eliminar_etiqueta_xml(&elemento_nota, "br");
    this->eliminar_etiqueta_xml(&elemento_nota, "a");
    this->eliminar_etiqueta_xml(&elemento_nota, "em");
    herramientas::utiles::FuncionesString::eliminarOcurrencias(elemento_nota, "&nbsp;");

    std::vector<std::string> elementos_p;
    this->extraer_elementos_xml(elemento_nota, "p", "<p", &elementos_p);

    if (elementos_p.empty()) {
        return false;
    }

    *contenido = herramientas::utiles::FuncionesString::unir(elementos_p, "", "");

    return true;
}

bool paginadoce::nueva_noticia(const medios::feed::historia & historia, const std::string & seccion) {

    noticia * nueva_noticia = new noticia(historia.titulo(), "", seccion, historia.fecha());

    std::string contenido_noticia = "";
    if (false == this->extraer_contenido_de_html(historia.html(), &contenido_noticia)) {
        delete nueva_noticia;
        return false;
    }
    this->extraer_datos_de_historia(historia.html(), nueva_noticia);
    nueva_noticia->contenido(contenido_noticia);

    this->noticias_portal[seccion].push_back(nueva_noticia);

    return true;
}

bool paginadoce::extraer_datos_de_historia(const std::string & contenido_html, noticia * noti) {

    std::string titulo;
    this->extraer_elemento_xml(contenido_html, "div", "<div class=\"article-title\">", &titulo);
    titulo.erase(titulo.begin(), titulo.begin() + std::string("<div class=\"article-title\">").size());
    titulo.erase(titulo.end() - std::string("</div>").size() + 1, titulo.end() );

    noti->titulo(titulo);
    return true;
}

}
}