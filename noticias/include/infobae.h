#pragma once

// utiles
#include <utiles/include/FuncionesString.h>

// feed
#include <feed/include/rss.h>

// noticias
#include <noticias/include/portal.h>

namespace medios {
    namespace feed {

    class rss_infobae : public medios::feed::rss {

    public:
        rss_infobae(const std::string & uri, const std::string & seccion, const std::unordered_map<std::string, std::string> & subcategorias) : medios::feed::rss(uri, seccion, subcategorias) {};
        virtual ~rss_infobae() {};

    protected:
        virtual bool parsear(const std::string & contenido_xml, std::vector<historia*> & historias,
            const herramientas::utiles::Fecha & desde = herramientas::utiles::Fecha(0, 0, 0),
            const herramientas::utiles::Fecha & hasta = herramientas::utiles::Fecha::getFechaActual()) {
            pugi::xml_document xml_feed;
            pugi::xml_parse_result resultado = xml_feed.load_string(contenido_xml.c_str());

            uint32_t cantidad_total_de_historias = 0;
            uint32_t cantidad_de_historias_descargadas = 0;
            for (pugi::xml_node item : this->historias_xml(xml_feed)) {

                historia * nueva = new historia();
                this->parsear_historia(item, nueva);
                if (false == this->reconocer_subcategoria(nueva)) {  // si no pertenece a ninguna subcategoria, entonces descarto la noticia.
                    delete nueva;
                    continue;
                }

                herramientas::utiles::Fecha fecha_origi = nueva->fecha();
                fecha_origi -= std::chrono::hours(3);  // ajusto xq las fechas de infobae estan adelantadas 3 horas.
                nueva->fecha(fecha_origi);

                if (desde <= nueva->fecha() && nueva->fecha() <= hasta) {
                    nueva->html(nueva->contenido());
                    historias.push_back(nueva);
                    cantidad_total_de_historias++;
                }
                else {
                    delete nueva;
                }
            }

            return true;
        }

        virtual bool reconocer_subcategoria(historia * histo) {
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

class infobae : public portal {
public:
    infobae();
    virtual ~infobae();

    // virtual bool nueva_noticia(const medios::feed::historia & historia, const std::string & seccion);

    virtual std::string web();

    virtual portal * clon();

protected:
    virtual bool extraer_contenido_de_html(const std::string & contenido_html, std::string * contenido);

private:
    bool reconocer_seccion(const std::string & url, std::string * seccion);
};

    };
};