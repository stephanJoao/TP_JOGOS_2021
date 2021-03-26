#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <math.h>
#include "Inimigo.h"
#include "Inventario.h"
#include "Item.h"
#include "Jogador.h"
#include "Mapa.h"
#include "Cena.h"
#include "Objetivo.h"
#include "Plataforma.h"

#define MAX_PONTOS 2000
#define MAX_ITENS 27
#define CAMPO_VISAO 500

static const float VIEW_HEIGHT = 322.0f;

using namespace std;

void ResizeView(const sf::RenderWindow& window, sf::View& view)
{
    float aspectRatio = float(window.getSize().x) / float(window.getSize().y);
    view.setSize(VIEW_HEIGHT * aspectRatio, VIEW_HEIGHT);
}

int teclaPressionada()
{
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
        return 1;
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
        return 2;
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
        return 3;
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num4))
        return 4;
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num5))
        return 5;
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num6))
        return 6;
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num7))
        return 7;
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num8))
        return 8;
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num9))
        return 9;
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::M))
        return 10;
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Tab))
        return 11;
    else
        return 0;
}

float obtemPosX(Jogador* j)
{
    return j->getX();
}

float obtemPosY(Jogador* j)
{
    return j->getY();
}

typedef struct
{
    float x, y;
    int visivel;
}Itens;

float obtemPosItemX(Itens t[], int i)
{
    return t[i].x;
}

float obtemPosItemY(Itens t[], int i)
{
    return t[i].y;
}

int obtemVisibilidadeItem(Itens t[], int i)
{
    return t[i].visivel;
}

void atualizaItens(Itens t[], std::vector<Item> itens)
{
    for(int i = 0; i < NUMERO_ITENS; i++)
    {
        t[i].x = itens[i].getX();
        t[i].y = itens[i].getY();
        t[i].visivel = !itens[i].getStatus();
    }
}

int obtemTipoCelula(Mapa* m, int x, int y)
{
    return m->getCelula(x, y);
}

///----------------------------------------------------------------------------------///
///                                  EXERCICIOS                                      ///
///----------------------------------------------------------------------------------///

///EXERCICIO 1

typedef struct
{
    int x; ///Coordenada x
    int y; ///Coordenada y
}Ponto;

typedef struct
{
    Ponto posicao; ///Posicao do item
    int visivel;   ///Indicador se o item eh visivel ou nao
}ItemMinimapa;

typedef struct
{
    int mapa[TAMANHO_MAPA_X][TAMANHO_MAPA_Y]; ///Matriz do minimapa
    Ponto jogador;                            ///Posicao do jogador
    int numeroPontos;                         ///Numero de pontos visiveis
    Ponto pontosVisiveis[MAX_PONTOS];         ///Vetor de pontos visiveis
    ItemMinimapa itens[MAX_ITENS];            ///Vetor de itens no minimapa
}Minimapa;

///EXERCICIO 2

Ponto atualizaJogador(Jogador* j, Minimapa minimapa)
{
    minimapa.jogador.x = (int)(obtemPosX(j) / TAMANHO_BLOCOS);
    minimapa.jogador.y = (int)(obtemPosY(j) / TAMANHO_BLOCOS);

    return minimapa.jogador;
}

///EXERCICIO 3

Minimapa atualizaVisibilidade(Jogador* j, Minimapa minimapa)
{
    minimapa.numeroPontos = 0;
    float jogadorX = obtemPosX(j);
    float jogadorY = obtemPosY(j);
    float blocoX, blocoY, distancia;
    for(int i = 0; i < TAMANHO_MAPA_X; i++)
    {
        for(int j = 0; j < TAMANHO_MAPA_Y; j++)
        {
            blocoX = (i * TAMANHO_BLOCOS) + (TAMANHO_BLOCOS / 2);
            blocoY = (j * TAMANHO_BLOCOS) + (TAMANHO_BLOCOS / 2);

            distancia = sqrt(pow(blocoX - jogadorX, 2) + pow(blocoY - jogadorY, 2));

            if(distancia < CAMPO_VISAO)
            {
                minimapa.pontosVisiveis[minimapa.numeroPontos].x = i;
                minimapa.pontosVisiveis[minimapa.numeroPontos].y = j;
                minimapa.numeroPontos++;
            }
        }
    }
    return minimapa;
}

///EXERCICIO 4

