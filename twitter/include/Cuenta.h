#pragma once

// stl
#include <string>

namespace medios::twitter {

class Cuenta {
public:
    Cuenta(std::string nombre = "");
    virtual ~Cuenta();

    // GETTERS

    std::string getNombre();

    unsigned long long int getIdUltimoTweetAnalizado();

    // SETTERS

    void setNombre(std::string nombre);

    void setIdUltimoTweetAnalizado(unsigned long long int id_ultimo_tweet_analizado);

    // METODOS

    // CONSULTAS

private:

    // ATRIBUTOS

    std::string nombre;

    unsigned long long int id_ultimo_tweet_analizado;
};

};