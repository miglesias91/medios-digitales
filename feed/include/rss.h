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
    virtual pugi::xml_object_range<pugi::xml_named_node_iterator> historias_xml(const pugi::xml_document & xml_feed);

    virtual bool parsear_historia(const pugi::xml_node & xml_historia, historia * histo);

};

};