#include <noticias/include/config.h>


namespace medios {
    namespace noticias {

config_feed config::clarin;
config_feed config::la_nacion;
config_feed config::infobae;
config_feed config::pagina12;
config_feed config::eldestape;
std::unordered_map<std::string, config_feed> config::feeds;

    }
}