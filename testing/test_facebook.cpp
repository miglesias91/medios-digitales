
// catch2
#include <catch.hpp>

// facebook
#include <facebook/include/Aplicacion.h>

TEST_CASE("descargar_publicaciones", "facebook[.]") {
    medios::facebook::consumidor_api * consumidor_api_facebook = new medios::facebook::consumidor_api("929798640478438", "f36e906bf6b8445ac3ee53e95ac303a7");

    medios::facebook::aplicacion app(consumidor_api_facebook);

    medios::facebook::Pagina tn("todo-noticias");

    std::vector<medios::facebook::Publicacion*> publicaciones = app.leer(&tn);

    REQUIRE(100 == publicaciones.size());
}

TEST_CASE("parsear_publicaciones", "facebook") {
    std::ifstream archivo_tweets("publicaciones_de_prueba.txt");

    std::stringstream sstream;
    sstream << archivo_tweets.rdbuf();

    std::string string_tweets(sstream.str());

    herramientas::utiles::Json json_publicaciones(string_tweets);

    std::vector<herramientas::utiles::Json*> publicaciones_json = json_publicaciones.getAtributoArrayJson("data");

    std::vector<medios::facebook::Publicacion*> publicaciones;
    medios::facebook::Publicacion* nueva_publicacion = NULL;
    medios::facebook::aplicacion app;
    for (std::vector<herramientas::utiles::Json*>::iterator it = publicaciones_json.begin(); it != publicaciones_json.end(); it++) {
        nueva_publicacion = new medios::facebook::Publicacion();
        medios::facebook::aplicacion::parsear(*it, nueva_publicacion);

        publicaciones.push_back(nueva_publicacion);
    }

    unsigned long long int id_parseado_publicacion_1 = publicaciones[0]->getIdPublicacion();
    unsigned long long int id_parseado_pagina_1 = publicaciones[0]->getIdPagina();
    std::string texto_parseado_publicacion_1 = publicaciones[0]->getTextoPublicacion();
    herramientas::utiles::Fecha fecha_de_creacion_parseada_publicacion_1 = publicaciones[0]->getFechaCreacion();

    unsigned long long int id_correcto_publicacion_1 = 522759367889906;
    unsigned long long int id_correcto_pagina_1 = 116053261893854;
    std::string texto_correcto_publicacion_1 = u8"HISTÓRICO: La ONU aprobó la iniciativa argentina sobre el marco legal para la reestructuración de deuda. #SoberaníaEconómica.";
    herramientas::utiles::Fecha fecha_de_creacion_correcta_publicacion_1(10, 9, 2015, 20, 33, 54);

    for (std::vector<medios::facebook::Publicacion*>::iterator it = publicaciones.begin(); it != publicaciones.end(); it++) {
        delete *it;
    }

    REQUIRE(id_correcto_publicacion_1 == id_parseado_publicacion_1);
    REQUIRE(texto_correcto_publicacion_1 == texto_parseado_publicacion_1);
    REQUIRE(true == (fecha_de_creacion_correcta_publicacion_1 == fecha_de_creacion_parseada_publicacion_1));
    REQUIRE(id_correcto_pagina_1 == id_parseado_pagina_1);
}