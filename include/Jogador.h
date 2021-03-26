#ifndef JOGADOR_H
#define JOGADOR_H
#include "Animacao.h"
#include "Colisor.h"


class Jogador
{
    public:
        Jogador(sf::Texture* textura, sf::Vector2u tamanhoDaImagem, float tempoTroca, float vel);
        virtual ~Jogador();

        void atualiza(float deltaTempo);
        void desenha(sf::RenderWindow& window);

        sf::Vector2f getPosicao() { return corpoJogador.getPosition(); };
        float getY() { return corpoJogador.getPosition().y; };

        bool getStatus() { return vivo; };
        void setStatus(bool status) { vivo = status; };

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

        bool vivo;
};

#endif // Jogador_H
