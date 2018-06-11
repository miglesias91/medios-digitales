#include <twitter/include/Cuenta.h>

namespace medios::twitter {

Cuenta::Cuenta(std::string nombre) : nombre(nombre), id_ultimo_tweet_analizado(0) {}

Cuenta::~Cuenta() {}

// GETTERS

std::string Cuenta::getNombre() {
    return this->nombre;
}

unsigned long long int Cuenta::getIdUltimoTweetAnalizado() {
    return this->id_ultimo_tweet_analizado;
}

// SETTERS

void Cuenta::setNombre(std::string nombre) {
    this->nombre = nombre;
}

void Cuenta::setIdUltimoTweetAnalizado(unsigned long long int id_ultimo_tweet_analizado) {
    this->id_ultimo_tweet_analizado = id_ultimo_tweet_analizado;
}

// METODOS

// CONSULTAS

}