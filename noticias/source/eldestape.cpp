#include <noticias/include/eldestape.h>

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

eldestape::eldestape() : portal() {
    for (config_canal config : config::eldestape.canales) {
        std::unordered_map<std::string, std::string> subcategorias;
        for(config_subcategoria config_subcatego : config.subcategorias) {
            subcategorias[config_subcatego.subcategoria] = config_subcatego.recurso_url;
        }
        feed::canal * canal = new medios::feed::urlset(config.link, config.categoria, subcategorias);
        this->canales_portal[canal->seccion()] = canal;
    }
}

eldestape::~eldestape() {}

std::string eldestape::web() {
    return config::eldestape.web;
}

portal * eldestape::clon() {
    portal * nuevo_portal = new eldestape();
    nuevo_portal->nuevas_noticias(this->noticias_portal);
    return nuevo_portal;
}

bool eldestape::extraer_contenido_de_html(const std::string & contenido_html, std::string * contenido) {

    std::string elemento_nota = "";
    this->extraer_elemento_xml(contenido_html, "section", "<section class=\"note-body clearfix\"", &elemento_nota);
    this->eliminar_elemento_xml(&elemento_nota, "time", "<time ");
    this->eliminar_etiqueta_xml(&elemento_nota, "strong");
    this->eliminar_etiqueta_xml(&elemento_nota, "br");
    this->eliminar_etiqueta_xml(&elemento_nota, "a");
    this->eliminar_etiqueta_xml(&elemento_nota, "em");
    herramientas::utiles::FuncionesString::eliminarOcurrencias(elemento_nota, "pic.twitter.com/");
    herramientas::utiles::FuncionesString::eliminarOcurrencias(elemento_nota, "&nbsp;");
    herramientas::utiles::FuncionesString::reemplazarOcurrencias(elemento_nota, "&aacute;", "a");
    herramientas::utiles::FuncionesString::reemplazarOcurrencias(elemento_nota, "&eacute;", "e");
    herramientas::utiles::FuncionesString::reemplazarOcurrencias(elemento_nota, "&iacute;", "i");
    herramientas::utiles::FuncionesString::reemplazarOcurrencias(elemento_nota, "&oacute;", "o");
    herramientas::utiles::FuncionesString::reemplazarOcurrencias(elemento_nota, "&uacute;", "u");
    herramientas::utiles::FuncionesString::reemplazarOcurrencias(elemento_nota, "&Aacute;", "A");
    herramientas::utiles::FuncionesString::reemplazarOcurrencias(elemento_nota, "&Eacute;", "E");
    herramientas::utiles::FuncionesString::reemplazarOcurrencias(elemento_nota, "&Iacute;", "I");
    herramientas::utiles::FuncionesString::reemplazarOcurrencias(elemento_nota, "&Oacute;", "O");
    herramientas::utiles::FuncionesString::reemplazarOcurrencias(elemento_nota, "&Uacute;", "U");
    herramientas::utiles::FuncionesString::reemplazarOcurrencias(elemento_nota, "&yacute;", "y");
    herramientas::utiles::FuncionesString::reemplazarOcurrencias(elemento_nota, "&Yacute;", "Y");
    herramientas::utiles::FuncionesString::reemplazarOcurrencias(elemento_nota, "&ntilde;", "n");
    herramientas::utiles::FuncionesString::eliminarOcurrencias(elemento_nota, "&ldquo;");
    herramientas::utiles::FuncionesString::eliminarOcurrencias(elemento_nota, "&rdquo;");
    herramientas::utiles::FuncionesString::eliminarOcurrencias(elemento_nota, "&uuml;");
    herramientas::utiles::FuncionesString::eliminarOcurrencias(elemento_nota, "<br/>");

    std::vector<std::string> elementos_p;
    this->extraer_elementos_xml(elemento_nota, "p", "<p", &elementos_p);

    if (elementos_p.empty()) {
        return false;
    }

    *contenido = herramientas::utiles::FuncionesString::unir(elementos_p, "", "");

    return true;
}

bool eldestape::nueva_noticia(const medios::feed::historia & historia, const std::string & seccion) {

    noticia * nueva_noticia = new noticia(historia.titulo(), "", seccion, historia.fecha());

    std::string contenido_noticia = "";
    if (false == this->extraer_contenido_de_html(historia.html(), &contenido_noticia)) {
        delete nueva_noticia;
        return false;
    }

    if (false == this->extraer_datos_de_historia(historia.html(), nueva_noticia)) {
        delete nueva_noticia;
        return false;
    }

    nueva_noticia->contenido(contenido_noticia);

    this->noticias_portal[nueva_noticia->seccion()].push_back(nueva_noticia);

    return true;
}
bool eldestape::extraer_datos_de_historia(const std::string & contenido_html, noticia * noti) {
    //std::string titulo;
    //this->extraer_elemento_xml(contenido_html, "h1", "<h1 class=\"title\">", &titulo);
    //titulo.erase(titulo.begin(), titulo.begin() + std::string("<h1 class=\"title\">").size());
    //titulo.erase(titulo.end() - std::string("</h1>").size(), titulo.end());

    //noti->titulo(titulo);

    std::string seccion = "";
    if (false == this->extraer_elemento_xml(contenido_html, "div", "<div class=\"category-wrapper\">", &seccion)) {  // si no tiene seccion, entonces la descarto.
        return false;
    }
    this->eliminar_etiqueta_xml(&seccion, "a");
    this->eliminar_etiqueta_xml(&seccion, "span");

    seccion.erase(seccion.begin(), seccion.begin() + std::string("<div class=\"category-wrapper\">").size());
    seccion.erase(seccion.end() - std::string("</div>").size(), seccion.end());

    if (seccion.size() == 0) return false;

    herramientas::utiles::FuncionesString::eliminarOcurrencias(seccion, " ");
    std::string seccion_depurada = herramientas::utiles::FuncionesString::separar(seccion, "|")[0];  // el primero de los campos me indica la seccion.

    herramientas::utiles::FuncionesString::reemplazarOcurrencias(seccion_depurada, u8"á", "a");
    herramientas::utiles::FuncionesString::reemplazarOcurrencias(seccion_depurada, u8"é", "e");
    herramientas::utiles::FuncionesString::reemplazarOcurrencias(seccion_depurada, u8"í", "i");
    herramientas::utiles::FuncionesString::reemplazarOcurrencias(seccion_depurada, u8"ó", "o");
    herramientas::utiles::FuncionesString::reemplazarOcurrencias(seccion_depurada, u8"ú", "u");
    herramientas::utiles::FuncionesString::todoMinuscula(seccion_depurada);

    for (std::pair<std::string, std::string> subcategoria_recurso : (this->canales_portal["todo"])->subcategorias()) {
        std::string subcategoria_depurada = subcategoria_recurso.second;
        herramientas::utiles::FuncionesString::eliminarOcurrencias(subcategoria_depurada, " ");
        herramientas::utiles::FuncionesString::todoMinuscula(subcategoria_depurada);
        if (seccion_depurada == subcategoria_depurada) {
            noti->seccion(seccion_depurada);
            return true;
        }
    }
    return false;
}
}
}