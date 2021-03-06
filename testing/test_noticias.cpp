
// catch2
#include <catch.hpp>

// utiles
#include <utiles/include/FuncionesSistemaArchivos.h>

// feed
#include <feed/include/historia.h>

// noticias
#include <noticias/include/config.h>
#include <noticias/include/lector.h>
#include <noticias/include/clarin.h>
#include <noticias/include/la_nacion.h>
#include <noticias/include/infobae.h>
#include <noticias/include/paginadoce.h>
#include <noticias/include/eldestape.h>

TEST_CASE("levantar_config", "noticias[.]") {
    medios::noticias::config::levantar("config_noticias.json");

    REQUIRE("politica" == medios::noticias::config::clarin.canales[0].categoria);
    REQUIRE("https://www.clarin.com/rss/politica/" == medios::noticias::config::clarin.canales[0].link);

    REQUIRE("economia" == medios::noticias::config::la_nacion.canales[1].categoria);
    REQUIRE("http://contenidos.lanacion.com.ar/herramientas/rss-categoria_id=272" == medios::noticias::config::la_nacion.canales[1].link);

    REQUIRE("todo" == medios::noticias::config::infobae.canales[0].categoria);
    REQUIRE("https://www.infobae.com/feeds/rss/" == medios::noticias::config::infobae.canales[0].link);
}

TEST_CASE("extraer_elemento", "noticias[.]") {
    std::string elemento_html_vacio = "0123456789<div class=\"category-wrapper\"></div>0123456789";
    std::string elemento_html_con_contenido = "0123456789<div class=\"category-wrapper\">0123546789</div>0123456789";

    medios::noticias::clarin clarinete;

    std::string elemento = "";
    clarinete.extraer_elemento_xml(elemento_html_con_contenido, "div", "<div class=\"category-wrapper\">", &elemento);

    std::string elemento_vacio = "";
    clarinete.extraer_elemento_xml(elemento_html_vacio, "div", "<div class=\"category-wrapper\">", &elemento_vacio);


}

TEST_CASE("leer_noticia_clarin", "noticias[.]") {

    std::string contenido_html = "";
    herramientas::utiles::FuncionesSistemaArchivos::leer("noticia_clarin.html", contenido_html);

    medios::feed::historia historia("titulo", "politica","link", herramientas::utiles::Fecha::getFechaActual(), contenido_html);

    medios::noticias::clarin el_gran_diario_argentino;

    el_gran_diario_argentino.nueva_noticia(historia);
}

TEST_CASE("leer_noticia_la_nacion", "noticias[.]") {

    std::string contenido_html = "";
    herramientas::utiles::FuncionesSistemaArchivos::leer("noticia_la_nacion.html", contenido_html);

    medios::feed::historia historia("titulo", "politica", "link", herramientas::utiles::Fecha::getFechaActual(), contenido_html);

    medios::noticias::la_nacion el_diario_de_mitre;

    el_diario_de_mitre.nueva_noticia(historia);
}

TEST_CASE("leer_noticia_infobae", "noticias[.]") {

    std::string contenido_html = "";
    herramientas::utiles::FuncionesSistemaArchivos::leer("noticia_infobae.html", contenido_html);

    medios::feed::historia historia("titulo", "todo", "https://www.infobae.com/politica/2018/06/20/rindieron-homenaje-a-dante-caputo-en-washington/", herramientas::utiles::Fecha::getFechaActual(), contenido_html);

    medios::noticias::infobae infobae;

    infobae.nueva_noticia(historia);
}

TEST_CASE("leer_noticia_extrania_paginadoce", "noticias[.]") {

    std::string contenido_html = "";
    herramientas::utiles::FuncionesSistemaArchivos::leer("noticia_extrania_paginadoce.html", contenido_html);

    medios::feed::historia historia("titulo", "todo", "https://www.infobae.com/politica/2018/06/20/rindieron-homenaje-a-dante-caputo-en-washington/", herramientas::utiles::Fecha::getFechaActual(), contenido_html);

    medios::noticias::paginadoce pagina;

    pagina.nueva_noticia(historia, "");
}

TEST_CASE("leer_clarin", "noticias") {
   
    medios::noticias::lector lector_de_noticias;

    medios::noticias::clarin el_gran_diario_argentino;

    lector_de_noticias.leer(&el_gran_diario_argentino);
}

TEST_CASE("leer_la_nacion", "noticias[.]") {

    medios::noticias::lector lector_de_noticias;

    medios::noticias::la_nacion el_diario_de_mitre;

    lector_de_noticias.leer(&el_diario_de_mitre);
}

TEST_CASE("leer_infobae", "noticias[.]") {

    medios::noticias::lector lector_de_noticias;

    medios::noticias::infobae infobae;

    lector_de_noticias.leer(&infobae);
}

TEST_CASE("leer_infobae_fechas", "noticias[.]") {

    medios::noticias::lector lector_de_noticias;

    medios::noticias::infobae infobae;

    // le pido que me traiga noticia a partir de la fecha de ma�ana, entonces NO DEBERIA tener ninguna noticia.
    herramientas::utiles::Fecha desde = herramientas::utiles::Fecha::getFechaActual();
    desde.setDia(desde.getDia() + 1);

    lector_de_noticias.leer(&infobae, desde);

    std::vector<medios::noticias::noticia*> noticias;
    infobae.noticias(&noticias);

    REQUIRE(0 == noticias.size());
}

TEST_CASE("leer_pagina12", "noticias[.]") {

    medios::noticias::lector lector_de_noticias;

    medios::noticias::paginadoce pagina;

    lector_de_noticias.leer(&pagina);
}

TEST_CASE("leer_eldestape", "noticias[.]") {

    medios::noticias::lector lector_de_noticias;

    medios::noticias::eldestape el_destape_web;

    lector_de_noticias.leer(&el_destape_web);
}