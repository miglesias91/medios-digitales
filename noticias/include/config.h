#pragma once

// stl
#include <unordered_map>

// utiles
#include <utiles/include/Json.h>
#include <utiles/include/FuncionesSistemaArchivos.h>

namespace medios {
    namespace noticias {

struct config_subcategoria {
    bool levantar(herramientas::utiles::Json* json) {
        this->subcategoria = json->getAtributoValorString("subcategoria");
        this->recurso_url = json->getAtributoValorString("recurso_url");
        return true;
    };
    std::string subcategoria, recurso_url;
};


struct config_canal {
    bool levantar(herramientas::utiles::Json* json) {
        this->categoria = json->getAtributoValorString("categoria");
        this->link = json->getAtributoValorString("link");

        std::vector<herramientas::utiles::Json*> json_subcategorias = json->getAtributoArrayJson("subcategorias");
        for (herramientas::utiles::Json * json_subcategoria : json_subcategorias) {
            config_subcategoria subcategoria;
            subcategoria.levantar(json_subcategoria);
            this->subcategorias.push_back(subcategoria);
            delete json_subcategoria;
        }

        return true;
    };
    std::string categoria, link;
    std::vector<config_subcategoria> subcategorias;
};

struct config_feed {
    bool levantar(herramientas::utiles::Json* json) {
        this->web = json->getAtributoValorString("web");
        std::vector<herramientas::utiles::Json*> json_canales = json->getAtributoArrayJson("canales");

        for (herramientas::utiles::Json * json_canal : json_canales) {
            config_canal canal;
            canal.levantar(json_canal);
            this->canales.push_back(canal);
            delete json_canal;
        }
        return true;
    };
    std::string web;
    std::vector<config_canal> canales;
};

struct config {
    static bool levantar(const std::string & path) {
        std::string config;
        herramientas::utiles::FuncionesSistemaArchivos::leer(path, config);

        herramientas::utiles::Json json(config);

        herramientas::utiles::Json * json_clarin, *json_la_nacion, *json_infobae, *json_paginadoce, *json_eldestape, *json_casarosada;

        json_clarin = json.getAtributoValorJson("clarin");
        json_la_nacion = json.getAtributoValorJson("la nacion");
        json_infobae = json.getAtributoValorJson("infobae");
        json_paginadoce = json.getAtributoValorJson("paginadoce");
        json_eldestape = json.getAtributoValorJson("eldestape");
        json_casarosada = json.getAtributoValorJson("casarosada");

        clarin.levantar(json_clarin);
        la_nacion.levantar(json_la_nacion);
        infobae.levantar(json_infobae);
        paginadoce.levantar(json_paginadoce);
        eldestape.levantar(json_eldestape);
        casarosada.levantar(json_casarosada);

        feeds["clarin"] = clarin;
        feeds["la nacion"] = la_nacion;
        feeds["infobae"] = infobae;
        feeds["paginadoce"] = paginadoce;
        feeds["eldestape"] = eldestape;
        feeds["casarosada"] = casarosada;

        delete json_clarin;
        delete json_la_nacion;
        delete json_infobae;
        delete json_paginadoce;
        delete json_eldestape;
        delete json_casarosada;
        return true;
    };

    static config_feed clarin, la_nacion, infobae, paginadoce, eldestape, casarosada;
    static std::unordered_map<std::string, config_feed> feeds;
};

    };
};