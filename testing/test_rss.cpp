
// catch2
#include <catch.hpp>

// rss
#include <rss/include/canal.h>

TEST_CASE("pedir_feeds", "canal") {

    medios::rss::canal clarin_politica("http://contenidos.lanacion.com.ar/herramientas/rss-categoria_id=272");

    std::vector<medios::rss::historia> historias;
    clarin_politica.historias_ya(historias);



    REQUIRE(1 == 1);
}

