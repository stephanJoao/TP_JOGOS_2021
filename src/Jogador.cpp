#include "Jogador.h"
#include "Mapa.h"
#include <math.h>
#include <iostream>

using namespace std;

Jogador::Jogador(sf::Texture* textura, sf::Vector2u tamanhoDaImagem, float tempoTroca, float vel) :
    animacao(textura, tamanhoDaImagem, tempoTroca)
{
    vivo = true;

    linha = 0;

    velMax = vel;
    velocidadeX = 0;
    velocidadeY = 0;
    sentidoMovimentoX = 0;
    sentidoMovimentoY = 0;

    ultimaDirecao = 'b';

    corpoJogador.setSize(sf::Vector2f(30.0f, 15.0f));
    corpoJogador.setOrigin(corpoJogador.getSize() / 2.0f);
    corpoJogador.setPosition(300.0f, 350.0f);
    texturaJogador.setSize(sf::Vector2f(64.0f, 64.0f));
    texturaJogador.setOrigin(texturaJogador.getSize() / 2.0f);
    texturaJogador.setPosition(0.0f, 0.0f);
    texturaJogador.setTexture(textura);
}

Jogador::~Jogador()
{

}

void Jogador::atualiza(float deltaTempo)
{
    //COMANDOS TECLADO
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && sentidoMovimentoY == 0 && !sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && corpoJogador.getPosition().x - corpoJogador.getSize().x / 2 > BORDA_ESQ && vivo)
    {
        sentidoMovimentoX = -1;
        velocidadeX = velMax;
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && sentidoMovimentoY == 0 && !sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && corpoJogador.getPosition().x + corpoJogador.getSize().x / 2 < BORDA_DIR && vivo)
    {
        sentidoMovimentoX = 1;
        velocidadeX = velMax;
    }
    else
    {
        sentidoMovimentoX = 0;
        velocidadeX = 0;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && sentidoMovimentoX == 0 && !sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && corpoJogador.getPosition().y - corpoJogador.getSize().y / 2 > BORDA_SUP && vivo)
    {
        sentidoMovimentoY = -1;
        velocidadeY = velMax;
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && sentidoMovimentoX == 0 && !sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && corpoJogador.getPosition().y + corpoJogador.getSize().y / 2 < BORDA_INF && vivo)
    {
        sentidoMovimentoY = 1;
        velocidadeY = velMax;
    }
    else
    {
        sentidoMovimentoY = 0;
        velocidadeY = 0;
    }

    //EM MOVIMENTO
    if(sentidoMovimentoX || sentidoMovimentoY)
        emMovimento = true;
    else
        emMovimento = false;

    //ANIMACAO
    if(vivo)
    {
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
    }
    else
    {
        linha = 20;
        animacao.setNumFrames(6);
    }

    float dx = velocidadeX * sentidoMovimentoX * deltaTempo;
    float dy = velocidadeY * sentidoMovimentoY * deltaTempo;
    corpoJogador.move(dx, dy);

    animacao.atualiza(linha, deltaTempo, emMovimento, vivo);
    sf::Vector2f posicao = corpoJogador.getPosition();
    posicao.y -= 27;
    texturaJogador.setPosition(posicao);
    texturaJogador.setTextureRect(animacao.frameRet);
}

void Jogador::desenha(sf::RenderWindow& window)
{
    //window.draw(corpoJogador);
    window.draw(texturaJogador);
}
