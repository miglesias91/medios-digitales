
// catch2
#include <catch.hpp>

// utiles
#include <utiles/include/FuncionesSistemaArchivos.h>

// feed
#include <feed/include/historia.h>

// noticias
#include <noticias/include/lector.h>
#include <noticias/include/clarin.h>
#include <noticias/include/la_nacion.h>

TEST_CASE("leer_noticia_clarin", "noticias[.]") {

    std::string contenido_html = "";
    herramientas::utiles::FuncionesSistemaArchivos::leer("noticia_clarin.html", contenido_html);

    medios::feed::historia historia("titulo", "link", herramientas::utiles::Fecha::getFechaActual(), contenido_html);

    medios::noticias::clarin el_gran_diario_argentino;

    el_gran_diario_argentino.nueva_noticia(historia, "politica");
}

TEST_CASE("leer_noticia_la_nacion", "noticias") {

    std::string contenido_html = "";
    herramientas::utiles::FuncionesSistemaArchivos::leer("noticia_la_nacion.html", contenido_html);

    medios::feed::historia historia("titulo", "link", herramientas::utiles::Fecha::getFechaActual(), contenido_html);

    medios::noticias::la_nacion el_diario_de_mitre;

    el_diario_de_mitre.nueva_noticia(historia, "politica");
}

TEST_CASE("leer_clarin", "noticias[.]") {
   
    medios::noticias::lector lector_de_noticias;

    medios::noticias::clarin el_gran_diario_argentino;

    lector_de_noticias.leer(&el_gran_diario_argentino);

}

TEST_CASE("leer_la_nacion", "noticias[.]") {

    medios::noticias::lector lector_de_noticias;

    medios::noticias::la_nacion el_diario_de_mitre;

    lector_de_noticias.leer(&el_diario_de_mitre);

}