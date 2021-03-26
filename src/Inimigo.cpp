#include "Inimigo.h"
#include "Mapa.h"
#include <math.h>
#include <iostream>

using namespace std;

Inimigo::Inimigo(sf::Texture* textura, sf::Vector2u tamanhoDaImagem, float tempoTroca, float vel) :
    animacao(textura, tamanhoDaImagem, tempoTroca)
{
    linha = 0;

    velMax = vel;
    velocidadeX = vel;
    velocidadeY = vel;
    sentidoMovimentoX = 1;
    sentidoMovimentoY = 0;

    ultimaDirecao = 'b';

    corpoInimigo.setSize(sf::Vector2f(30.0f, 15.0f));
    corpoInimigo.setOrigin(corpoInimigo.getSize() / 2.0f);
    corpoInimigo.setPosition(500.0f, 600.0f);
    texturaInimigo.setSize(sf::Vector2f(64.0f, 64.0f));
    texturaInimigo.setOrigin(texturaInimigo.getSize() / 2.0f);
    texturaInimigo.setPosition(0.0f, 0.0f);
    texturaInimigo.setTexture(textura);
}

Inimigo::~Inimigo()
{

}

void Inimigo::atualiza(float deltaTempo, float distanciaX, float distanciaY, int perseguindo)
{
    //COMANDOS MOVIMENTAÇAO
    if(perseguindo)
    {
        if(distanciaX >= -5 && distanciaX <= 5)
            sentidoMovimentoX = 0;
        if(distanciaY >= -5 && distanciaY <= 5)
            sentidoMovimentoY = 0;
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
    window.draw(texturaInimigo);
}
