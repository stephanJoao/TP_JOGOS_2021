#ifndef OBJETIVO_H
#define OBJETIVO_H
#include <SFML/Graphics.hpp>
#include "Colisor.h"

class Objetivo
{
    public:
        Objetivo(sf::Texture* texturaPessoa, sf::Vector2u tamanhoDaImagemPessoa, sf::Texture* texturaFala, sf::Vector2u tamanhoDaImagemFala, sf::Texture* texturaItem, sf::Vector2u tamanhoDaImagemItem);
        virtual ~Objetivo();

        Colisor getColisorPlayer() { return Colisor(corpo); };
        Colisor getColisorItens() { return Colisor(corpoObjetivo); };

        void recebeuItem(char recebeu);

        bool getTerminou(){ return terminou; };
        int getNumRecebidos() { return numRecebidos; };
        void fimDeJogo();

        float getY() { return corpo.getPosition().y; };

        void desenha(sf::RenderWindow& window, bool vivo);
        void desenhaFinal(sf::RenderWindow& window, sf::Vector2f posicao, float p, bool desenhaRecordes);
        void desenhaRecordes(sf::RenderWindow& window, sf::Vector2f posicao, int numeroRecordes, float recordes[]);

    private:
        sf::RectangleShape corpo;
        sf::RectangleShape corpoObjetivo;
        sf::IntRect objetivoRet;

        sf::RectangleShape corpoFala;
        sf::IntRect falaRet;

        sf::RectangleShape corpoItem;
        sf::IntRect itemRet;

        sf::RectangleShape corpoRec;
        sf::IntRect recRet;

        bool terminou;
        bool ganhou;

        char letras[10];
        char resposta[6];

        char recebidos[6];
        int numRecebidos;

        sf::Text texto;
        sf::Text pontos;
        sf::Text recorde;
        sf::Font fonte;

};

#endif // OBJETIVO_H
