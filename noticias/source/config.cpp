#include <noticias/include/config.h>


namespace medios {
    namespace noticias {

config_feed config::clarin;
config_feed config::la_nacion;
config_feed config::infobae;
std::unordered_map<std::string, config_feed> config::feeds;

    }
}