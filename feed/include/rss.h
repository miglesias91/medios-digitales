#pragma once

// stl
#include <vector>

// feed
#include <feed/include/canal.h>

namespace medios::feed {

class rss : public canal {
public:
    rss(const std::string & uri);
    virtual ~rss();

protected:

    virtual bool parsear(const std::string & contenido_xml, std::vector<historia> & historias);

};

};