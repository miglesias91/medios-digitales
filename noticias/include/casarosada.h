#pragma once

// feed
#include <feed/include/rss.h>

// noticias
#include <noticias/include/portal.h>

namespace medios {
    namespace feed {

        class rss_casarosada : public medios::feed::rss {

        public:
            rss_casarosada(const std::string & uri, const std::string & seccion, const std::unordered_map<std::string, std::string> & subcategorias) : medios::feed::rss(uri, seccion, subcategorias) {};
            virtual ~rss_casarosada() {};

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
        };
    }
}

namespace medios {
    namespace noticias {

class casarosada : public portal {
public:
    casarosada();
    virtual ~casarosada();

    virtual std::string web();

    virtual portal * clon();

    virtual bool extraer_contenido_de_html(const std::string & contenido_html, std::string * contenido);
protected:
};

    };
};