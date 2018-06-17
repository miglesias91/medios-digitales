
// catch2
#include <catch.hpp>

// noticias
#include <noticias/include/lector.h>
#include <noticias/include/clarin.h>
#include <noticias/include/la_nacion.h>

TEST_CASE("leer_clarin", "noticias") {
   
    medios::noticias::lector lector_de_noticias;

    medios::noticias::clarin el_gran_diario_argentino;

    lector_de_noticias.leer(&el_gran_diario_argentino);

}

TEST_CASE("leer_la_nacion", "noticias") {

    medios::noticias::lector lector_de_noticias;

    medios::noticias::la_nacion el_diario_de_mitre;

    lector_de_noticias.leer(&el_diario_de_mitre);

}