ItemMinimapa atualizaPontoItem(Itens t[], int i, Minimapa minimapa)
{
    minimapa.itens[i].posicao.x = (int)(obtemPosItemX(t, i) / TAMANHO_BLOCOS);
    minimapa.itens[i].posicao.y = (int)(obtemPosItemY(t, i) / TAMANHO_BLOCOS);
    minimapa.itens[i].visivel = obtemVisibilidadeItem(t, i);

    return minimapa.itens[i];
}

///EXERCICIO 5

Minimapa atualizaMinimapa(Jogador* j, Mapa* m, Itens t[], Minimapa minimapa)
{
    minimapa = atualizaVisibilidade(j, minimapa);

    minimapa.jogador = atualizaJogador(j, minimapa);

    int valor;
    for(int i = 0; i < TAMANHO_MAPA_X; i++)
    {
        for(int j = 0; j < TAMANHO_MAPA_Y; j++)
        {
            valor = obtemTipoCelula(m, i, j);
            if(valor == 0)
                minimapa.mapa[i][j] = 0;
            else if(valor == 7 || valor == 8)
                minimapa.mapa[i][j] = 2;
            else
                minimapa.mapa[i][j] = 1;
        }
    }

    for(int i = 0; i < NUMERO_ITENS; i++)
    {
        minimapa.itens[i] = atualizaPontoItem(t, i, minimapa);
    }

    return minimapa;
}

///----------------------------------------------------------------------------------///
///                                                                                  ///
///----------------------------------------------------------------------------------///

