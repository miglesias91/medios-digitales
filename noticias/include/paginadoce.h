#pragma once

// utiles
#include <utiles/include/FuncionesString.h>

// feed
#include <feed/include/urlset.h>

// noticias
#include <noticias/include/portal.h>

namespace medios {
    namespace feed {

        class urlset_paginadoce : public medios::feed::urlset {

        public:
            urlset_paginadoce(const std::string & uri, const std::string & seccion, const std::unordered_map<std::string, std::string> & subcategorias) : medios::feed::urlset(uri, seccion, subcategorias) {};
            virtual ~urlset_paginadoce() {};

        protected:
            virtual bool parsear_historia(const pugi::xml_node & xml_historia, historia * histo) {
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

                if (false == this->reconocer_subcategoria(xml_historia.child("news:news").child_value("news:keywords"), histo)) {  // si no pertenece a ninguna subcategoria, entonces descarto la noticia.
                    return false;
                }

                return true;
            }

            virtual bool reconocer_subcategoria(const std::string & string_keywords, historia * histo) {
                std::string string_keywords_depurado = string_keywords;
                herramientas::utiles::FuncionesString::eliminarOcurrencias(string_keywords_depurado, " ");

                std::vector<std::string> keywords = herramientas::utiles::FuncionesString::separar(string_keywords_depurado, ",");

                std::string seccion = keywords[1];
                herramientas::utiles::FuncionesString::reemplazarOcurrencias(seccion, u8"á", "a");
                herramientas::utiles::FuncionesString::reemplazarOcurrencias(seccion, u8"é", "e");
                herramientas::utiles::FuncionesString::reemplazarOcurrencias(seccion, u8"í", "i");
                herramientas::utiles::FuncionesString::reemplazarOcurrencias(seccion, u8"ó", "o");
                herramientas::utiles::FuncionesString::reemplazarOcurrencias(seccion, u8"ú", "u");
                herramientas::utiles::FuncionesString::reemplazarOcurrencias(seccion, u8"Á", "A");
                herramientas::utiles::FuncionesString::reemplazarOcurrencias(seccion, u8"É", "E");
                herramientas::utiles::FuncionesString::reemplazarOcurrencias(seccion, u8"Í", "I");
                herramientas::utiles::FuncionesString::reemplazarOcurrencias(seccion, u8"Ó", "O");
                herramientas::utiles::FuncionesString::reemplazarOcurrencias(seccion, u8"Ú", "U");
                herramientas::utiles::FuncionesString::reemplazarOcurrencias(seccion, u8"ý", "y");
                herramientas::utiles::FuncionesString::reemplazarOcurrencias(seccion, u8"Ý", "Y");

                herramientas::utiles::FuncionesString::todoMinuscula(seccion);
                for (std::pair<std::string, std::string> subcategoria_recurso : this->subcategorias()) {
                    std::string subcategoria_depurada = subcategoria_recurso.second;
                    herramientas::utiles::FuncionesString::eliminarOcurrencias(subcategoria_depurada, " ");
                    herramientas::utiles::FuncionesString::todoMinuscula(subcategoria_depurada);
                    if (seccion == subcategoria_depurada) {
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

class paginadoce : public portal {
public:
    paginadoce();
    virtual ~paginadoce();

    virtual std::string web();

    virtual portal * clon();

    virtual bool extraer_contenido_de_html(const std::string & contenido_html, std::string * contenido) override;

protected:
    virtual bool nueva_noticia(const medios::feed::historia & historia, const std::string & seccion) override;

private:
    bool extraer_datos_de_historia(const std::string & contenido_html, noticia * noti);
};

    };
};