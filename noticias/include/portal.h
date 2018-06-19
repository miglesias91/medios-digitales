#pragma once

// stl
#include <unordered_map>

// feed
#include <feed/include/canal.h>

// noticias
#include <noticias/include/noticia.h>

namespace medios::noticias {

class portal {
public:
    portal();
    virtual ~portal();

    virtual void canal(medios::feed::canal * canal, const std::string & seccion);

    virtual void canales(std::vector<medios::feed::canal*> * canales);

    virtual bool noticias(std::vector<noticia*> * noticias, const std::string & seccion = "");

    virtual bool nueva_noticia(const medios::feed::historia & historia, const std::string & seccion);

protected:
    virtual bool extraer_contenido_de_html(const std::string & contenido_html, std::string & contenido) = 0;

    virtual bool extraer_elemento_xml(const std::string & contenido_html, const std::string & nombre_elemento, const std::string & etiqueta_inicial, std::string & elemento_extraido);

    virtual bool eliminar_elemento_xml(std::string & contenido_html, const std::string & nombre_elemento, const std::string & etiqueta_inicial);

    std::unordered_map<std::string, medios::feed::canal*> canales_portal;

    std::unordered_map<std::string, std::vector<noticia*>> noticias_portal;
};

};