#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Jogador.h"
#include "Plataforma.h"
#include "Mapa.h"

static const float VIEW_HEIGHT = 322.0f;

using namespace std;

float obtemPosicaoX(Jogador* p)
{
    return p->getX();
}

float obtemPosicaoY(Jogador* p)
{
    return p->getY();
}

void atualizaPosicao(Jogador* p, float x, float y)
{
    p->set(x, y);
}

float obtemVelocidadeX(Jogador* p)
{
    return p->getVX();
}

float obtemVelocidadeY(Jogador* p)
{
    return p->getVY();
}

void atualizaVelocidadeX(Jogador* p, float novaVX)
{
    p->setVX(novaVX);
}

void atualizaVelocidadeY(Jogador* p, float novaVY)
{
    p->setVY(novaVY);
}

int sentidoMovimentoLateral(Jogador* p)
{
    return p->sentidoMovimentoLateral();
}

int sentidoMovimentoVertical(Jogador* p)
{
    return p->sentidoMovimentoVertical();
}

void ResizeView(const sf::RenderWindow& window, sf::View& view)
{
    float aspectRatio = float(window.getSize().x) / float(window.getSize().y);
    view.setSize(VIEW_HEIGHT * aspectRatio, VIEW_HEIGHT);
}

///----------------------------------------------------------------------------------///
///                                  EXERCICIOS                                      ///
///----------------------------------------------------------------------------------///

///EXERCICIO 1
float deslocamentoLateral(Jogador* p, float deltaTempo)
{
    float vx = obtemVelocidadeX(p);
    return vx * deltaTempo * sentidoMovimentoLateral(p);
}

///EXERCICIO 2
float deslocamentoVertical(Jogador* p, float deltaTempo)
{
    float vy = obtemVelocidadeY(p);
    return vy * deltaTempo * sentidoMovimentoVertical(p);
}

///EXERCICIO 3 & 4
int movimentaPersonagem(Jogador* p, float deltaTempo)
{
    float x, y;
    x = obtemPosicaoX(p);
    y = obtemPosicaoY(p);

///EXERCICIO 4
///float vx, vy;
///vx = obtemVelocidadeX(p);
///vy = obtemVelocidadeY(p);
///vx = vx + (500 * deltaTempo * sentidoMovimentoLateral(p));
///vy = vy + (500 * deltaTempo * sentidoMovimentoVertical(p));
///atualizaVelocidadeX(p, vx);
///atualizaVelocidadeY(p, vy);
///x = x + vx * deltaTempo;
///y = y + vy * deltaTempo;

    ///Essas duas linhas abaixo devem ser excluidas para o funcionamento do exercicio 4;
    x = x + deslocamentoLateral(p, deltaTempo);
    y = y + deslocamentoVertical(p, deltaTempo);
    atualizaPosicao(p, x, y);

    return 0;
}


///----------------------------------------------------------------------------------///
///                                                                                  ///
///----------------------------------------------------------------------------------///

int main()
{
    //VARIAVEIS DA CONFIGURACAO
    sf::RenderWindow window(sf::VideoMode(800, 512), "Jogo Aula 01", sf::Style::Close);
    sf::View view(sf::Vector2f(0, 0), sf::Vector2f(VIEW_HEIGHT, VIEW_HEIGHT));

    //VARIAVEIS DO JOGO
    sf::Texture texturaJogador;
    texturaJogador.loadFromFile("texturas/jogador.png");
    sf::Texture texturaMapa;
    texturaMapa.loadFromFile("texturas/mapa.png");

    int acelerado = 0;

    char direcao;

    Mapa mapa(&texturaMapa);

    Jogador jogador(&texturaJogador, sf::Vector2u(13, 21), 0.3f, 180.0f);

    std::vector<Plataforma> platformas;
        platformas.push_back(Plataforma(NULL, sf::Vector2f(384.0f, 384.0f), sf::Vector2f(96.0f, 96.0f)));
        platformas.push_back(Plataforma(NULL, sf::Vector2f(528.0f, 576.0f), sf::Vector2f(192.0f, 192.0f)));
        platformas.push_back(Plataforma(NULL, sf::Vector2f(215.0f, 480.0f), sf::Vector2f(48.0f, 576.0f)));
        platformas.push_back(Plataforma(NULL, sf::Vector2f(745.0f, 480.0f), sf::Vector2f(48.0f, 576.0f)));
        platformas.push_back(Plataforma(NULL, sf::Vector2f(480.0f, 167.0f), sf::Vector2f(480.0f, 48.0f)));
        platformas.push_back(Plataforma(NULL, sf::Vector2f(480.0f, 793.0f), sf::Vector2f(480.0f, 48.0f)));

    //CONFIGURA TEMPO
    float deltaTempo = 0.0f;
    sf::Clock clock;

    //CONFIGURA VIEW
    ResizeView(window, view);

    while(window.isOpen())
    {
        ////CONFIGURACOES GERAIS

        deltaTempo = clock.restart().asSeconds();
        if(deltaTempo > 1.0f / 20.0f)
            deltaTempo = 1.0f / 20.0f;

        sf::Event evnt;
        while(window.pollEvent(evnt))
        {
            switch(evnt.type)
            {
                case sf::Event::Closed:
                    window.close();
                    break;
                default:
                    break;
            }
        }

        ////JOGO

        //MOVIMENTACAO

        for(unsigned int i = 0; i < platformas.size(); i++)
        {
            Plataforma& platforma = platformas[i];
            if(platforma.getColisor().checaColisao(jogador.getColisor(), &direcao))
            {
                jogador.emColisao(direcao);
            }
        }

        jogador.atualiza(deltaTempo, acelerado);
        acelerado = movimentaPersonagem(&jogador, deltaTempo);

        //ATUALIZA CONFIGURACOES

        view.setCenter(jogador.getPosicao());
        window.setView(view);
        window.clear(sf::Color(150,150,150));

        //DESENHA OS OBJETOS


        for(unsigned int i = 0; i < platformas.size(); i++)
        {
            Plataforma& platforma = platformas[i];
            platforma.desenha(window);
        }
        mapa.desenha(window);
        jogador.desenha(window);

        ////
        window.display();
    }

    return 0;
}
