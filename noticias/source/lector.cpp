#include <noticias/include/lector.h>

// stl
#include <algorithm>

namespace medios {
    namespace noticias {

lector::lector() {}

lector::~lector() {}

void lector::leer(portal * portal,
    const herramientas::utiles::Fecha & desde,
    const herramientas::utiles::Fecha & hasta) const {

    std::vector<medios::feed::canal*> canales;
    portal->canales(&canales);

    // lanzo todas las peticiones http,
    std::for_each(canales.begin(), canales.end(), [=](medios::feed::canal * canal) {
        canal->pedir_historias();
    });

    // y ahora espero a recibir las respuestas.
    std::for_each(canales.begin(), canales.end(), [=](medios::feed::canal * canal) {
        std::vector<medios::feed::historia*> historias_por_canal;
        canal->historias_ya(historias_por_canal, desde, hasta);

        // agrego las noticias recibidas.
        std::for_each(historias_por_canal.begin(), historias_por_canal.end(), [=](medios::feed::historia * historia) {

            portal->nueva_noticia(*historia);
            delete historia;
        });
    });
}

    }
}