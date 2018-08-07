#pragma once

// utiles
#include <utiles/include/FuncionesString.h>

// feed
#include <feed/include/urlset.h>

// noticias
#include <noticias/include/portal.h>

namespace medios {
    namespace feed {

        class urlset_pagina12 : public medios::feed::urlset {

        public:
            urlset_pagina12(const std::string & uri, const std::string & seccion, const std::unordered_map<std::string, std::string> & subcategorias) : medios::feed::rss(uri, seccion, subcategorias) {};
            virtual ~urlset_pagina12() {};

        protected:
            virtual bool parsear_historia(const pugi::xml_node & xml_historia, historia * histo) override {
                std::string link = xml_historia.child_value("loc");

                std::string titulo = xml_historia.child("news:news").child_value("news:title");
                std::string string_fecha = xml_historia.child("news:news").child_value("news:publication_date");
                std::string contenido = xml_historia.child_value("content:encoded");

                herramientas::utiles::Fecha fecha;
                herramientas::utiles::Fecha::parsear(string_fecha, "%Y-%m-%dT%H:%M:%S", &fecha);

                histo->titulo(titulo);
                histo->fecha(fecha);
                histo->link(link);
                histo->contenido(contenido);
                histo->seccion(this->seccion());

                if (false == this->reconocer_subcategoria(xml_historia.child_value("news:keywords"), histo)) {  // si no pertenece a ninguna subcategoria, entonces descarto la noticia.
                    return false;
                }

                return true;
            }

            virtual bool reconocer_subcategoria(const std::string & keywords, historia * histo) {
                web::uri url(utility::conversions::to_string_t(histo->link()));
                std::string path = utility::conversions::to_utf8string(url.path());

                std::vector<std::string> recursos = herramientas::utiles::FuncionesString::separar(path, "/");
                recursos.erase(recursos.begin());  // elimino el primero porque me queda vacio.
                recursos.erase(recursos.end() - 4, recursos.end());  // elimino los ultimos recursos.

                std::string string_recursos = herramientas::utiles::FuncionesString::unir(recursos, "/");

                for (std::pair<std::string, std::string> subcategoria_recurso : this->subcategorias) {
                    if (string_recursos == subcategoria_recurso.second) {
                        histo->seccion(subcategoria_recurso.first);
                        return true;
                    }
                }

                return false;
            }
        };
    }
}

namespace medios {
    namespace noticias {

class pagina12 : public portal {
public:
    pagina12();
    virtual ~pagina12();

    virtual std::string web();

    virtual portal * clon();

protected:
    virtual bool extraer_contenido_de_html(const std::string & contenido_html, std::string * contenido) override;
    virtual bool nueva_noticia(const medios::feed::historia & historia, const std::string & seccion) override;

private:
    bool extraer_datos_de_historia(const std::string & contenido_html, noticia * noti);
};

    };
};