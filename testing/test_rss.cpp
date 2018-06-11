
// catch2
#include <catch.hpp>

// rss
#include <rss/include/canal.h>

TEST_CASE("pedir_feeds", "canal") {

    medios::rss::canal clarin_politica("http://contenidos.lanacion.com.ar/herramientas/rss-categoria_id=272");

    std::vector<medios::rss::feed> feeds;
    clarin_politica.feeds_ya(feeds);



    REQUIRE(1 == 1);
}