int main()
{
    char nome[6];
    printf("Digite seu apelido (abaixo de 5 caracteres): ");
    scanf("%s", nome);

    //VARIAVEIS DA CONFIGURACAO
    sf::RenderWindow window(sf::VideoMode(800, 512), "Jogo Aula 07", sf::Style::Close);
    sf::View view(sf::Vector2f(0, 0), sf::Vector2f(VIEW_HEIGHT, VIEW_HEIGHT));
    srand(time(0));

    //VARIAVEL EXERCICIO
    Minimapa minimapa;

    //VARIAVEIS DO JOGO
    sf::Texture texturaJogador;
    texturaJogador.loadFromFile("texturas/jogador.png");
    sf::Texture texturaMapa;
    texturaMapa.loadFromFile("texturas/mapa.png");
    sf::Texture texturaInimigo;
    texturaInimigo.loadFromFile("texturas/inimigo.png");
    sf::Texture texturaInventario;
    texturaInventario.loadFromFile("texturas/inventario.png");
    sf::Texture texturaItem;
    texturaItem.loadFromFile("texturas/itens.png");
    sf::Texture texturaIndice;
    texturaIndice.loadFromFile("texturas/indices.png");
    sf::Texture texturaObjetivo;
    texturaObjetivo.loadFromFile("texturas/amigo.png");

    Mapa mapa(&texturaMapa, sf::Vector2u(16, 16), &texturaInventario, sf::Vector2u(17, 10));

    Jogador jogador(&texturaJogador, sf::Vector2u(13, 21), 0.3f, 180.0f);

    Inventario inventario(&texturaInventario, sf::Vector2u(17, 10), &texturaItem, sf::Vector2u(16, 16), &texturaIndice, sf::Vector2u(4, 1));

    Objetivo objetivo(&texturaObjetivo, sf::Vector2u(13, 21), &texturaInventario, sf::Vector2u(17, 10), &texturaItem, sf::Vector2u(16, 16));
    objetivo.adicionaEventos(jogador.getPosicao());

    ////TEMPO

    float tempoTotal = 0.01;
    float tempoAtual = 0.01;
    bool tempoAtualRecebido = false;

    //CENA

    float xPlataformas[NUMERO_PLATAFORMAS] = {500, 384,  480,  624,  864, 1056, 1248, 1296,  768, 1128, 1392};
    float compPlataformas[NUMERO_PLATAFORMAS] = {26, 96, 192, 288, 192, 192, 192, 192, 192, 144,  96};
    float yPlataformas[NUMERO_PLATAFORMAS] = {227, 384, 1104,  528,  624, 1296, 1200,  576, 1104,  888, 1512};
    float altPlataformas[NUMERO_PLATAFORMAS] =  {15, 96, 384, 192, 384, 384, 192, 192, 192, 144, 144};

    Cena dadosCena(xPlataformas, compPlataformas, yPlataformas, altPlataformas);

    ////PLATAFORMAS

    std::vector<Plataforma> plataformas;
    for(int i = 0; i < NUMERO_PLATAFORMAS; i++)
        plataformas.push_back(Plataforma(NULL, sf::Vector2f(dadosCena.getPlatX(i), dadosCena.getPlatY(i)), sf::Vector2f(dadosCena.getPlatComp(i), dadosCena.getPlatAlt(i))));

    ////INIMIGO

    dadosCena.criaInimigos();
    std::vector<Inimigo> inimigos;
    for(int i = 0; i < NUMERO_INIMIGOS; i++)
        inimigos.push_back(Inimigo(&texturaInimigo, sf::Vector2u(13, 21), 0.3f, dadosCena.getInimVel(i), sf::Vector2f(dadosCena.getInimX(i) , dadosCena.getInimY(i)), dadosCena.getInimMovX(i), dadosCena.getInimMovY(i)));

    ////ITENS

    Itens itensMinimapa[NUMERO_ITENS];
    dadosCena.criaItens();
    std::vector<Item> itens;
    for(int i = 0; i < NUMERO_ITENS; i++)
        itens.push_back(Item(&texturaItem, sf::Vector2u(16, 16), sf::Vector2f(dadosCena.getItemX(i), dadosCena.getItemY(i)), dadosCena.getItemTipo(i)));
    atualizaItens(itensMinimapa, itens);

    //CONFIGURA TEMPO
    float deltaTempo = 0.0f;
    sf::Clock clock;

    //DELAY TECLA
    float delay = 1;

    //CONFIGURA VIEW
    ResizeView(window, view);

    while(window.isOpen())
    {
        ////CONFIGURACOES GERAIS

        deltaTempo = clock.restart().asSeconds();
        if(deltaTempo > 1.0f / 20.0f)
            deltaTempo = 1.0f / 20.0f;

        if(delay > 0)
            delay -= deltaTempo;
        else
            delay = 0;

        tempoTotal += deltaTempo;

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

        //ITENS

        for(unsigned int i = 0; i < itens.size(); i++)
        {
            Item& item = itens[i];

            //PEGAR ITEM
            if(item.getColisor().checaColisao(jogador.getColisor()) && sf::Keyboard::isKeyPressed(sf::Keyboard::E) && !item.getStatus())
            {
                item.coletou();
                inventario.pegouItem(item.getTipo());
                atualizaItens(itensMinimapa, itens);
                objetivo.adicionaEventos(jogador.getPosicao());
            }

            //ENTREGAR ITEM
            if(item.getColisor().checaColisao(objetivo.getColisorItens()) && !item.getStatus() && objetivo.getNumRecebidos() != 5)
            {
                item.coletou();
                atualizaItens(itensMinimapa, itens);
                objetivo.recebeuItem(item.getTipo());
            }
        }

        int tecla = teclaPressionada();

        if(tecla != 0 && delay == 0)
        {
            char tipo = inventario.soltouItem(tecla);
            if(tipo != ' ')
            {
                for(unsigned int i = 0; i < itens.size(); i++)
                {
                    Item& item = itens[i];
                    if(item.getTipo() == tipo && item.getStatus())
                    {
                        item.soltou(jogador.getPosicao().x, jogador.getPosicao().y - 20);
                        atualizaItens(itensMinimapa, itens);
                        break;
                    }
                }
            delay = 0.6;
            objetivo.adicionaEventos(jogador.getPosicao());
            }
        }

        //COLISOES

        char direcao;

        for(unsigned int i = 0; i < plataformas.size(); i++)
        {
            Plataforma& plataforma = plataformas[i];

            //JOGADOR x PLATAFORMA
            plataforma.getColisor().checaColisaoJogadorPlataforma(jogador.getColisor());

            for(unsigned int j = 0; j < inimigos.size(); j++)
            {
                Inimigo& inimigo = inimigos[j];

                //INIMIGO x PLATAFORMA
                direcao = plataforma.getColisor().checaColisaoInimigoPlataforma(inimigo.getColisor());
                switch(direcao)
                {
                    case 'c':
                        inimigo.setSentidoY(1);
                        break;
                    case 'b':
                        inimigo.setSentidoY(-1);
                        break;
                    case 'd':
                        inimigo.setSentidoX(-1);
                        break;
                    case 'e':
                        inimigo.setSentidoX(1);
                        break;
                    default:
                        break;
                }

                //INIMIGO x JOGADOR
                if(jogador.getStatus())
                {
                    bool status = jogador.getColisor().checaColisao(inimigo.getColisor());
                    if(status)
                    {
                        jogador.setStatus(!status);
                        objetivo.adicionaEventos(jogador.getPosicao());
                    }
                }
            }
        }

        objetivo.getColisorPlayer().checaColisaoJogadorPlataforma(jogador.getColisor());

        //MOVIMENTACAO

        for(unsigned int i = 0; i < inimigos.size(); i++)
        {
            Inimigo& inimigo = inimigos[i];
            inimigo.atualiza(deltaTempo);
        }

        if(!objetivo.getTerminou())
            jogador.atualiza(deltaTempo);

        //ATUALIZA CONFIGURACOES

        view.setCenter(jogador.getPosicao());
        window.setView(view);
        window.clear(sf::Color(150,150,150));

        //DESENHA OS OBJETOS

        mapa.desenha(window);

        for(unsigned int i = 0; i < itens.size(); i++)
        {
            Item& item = itens[i];
            item.desenha(window);
        }

        bool vivo = jogador.getStatus();
        bool naFrente = (objetivo.getY() > jogador.getY());

        if(!vivo)
            jogador.desenha(window);

        for(unsigned int i = 0; i < inimigos.size(); i++)
        {
            Inimigo& inimigo = inimigos[i];
            if(inimigo.getY() < jogador.getY())
                inimigo.desenha(window);
        }

        if(!naFrente)
            objetivo.desenha(window, jogador.getStatus());

        if(vivo)
            jogador.desenha(window);

        if(naFrente)
            objetivo.desenha(window, jogador.getStatus());

        for(unsigned int i = 0; i < inimigos.size(); i++)
        {
            Inimigo& inimigo = inimigos[i];
            if(inimigo.getY() > jogador.getY())
                inimigo.desenha(window);
        }

        if(!objetivo.getTerminou() && jogador.getStatus())
        {
            inventario.desenha(window, view.getCenter());
            minimapa = atualizaMinimapa(&jogador, &mapa, itensMinimapa, minimapa);

            for(int i = 0; i < NUMERO_ITENS; i++)
            {
                mapa.m.itens[i].posicao.x = minimapa.itens[i].posicao.x;
                mapa.m.itens[i].posicao.y = minimapa.itens[i].posicao.y;
                mapa.m.itens[i].visivel = minimapa.itens[i].visivel;
            }
            mapa.m.jogador.x = minimapa.jogador.x;
            mapa.m.jogador.y = minimapa.jogador.y;
            for(int i = 0; i < TAMANHO_MAPA_X; i++)
            {
                for(int j = 0; j < TAMANHO_MAPA_X; j++)
                {
                    mapa.m.mapa[i][j] = minimapa.mapa[i][j];
                }
            }
            mapa.m.numeroPontos = minimapa.numeroPontos;
            for(int i = 0; i < minimapa.numeroPontos; i++)
            {
                mapa.m.pontosVisiveis[i].x = minimapa.pontosVisiveis[i].x;
                mapa.m.pontosVisiveis[i].y = minimapa.pontosVisiveis[i].y;
            }

            mapa.desenhaMinimapa(window, view.getCenter());
        }

        //FINAL DO JOGO

        if(!jogador.getStatus() && !objetivo.getTerminou())
        {
            if(!tempoAtualRecebido)
            {
                tempoAtual = tempoTotal;
                tempoAtualRecebido = true;
                objetivo.calculaPontos(tempoAtual);
                objetivo.organizaRecordes(nome);
            }
            objetivo.desenhaFinal(window, view.getCenter(), (teclaPressionada() == 10));

            if(teclaPressionada() == 11)
                objetivo.desenhaRecordes(window, view.getCenter());
        }


        if(objetivo.getTerminou())
        {
            if(!tempoAtualRecebido)
            {
                tempoAtual = tempoTotal;
                tempoAtualRecebido = true;
                objetivo.calculaPontos(tempoAtual);
                objetivo.organizaRecordes(nome);
            }
            objetivo.fimDeJogo();
            objetivo.desenhaFinal(window, view.getCenter(), (teclaPressionada() == 10));

            if(teclaPressionada() == 11)
                objetivo.desenhaRecordes(window, view.getCenter());
        }

        ////
        window.display();
    }

    return 0;
}
