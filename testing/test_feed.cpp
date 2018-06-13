
// catch2
#include <catch.hpp>

// rss
#include <feed/include/rss.h>
#include <feed/include/atom.h>

TEST_CASE("pedir_historias_ya_rss", "feed") {

    medios::feed::rss clarin_politica("https://www.clarin.com/rss/politica/");

    std::vector<medios::feed::historia> historias;
    REQUIRE(true == clarin_politica.historias_ya(historias));
}

TEST_CASE("pedir_historias_ya_atom", "feed") {

    medios::feed::atom lanacion_politica("http://contenidos.lanacion.com.ar/herramientas/rss-categoria_id=30");

    std::vector<medios::feed::historia> historias;
    REQUIRE(true == lanacion_politica.historias_ya(historias));
}

TEST_CASE("pedir_historias_asincronico_rss", "feed") {

    medios::feed::rss clarin_politica("https://www.clarin.com/rss/politica/");
    medios::feed::rss clarin_economia("https://www.clarin.com/rss/economia/");
    medios::feed::rss clarin_lo_ultimo("https://www.clarin.com/rss/lo-ultimo/");

    clarin_politica.pedir_historias();
    clarin_economia.pedir_historias();
    clarin_lo_ultimo.pedir_historias();

    std::vector<medios::feed::historia> historias_politica;
    std::vector<medios::feed::historia> historias_economia;
    std::vector<medios::feed::historia> historias_lo_ultimo;

    REQUIRE(false == clarin_politica.historias(historias_politica));
    REQUIRE(false == clarin_economia.historias(historias_economia));
    REQUIRE(false == clarin_lo_ultimo.historias(historias_lo_ultimo));

    REQUIRE(true == clarin_politica.historias_ya(historias_politica));
    REQUIRE(true == clarin_economia.historias_ya(historias_economia));
    REQUIRE(true == clarin_lo_ultimo.historias_ya(historias_lo_ultimo));
}

TEST_CASE("pedir_historias_asincronico_atom", "feed") {

    medios::feed::atom lanacion_politica("http://contenidos.lanacion.com.ar/herramientas/rss-categoria_id=30");
    medios::feed::atom lanacion_economia("http://contenidos.lanacion.com.ar/herramientas/rss-categoria_id=272");
    medios::feed::atom lanacion_lo_ultimo("http://contenidos.lanacion.com.ar/herramientas/rss-origen=2");

    lanacion_politica.pedir_historias();
    lanacion_economia.pedir_historias();
    lanacion_lo_ultimo.pedir_historias();

    std::vector<medios::feed::historia> historias_politica;
    std::vector<medios::feed::historia> historias_economia;
    std::vector<medios::feed::historia> historias_lo_ultimo;

    REQUIRE(false == lanacion_politica.historias(historias_politica));
    REQUIRE(false == lanacion_economia.historias(historias_economia));
    REQUIRE(false == lanacion_lo_ultimo.historias(historias_lo_ultimo));

    REQUIRE(true == lanacion_politica.historias_ya(historias_politica));
    REQUIRE(true == lanacion_economia.historias_ya(historias_economia));
    REQUIRE(true == lanacion_lo_ultimo.historias_ya(historias_lo_ultimo));
}