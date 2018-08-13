#include <noticias/include/config.h>


namespace medios {
    namespace noticias {

config_feed config::clarin;
config_feed config::la_nacion;
config_feed config::infobae;
config_feed config::paginadoce;
config_feed config::eldestape;
config_feed config::casarosada;
std::unordered_map<std::string, config_feed> config::feeds;

    }
}