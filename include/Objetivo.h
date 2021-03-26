#ifndef OBJETIVO_H
#define OBJETIVO_H
#include <SFML/Graphics.hpp>
#include "Colisor.h"
#include "math.h"

class Objetivo
{
    public:
        Objetivo(sf::Texture* texturaPessoa, sf::Vector2u tamanhoDaImagemPessoa, sf::Texture* texturaFala, sf::Vector2u tamanhoDaImagemFala, sf::Texture* texturaItem, sf::Vector2u tamanhoDaImagemItem);
        virtual ~Objetivo();

        Colisor getColisorPlayer() { return Colisor(corpo); };
        Colisor getColisorItens() { return Colisor(corpoObjetivo); };

        float getY() { return corpo.getPosition().y; };

        void desenha(sf::RenderWindow& window, char resposta[], char recebidos[], bool ganhou, bool terminou, bool vivo);
        void desenhaFinal(sf::RenderWindow& window, sf::Vector2f posicao, bool ganhou);
        void desenhaRecordes(sf::RenderWindow& window, sf::Vector2f posicao);

        void adicionaEventos(sf::Vector2f posicao);
        void calculaPontos(float tempoTotal, bool ganhou);
        int organizaRecordes();

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

        sf::Text texto;
        sf::Text pontos;
        sf::Text recorde;
        sf::Font fonte;

        //EVENTOS

        float xEventos[1000];
        float yEventos[1000];
        int numeroEventos;

        //RECORDES
        float recordes[5];
        int numeroRecordes;
        float pontuacao;
        bool recordeAdicionado;
        bool pontosCalculados;
};

#endif // OBJETIVO_H
