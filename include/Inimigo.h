#ifndef INIMIGO_H
#define INIMIGO_H
#include "Animacao.h"
#include "Colisor.h"

class Inimigo
{
    public:
        Inimigo(sf::Texture* textura, sf::Vector2u tamanhoDaImagem, float tempoTroca, float vel, sf::Vector2f posicao, int sentidoX, int sentidoY);
        virtual ~Inimigo();

        void atualiza(float deltaTempo);
        void desenha(sf::RenderWindow& window);

        float getY() { return corpoInimigo.getPosition().y; };

        void setSentidoX(int sentido) { sentidoMovimentoX = sentido; };
        void setSentidoY(int sentido) { sentidoMovimentoY = sentido; };

        Colisor getColisor() { return Colisor(corpoInimigo); };

    private:
        sf::RectangleShape corpoInimigo;
        sf::RectangleShape texturaInimigo;
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

#endif // INIMIGO_H
