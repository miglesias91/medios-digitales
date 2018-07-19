#pragma once

// stl
#include <unordered_map>

// feed
#include <feed/include/canal.h>

// noticias
#include <noticias/include/noticia.h>

namespace medios {
    namespace noticias {

class portal {
public:
    portal();
    virtual ~portal();

    virtual void canal(medios::feed::canal * canal, const std::string & seccion);

    virtual void canales(std::vector<medios::feed::canal*> * canales);

    virtual bool noticias(std::vector<noticia*> * noticias, const std::string & seccion = "");
    virtual bool noticias(std::unordered_map<std::string, std::vector<noticia*>> * noticias_por_seccion) const;

    virtual bool nueva_noticia(const medios::feed::historia & historia, const std::string & seccion);

    // si no se indica la 'seccion', entonces SE SUPÖNE que la historia ya tiene la seccion asignada.
    virtual bool nueva_noticia(const medios::feed::historia & historia);
    
    virtual void nuevas_noticias(const std::unordered_map<std::string, std::vector<noticia*>> & noticias_portal);

    virtual std::string web() = 0;

    virtual portal * clon() = 0;

protected:
    virtual bool extraer_contenido_de_html(const std::string & contenido_html, std::string * contenido) = 0;

    virtual bool extraer_elemento_xml(const std::string & contenido_html, const std::string & nombre_elemento, const std::string & etiqueta_inicial, std::string * elemento_extraido);

    virtual bool extraer_elementos_xml(const std::string & contenido_html, const std::string & nombre_elemento, const std::string & etiqueta_inicial, std::vector<std::string> * elementos_extraidos);

    virtual bool eliminar_elemento_xml(std::string * contenido_html, const std::string & nombre_elemento, const std::string & etiqueta_inicial);

    virtual bool eliminar_etiqueta_xml(std::string * contenido_html, const std::string & etiqueta);

    std::unordered_map<std::string, medios::feed::canal*> canales_portal;

    std::unordered_map<std::string, std::vector<noticia*>> noticias_portal;
};

    };
};