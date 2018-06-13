#pragma once

// stl
#include <vector>

// feed
#include <feed/include/canal.h>

namespace medios::feed {

class atom : public canal {
public:
    atom(const std::string & uri);
    virtual ~atom();

protected:

    virtual bool parsear(const std::string & contenido_xml, std::vector<historia> & historias);


};

};