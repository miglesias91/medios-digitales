#pragma once

// noticias
#include <noticias/include/portal.h>

struct simple_walker_clarin : pugi::xml_tree_walker {

    virtual bool for_each(pugi::xml_node & node) {

        for (int i = 0; i < depth(); ++i) std::cout << "  "; // indentation

        std::cout << "name='" << node.name() << "'\n";

        return true; // continue traversal
    }

    pugi::xml_node nodo_con_parrafos;
};

namespace medios::noticias {

class clarin : public portal {
public:
    clarin();
    virtual ~clarin();

protected:
    virtual bool extraer_contenido_de_html(const std::string & contenido_html, std::string & contenido);
};

};