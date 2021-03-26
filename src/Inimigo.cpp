#include "Inimigo.h"
#include "Mapa.h"
#include <math.h>
#include <iostream>

using namespace std;

Inimigo::Inimigo(sf::Texture* textura, sf::Vector2u tamanhoDaImagem, float tempoTroca, float vel, sf::Vector2f posicao, int sentidoX, int sentidoY) :
    animacao(textura, tamanhoDaImagem, tempoTroca)
{
    linha = 0;

    velMax = vel;
    velocidadeX = vel;
    velocidadeY = vel;
    sentidoMovimentoX = sentidoX;
    sentidoMovimentoY = sentidoY;

    ultimaDirecao = 'b';

    corpoInimigo.setSize(sf::Vector2f(30.0f, 15.0f));
    corpoInimigo.setOrigin(corpoInimigo.getSize() / 2.0f);
    corpoInimigo.setPosition(posicao);
    texturaInimigo.setSize(sf::Vector2f(64.0f, 64.0f));
    texturaInimigo.setOrigin(texturaInimigo.getSize() / 2.0f);
    texturaInimigo.setPosition(0.0f, 0.0f);
    texturaInimigo.setTexture(textura);
}

Inimigo::~Inimigo()
{

}

void Inimigo::atualiza(float deltaTempo)
{
    //COMANDOS MOVIMENTAÇAO
    float X = corpoInimigo.getPosition().x;
    float Y = corpoInimigo.getPosition().y;
    float metadeX = corpoInimigo.getSize().x / 2;
    float metadeY = corpoInimigo.getSize().y / 2;

    if(X - metadeX < BORDA_ESQ)
    {
        corpoInimigo.setPosition(BORDA_ESQ + 1 + metadeX, Y);
        sentidoMovimentoX = 1;
    }
    else if(X + metadeX > BORDA_DIR)
    {
        corpoInimigo.setPosition(BORDA_DIR - 1 - metadeX, Y);
        sentidoMovimentoX = -1;
    }

    if(Y - metadeY < BORDA_SUP)
    {
        corpoInimigo.setPosition(X, BORDA_SUP + 1 + metadeY);
        sentidoMovimentoY = 1;
    }
    else if(Y + metadeY > BORDA_INF)
    {
        corpoInimigo.setPosition(X, BORDA_INF - 1 - metadeY);
        sentidoMovimentoY = -1;
    }

    //EM MOVIMENTO
    if(sentidoMovimentoX || sentidoMovimentoY)
        emMovimento = true;
    else
        emMovimento = false;

    //ANIMACAO
    if(sentidoMovimentoX == 1)
    {
        linha = 11;
        animacao.setNumFrames(9);
        ultimaDirecao = 'd';
    }
    else if(sentidoMovimentoX == -1)
    {
        linha = 9;
        animacao.setNumFrames(9);
        ultimaDirecao = 'e';
    }
    else if(sentidoMovimentoY == 1)
    {
        linha = 10;
        animacao.setNumFrames(9);
        ultimaDirecao = 'b';
    }
    else if(sentidoMovimentoY == -1)
    {
        linha = 8;
        animacao.setNumFrames(9);
        ultimaDirecao = 'c';
    }
    else
    {
        switch(ultimaDirecao)
        {
            case 'c':
                linha = 0;
                break;
            case 'e':
                linha = 1;
                break;
            case 'b':
                linha = 2;
                break;
            case 'd':
                linha = 3;
                break;
        }
        animacao.setNumFrames(0);
        animacao.setFrameAtual(0);
    }

    float dx = velocidadeX * sentidoMovimentoX * deltaTempo;
    float dy = velocidadeY * sentidoMovimentoY * deltaTempo;
    corpoInimigo.move(dx, dy);

    animacao.atualiza(linha, deltaTempo, emMovimento, true);
    sf::Vector2f posicao = corpoInimigo.getPosition();
    posicao.y -= 27;
    texturaInimigo.setPosition(posicao);
    texturaInimigo.setTextureRect(animacao.frameRet);
}

void Inimigo::desenha(sf::RenderWindow& window)
{
    //window.draw(corpoInimigo);
    window.draw(texturaInimigo);
}

