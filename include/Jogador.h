#ifndef JOGADOR_H
#define JOGADOR_H
#include "Animacao.h"
#include "Colisor.h"


class Jogador
{
    public:
        Jogador(sf::Texture* textura, sf::Vector2u tamanhoDaImagem, float tempoTroca, float vel);
        virtual ~Jogador();

        void atualiza(float deltaTempo, int acelerado);
        void desenha(sf::RenderWindow& window);
        void emColisao(char direcao);
        bool colisaoBordasX();
        bool colisaoBordasY();

        sf::Vector2f getPosicao() { return corpoJogador.getPosition(); };

        float getX() { return corpoJogador.getPosition().x; };
        float getY() { return corpoJogador.getPosition().y; };

        float getVX() { return velocidadeX; };
        float getVY() { return velocidadeY; };

        void setVX(float novaVX) { velocidadeX = novaVX; };
        void setVY(float novaVY) { velocidadeY = novaVY; };

        int sentidoMovimentoLateral() { return sentidoMovimentoX; };
        int sentidoMovimentoVertical() { return sentidoMovimentoY; };

        void set(float x, float y) { corpoJogador.setPosition(x, y); };

        Colisor getColisor() { return Colisor(corpoJogador); };

    private:
        sf::RectangleShape corpoJogador;
        sf::RectangleShape texturaJogador;
        Animacao animacao;

        unsigned int linha;
        bool emMovimento;
        char ultimaDirecao;

        int velocidadeX;
        int velocidadeY;
        int sentidoMovimentoX;
        int sentidoMovimentoY;
        int velMax;

};

#endif // Jogador_H
