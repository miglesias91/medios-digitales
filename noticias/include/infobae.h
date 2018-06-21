#pragma once

// feed
#include <feed/include/rss.h>

// noticias
#include <noticias/include/portal.h>

namespace medios::feed {

    class rss_infobae : public medios::feed::rss {

    public:
        rss_infobae(const std::string & uri, const std::string & seccion) : medios::feed::rss(uri, seccion) {};
        virtual ~rss_infobae() {};

    protected:
        virtual bool parsear(const std::string & contenido_xml, std::vector<historia*> & historias) {
            pugi::xml_document xml_feed;
            pugi::xml_parse_result resultado = xml_feed.load_string(contenido_xml.c_str());

            uint32_t cantidad_total_de_historias = 0;
            uint32_t cantidad_de_historias_descargadas = 0;
            for (pugi::xml_node item : this->historias_xml(xml_feed)) {

                historia * nueva = new historia();
                this->parsear_historia(item, nueva);

                nueva->html(nueva->contenido());

                historias.push_back(nueva);

                cantidad_total_de_historias++;
            }

            return true;
        }
    };
}

namespace medios::noticias {

class infobae : public portal {
public:
    infobae();
    virtual ~infobae();

    virtual bool nueva_noticia(const medios::feed::historia & historia, const std::string & seccion);

protected:
    virtual bool extraer_contenido_de_html(const std::string & contenido_html, std::string & contenido);

private:
    bool reconocer_seccion(const std::string & url, std::string * seccion);
};

};