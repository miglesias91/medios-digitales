
// catch2
#include <catch.hpp>

// rss
#include <rss/include/canal.h>

TEST_CASE("pedir_feeds_ya", "canal1") {

    medios::rss::canal clarin_politica("https://www.clarin.com/rss/politica/");

    std::vector<medios::rss::historia> historias;
    REQUIRE(true == clarin_politica.historias_ya(historias));
}

TEST_CASE("pedir_feeds_asincronico", "canal2") {

    medios::rss::canal clarin_politica("https://www.clarin.com/rss/politica/");
    medios::rss::canal clarin_economia("https://www.clarin.com/rss/economia/");
    medios::rss::canal clarin_lo_ultimo("https://www.clarin.com/rss/lo-ultimo/");

    clarin_politica.pedir_historias();
    clarin_economia.pedir_historias();
    clarin_lo_ultimo.pedir_historias();

    std::vector<medios::rss::historia> historias_politica;
    std::vector<medios::rss::historia> historias_economia;
    std::vector<medios::rss::historia> historias_lo_ultimo;

    REQUIRE(false == clarin_politica.historias(historias_politica));
    REQUIRE(false == clarin_economia.historias(historias_economia));
    REQUIRE(false == clarin_lo_ultimo.historias(historias_lo_ultimo));

    REQUIRE(true == clarin_politica.historias_ya(historias_politica));
    REQUIRE(true == clarin_economia.historias_ya(historias_economia));
    REQUIRE(true == clarin_lo_ultimo.historias_ya(historias_lo_ultimo));
}

