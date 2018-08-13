#pragma once

// stl
#include <algorithm>
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

        if (json.contieneAtributo("clarin")) {
            json_clarin = json.getAtributoValorJson("clarin");
            clarin.levantar(json_clarin);
            feeds["clarin"] = clarin;
            delete json_clarin;
        }

        if (json.contieneAtributo("la nacion")) {
            json_la_nacion = json.getAtributoValorJson("la nacion");
            la_nacion.levantar(json_la_nacion);
            feeds["la nacion"] = la_nacion;
            delete json_la_nacion;
        }

        if (json.contieneAtributo("infobae")) {
            json_infobae = json.getAtributoValorJson("infobae");
            infobae.levantar(json_infobae);
            feeds["infobae"] = infobae;
            delete json_infobae;
        }

        if (json.contieneAtributo("paginadoce")) {
            json_paginadoce = json.getAtributoValorJson("paginadoce");
            paginadoce.levantar(json_paginadoce);
            feeds["paginadoce"] = paginadoce;
            delete json_paginadoce;
        }

        if (json.contieneAtributo("eldestape")) {
            json_eldestape = json.getAtributoValorJson("eldestape");
            eldestape.levantar(json_eldestape);
            feeds["eldestape"] = eldestape;
            delete json_eldestape;
        }

        if (json.contieneAtributo("casarosada")) {
            json_casarosada = json.getAtributoValorJson("casarosada");
            casarosada.levantar(json_casarosada);
            feeds["casarosada"] = casarosada;
            delete json_casarosada;
        }

        return true;
    };

    static config_feed clarin, la_nacion, infobae, paginadoce, eldestape, casarosada;
    static std::unordered_map<std::string, config_feed> feeds;
};

    };
};