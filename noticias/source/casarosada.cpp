#include <noticias/include/casarosada.h>

// utiles
#include <utiles/include/FuncionesString.h>

// pugixml
#include <pugixml.hpp>

// utiles
#include <utiles/include/FuncionesString.h>
#include <utiles/include/FuncionesSistemaArchivos.h>
#include <utiles/include/Json.h>

// feed
#include <feed/include/rss.h>

// noticias
#include <noticias/include/config.h>

namespace medios { namespace noticias {

casarosada::casarosada() : portal() {
    for (config_canal config : config::casarosada.canales) {
        std::unordered_map<std::string, std::string> subcategorias;
        for(config_subcategoria config_subcatego : config.subcategorias) {
            subcategorias[config_subcatego.subcategoria] = config_subcatego.recurso_url;
        }
        uint32_t tamanio_de_pagina = 40;
        uint32_t total_de_paginas = 11;
        for (uint32_t numero_de_pagina = 0; numero_de_pagina < total_de_paginas; numero_de_pagina++) {
            feed::canal * canal = new medios::feed::rss_casarosada(config.link + "&start=" + std::to_string(numero_de_pagina * tamanio_de_pagina), config.categoria, subcategorias);
            this->canales_portal[canal->seccion() + "-pagina" + std::to_string(numero_de_pagina)] = canal;
        }
    }
}

casarosada::~casarosada() {}

std::string casarosada::web() {
    return config::casarosada.web;
}

portal * casarosada::clon() {
    portal * nuevo_portal = new casarosada();
    nuevo_portal->nuevas_noticias(this->noticias_portal);
    return nuevo_portal;
}

bool casarosada::extraer_contenido_de_html(const std::string & contenido_html, std::string * contenido) {

    std::string elemento_nota = "";
    this->extraer_elemento_xml(contenido_html, "div", "<div class=\"body-nota\">", &elemento_nota);
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

}
}