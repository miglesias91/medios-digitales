
// catch2
#include <catch.hpp>

// utiles
#include <utiles/include/FuncionesSistemaArchivos.h>

// rss
#include <feed/include/rss.h>
#include <feed/include/atom.h>

TEST_CASE("leer_atom", "feed[.]") {

    medios::feed::atom lanacion_politica("http://contenidos.lanacion.com.ar/herramientas/rss-categoria_id=30", "politica");

    std::string contenido = "";
    herramientas::utiles::FuncionesSistemaArchivos::leer("feed_la_nacion.txt", contenido);

    std::vector<medios::feed::historia*> historias;
    lanacion_politica.parsear(contenido, historias, herramientas::utiles::Fecha(0,0,0), herramientas::utiles::Fecha::getFechaActual());
}

TEST_CASE("pedir_historias_ya_rss", "feed[.]") {

    medios::feed::rss clarin_politica("https://www.clarin.com/rss/politica/", "politica");

    std::vector<medios::feed::historia*> historias;
    REQUIRE(true == clarin_politica.historias_ya(historias));

    std::for_each(historias.begin(), historias.end(), [](medios::feed::historia * historia) { delete historia; });
}

TEST_CASE("pedir_historias_ya_atom", "feed[.]") {

    medios::feed::atom lanacion_politica("http://contenidos.lanacion.com.ar/herramientas/rss-categoria_id=30", "politica");

    std::vector<medios::feed::historia*> historias;
    REQUIRE(true == lanacion_politica.historias_ya(historias));

    std::for_each(historias.begin(), historias.end(), [](medios::feed::historia * historia) { delete historia; });
}

TEST_CASE("pedir_historias_asincronico_rss", "feed[.]") {

    medios::feed::rss clarin_politica("https://www.clarin.com/rss/politica/", "politica");
    medios::feed::rss clarin_economia("https://www.clarin.com/rss/economia/", "economia");
    medios::feed::rss clarin_lo_ultimo("https://www.clarin.com/rss/lo-ultimo/", "lo ultimo");

    clarin_politica.pedir_historias();
    clarin_economia.pedir_historias();
    clarin_lo_ultimo.pedir_historias();

    std::vector<medios::feed::historia*> historias_politica;
    std::vector<medios::feed::historia*> historias_economia;
    std::vector<medios::feed::historia*> historias_lo_ultimo;

    REQUIRE(false == clarin_politica.historias(historias_politica));
    REQUIRE(false == clarin_economia.historias(historias_economia));
    REQUIRE(false == clarin_lo_ultimo.historias(historias_lo_ultimo));

    REQUIRE(true == clarin_politica.historias_ya(historias_politica));
    REQUIRE(true == clarin_economia.historias_ya(historias_economia));
    REQUIRE(true == clarin_lo_ultimo.historias_ya(historias_lo_ultimo));

    std::for_each(historias_politica.begin(), historias_politica.end(), [](medios::feed::historia * historia) { delete historia; });
    std::for_each(historias_economia.begin(), historias_economia.end(), [](medios::feed::historia * historia) { delete historia; });
    std::for_each(historias_lo_ultimo.begin(), historias_lo_ultimo.end(), [](medios::feed::historia * historia) { delete historia; });
}

TEST_CASE("pedir_historias_asincronico_atom", "feed[.]") {

    medios::feed::atom lanacion_politica("http://contenidos.lanacion.com.ar/herramientas/rss-categoria_id=30", "politica");
    medios::feed::atom lanacion_economia("http://contenidos.lanacion.com.ar/herramientas/rss-categoria_id=272", "economia");
    medios::feed::atom lanacion_lo_ultimo("http://contenidos.lanacion.com.ar/herramientas/rss-origen=2", "lo ultimo");

    lanacion_politica.pedir_historias();
    lanacion_economia.pedir_historias();
    lanacion_lo_ultimo.pedir_historias();

    std::vector<medios::feed::historia*> historias_politica;
    std::vector<medios::feed::historia*> historias_economia;
    std::vector<medios::feed::historia*> historias_lo_ultimo;

    REQUIRE(false == lanacion_politica.historias(historias_politica));
    REQUIRE(false == lanacion_economia.historias(historias_economia));
    REQUIRE(false == lanacion_lo_ultimo.historias(historias_lo_ultimo));

    REQUIRE(true == lanacion_politica.historias_ya(historias_politica));
    REQUIRE(true == lanacion_economia.historias_ya(historias_economia));
    REQUIRE(true == lanacion_lo_ultimo.historias_ya(historias_lo_ultimo));

    std::for_each(historias_politica.begin(), historias_politica.end(), [](medios::feed::historia * historia) { delete historia; });
    std::for_each(historias_economia.begin(), historias_economia.end(), [](medios::feed::historia * historia) { delete historia; });
    std::for_each(historias_lo_ultimo.begin(), historias_lo_ultimo.end(), [](medios::feed::historia * historia) { delete historia; });
}