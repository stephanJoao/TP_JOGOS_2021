#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <math.h>
#include "Jogador.h"
#include "Inimigo.h"
#include "Plataforma.h"
#include "Mapa.h"
#include "Item.h"
#include "Inventario.h"
#include "Objetivo.h"
#include "Cena.h"

#define BORDA_ESQ 240
#define BORDA_DIR 1584
#define BORDA_CIMA 192
#define BORDA_BAIXO 1632

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
    else
        return 0;
}

float obtemXPlataforma(Cena* c, int i)
{
    return c->getPlatX(i);
}

float obtemCompPlataforma(Cena* c, int i)
{
    return c->getPlatComp(i);
}

float obtemYPlataforma(Cena* c, int i)
{
    return c->getPlatY(i);
}

float obtemAltPlataforma(Cena* c, int i)
{
    return c->getPlatAlt(i);
}

float obtemXItem(Cena* c, int i)
{
    return c->getItemX(i);
}

float obtemYItem(Cena* c, int i)
{
    return c->getItemY(i);
}

float obtemTamanhoItem(Cena* c, int i)
{
    return c->getItemTamanho(i);
}

void atualizaPosicaoItem(Cena* c, int i, float x, float y)
{
    c->setItemX(i, x);
    c->setItemY(i, y);
}

void atualizaTipoItem(Cena* c, int i, char tipo)
{
    c->setItemTipo(i, tipo);
}

float obtemXInimigo(Cena* c, int i)
{
    return c->getInimX(i);
}

float obtemCompInimigo(Cena* c, int i)
{
    return c->getInimComp(i);
}

float obtemYInimigo(Cena* c, int i)
{
    return c->getInimY(i);
}

float obtemAltInimigo(Cena* c, int i)
{
    return c->getInimAlt(i);
}

void atualizaPosicaoInimigo(Cena* c, int i, float x, float y)
{
    c->setInimX(i, x);
    c->setInimY(i, y);
}

void atualizaMovInimigo(Cena* c, int i, int x, int y)
{
    c->setInimMovX(i, x);
    c->setInimMovY(i, y);
}

void atualizaVelInimigo(Cena* c, int i, float vel)
{
    c->setInimVel(i, vel);
}

///----------------------------------------------------------------------------------///
///                                  EXERCICIOS                                      ///
///----------------------------------------------------------------------------------///

///EXERCICIO 1
int colidiu(float itemX, float compItem, float itemY, float altItem, float objX, float compObj, float objY, float altObj)
{
    float deltaX = fabs(itemX - objX);
    float deltaY = fabs(itemY - objY);
    float distMinX = (compItem + compObj) / 2;
    float distMinY = (altItem + altObj) / 2;
    if((deltaX <= distMinX) && (deltaY <= distMinY))
        return 1;
    else
        return 0;
}

///EXERCICIO 2
int colidiuPlataformasItens(Cena* c, int indiceItem)
{
    float platX, platY, compPlat, altPlat;
    float itemX = obtemXItem(c, indiceItem);
    float itemY = obtemYItem(c, indiceItem);
    float compItem = obtemTamanhoItem(c, indiceItem), altItem = compItem;

    for(int i = 0; i < NUMERO_PLATAFORMAS; i++)
    {
        platX = obtemXPlataforma(c, i);
        platY = obtemYPlataforma(c, i);
        compPlat = obtemCompPlataforma(c, i);
        altPlat = obtemAltPlataforma(c, i);
        if(colidiu(itemX, compItem, itemY, altItem, platX, compPlat, platY, altPlat))
            return 1;
    }
    return 0;
}

int colidiuPlataformasInimigos(Cena* c, int indiceInimigo)
{
    float platX, platY, compPlat, altPlat;
    float inimigoX = obtemXInimigo(c, indiceInimigo);
    float inimigoY = obtemYInimigo(c, indiceInimigo);
    float inimigoComp = obtemCompInimigo(c, indiceInimigo);
    float inimigoAlt = obtemAltInimigo(c, indiceInimigo);

    for(int i = 0; i < NUMERO_PLATAFORMAS; i++)
    {
        platX = obtemXPlataforma(c, i);
        platY = obtemYPlataforma(c, i);
        compPlat = obtemCompPlataforma(c, i);
        altPlat = obtemAltPlataforma(c, i);
        if(colidiu(inimigoX, inimigoComp, inimigoY, inimigoAlt, platX, compPlat, platY, altPlat))
            return 1;
    }
    return 0;
}

int colidiuItens(Cena* c, int indiceItem)
{
    float item2X, item2Y, compItem2, altItem2;

    float itemX = obtemXItem(c, indiceItem);
    float itemY = obtemYItem(c, indiceItem);
    float compItem = obtemTamanhoItem(c, indiceItem);
    float altItem = compItem;

    for(int i = 0; i < indiceItem; i++)
    {
        item2X = obtemXItem(c, i);
        item2Y = obtemYItem(c, i);
        compItem2 = obtemTamanhoItem(c, i);
        altItem2 = compItem2;
        if(colidiu(itemX, compItem, itemY, altItem, item2X, compItem2, item2Y, altItem2))
            return 1;
    }
    return 0;
}

int colidiuInimigos(Cena* c, int indiceInimigo)
{
    float inimigo2X, inimigo2Y, inimigo2Comp, inimigo2Alt;

    float inimigoX = obtemXInimigo(c, indiceInimigo);
    float inimigoY = obtemYInimigo(c, indiceInimigo);
    float inimigoComp = obtemCompInimigo(c, indiceInimigo);
    float inimigoAlt  =  obtemAltInimigo(c, indiceInimigo);

    for(int i = 0; i < indiceInimigo; i++)
    {
        inimigo2X = obtemXInimigo(c, i);
        inimigo2Y = obtemYInimigo(c, i);
        inimigo2Comp = obtemCompInimigo(c, i);
        inimigo2Alt  =  obtemAltInimigo(c, i);
        if(colidiu(inimigoX, inimigoComp, inimigoY, inimigoAlt, inimigo2X, inimigo2Comp, inimigo2Y, inimigo2Alt))
            return 1;
    }
    return 0;
}

///EXERCICIO 3

void criaItens(Cena* c)
{
    int colisaoPlat = 1;
    int colisaoItens = 1;

    float xItem, yItem, tamanhoItem;
    char tipoItem;

    for(int i = 0; i < NUMERO_ITENS; i++)
    {
        tipoItem = 'a' + (i%9);
        atualizaTipoItem(c, i, tipoItem);

        colisaoPlat = 1;
        colisaoItens = 1;

        while(colisaoPlat || colisaoItens)
        {
            tamanhoItem = obtemTamanhoItem(c, i);
            xItem = BORDA_ESQ + tamanhoItem / 2.0 + (rand() % (int)(BORDA_DIR - BORDA_ESQ - tamanhoItem));
            yItem = BORDA_CIMA + tamanhoItem / 2.0 + (rand() % (int)(BORDA_BAIXO - BORDA_CIMA - tamanhoItem));
            atualizaPosicaoItem(c, i, xItem, yItem);

            colisaoPlat = colidiuPlataformasItens(c, i);

            if(!colisaoPlat)
                colisaoItens = colidiuItens(c, i);
        }
    }
}

///EXERCICIO 4

void criaInimigos(Cena* c)
{
    int colisaoPlat = 1;
    int colisaoInimigos = 1;

    float xInimigo, yInimigo, compInimigo, altInimigo, velInimigo;
    int movX, movY;

    for(int i = 0; i < NUMERO_INIMIGOS; i++)
    {
        movX = rand()%2;
        movY = !movX;
        atualizaMovInimigo(c, i, movX, movY);

        velInimigo = 60 + rand()%60;
        atualizaVelInimigo(c, i, velInimigo);

        colisaoPlat = 1;
        colisaoInimigos = 1;

        while(colisaoPlat || colisaoInimigos)
        {
            compInimigo = obtemCompInimigo(c, i);
            altInimigo = obtemAltInimigo(c, i);
            xInimigo = BORDA_ESQ + compInimigo / 2.0 + (rand() % (int)(BORDA_DIR - BORDA_ESQ - compInimigo));
            yInimigo = BORDA_CIMA + altInimigo / 2.0 + (rand() % (int)(BORDA_BAIXO - BORDA_CIMA - altInimigo));
            atualizaPosicaoInimigo(c, i, xInimigo, yInimigo);

            colisaoPlat = colidiuPlataformasInimigos(c, i);

            if(!colisaoPlat)
                colisaoInimigos = colidiuInimigos(c, i);
        }
    }
}

///----------------------------------------------------------------------------------///
///                                                                                  ///
///----------------------------------------------------------------------------------///

int main()
{
    //VARIAVEIS DA CONFIGURACAO
    sf::RenderWindow window(sf::VideoMode(800, 512), "Jogo Aula 03", sf::Style::Close);
    sf::View view(sf::Vector2f(0, 0), sf::Vector2f(VIEW_HEIGHT, VIEW_HEIGHT));
    srand(time(0));

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
    sf::Texture texturaFala;
    texturaFala.loadFromFile("texturas/fala.png");

    Mapa mapa(&texturaMapa);

    Jogador jogador(&texturaJogador, sf::Vector2u(13, 21), 0.3f, 180.0f);

    Inventario inventario(&texturaInventario, sf::Vector2u(17, 10), &texturaItem, sf::Vector2u(16, 16), &texturaIndice, sf::Vector2u(4, 1));

    Objetivo objetivo(&texturaObjetivo, sf::Vector2u(13, 21), &texturaInventario, sf::Vector2u(17, 10), &texturaItem, sf::Vector2u(16, 16));

    ////CRIA CENA

    float xPlataformas[NUMERO_PLATAFORMAS] = {500, 384,  480,  624,  864, 1056, 1248, 1296,  768, 1128, 1392};
    float compPlataformas[NUMERO_PLATAFORMAS] = {26, 96, 192, 288, 192, 192, 192, 192, 192, 144,  96};
    float yPlataformas[NUMERO_PLATAFORMAS] = {227, 384, 1104,  528,  624, 1296, 1200,  576, 1104,  888, 1512};
    float altPlataformas[NUMERO_PLATAFORMAS] =  {15, 96, 384, 192, 384, 384, 192, 192, 192, 144, 144};

    Cena dadosCena(xPlataformas, compPlataformas, yPlataformas, altPlataformas);

    ////PLATAFORMAS

    std::vector<Plataforma> plataformas;
    for(int i = 0; i < NUMERO_PLATAFORMAS; i++)
        plataformas.push_back(Plataforma(NULL, sf::Vector2f(obtemXPlataforma(&dadosCena, i), obtemYPlataforma(&dadosCena, i)), sf::Vector2f(obtemCompPlataforma(&dadosCena, i), obtemAltPlataforma(&dadosCena, i))));

    ////INIMIGO

    criaInimigos(&dadosCena);

    std::vector<Inimigo> inimigos;
    for(int i = 0; i < NUMERO_INIMIGOS; i++)
        inimigos.push_back(Inimigo(&texturaInimigo, sf::Vector2u(13, 21), 0.3f, dadosCena.getInimVel(i), sf::Vector2f(dadosCena.getInimX(i) , dadosCena.getInimY(i)), dadosCena.getInimMovX(i), dadosCena.getInimMovY(i)));

    ////ITENS

    criaItens(&dadosCena);

    std::vector<Item> itens;
    for(int i = 0; i < NUMERO_ITENS; i++)
        itens.push_back(Item(&texturaItem, sf::Vector2u(16, 16), sf::Vector2f(obtemXItem(&dadosCena, i), obtemYItem(&dadosCena, i)), dadosCena.getItemTipo(i)));

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
            if(item.getColisor().checaColisao(jogador.getColisor()) && sf::Keyboard::isKeyPressed(sf::Keyboard::E) && !item.getStatus() && !inventario.slotCheio(item.getTipo()))
            {
                item.coletou();
                inventario.pegouItem(item.getTipo());
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
                        break;
                    }
                }
            delay = 0.6;
            }
        }

        for(unsigned int i = 0; i < itens.size(); i++)
        {
            Item& item = itens[i];
            if(item.getColisor().checaColisao(objetivo.getColisorItens()) && !item.getStatus() && objetivo.getNumRecebidos() != 5)
            {
                item.coletou();
                objetivo.recebeuItem(item.getTipo());
            }
        }

        //COLISOES

        char direcao;

        objetivo.getColisorPlayer().checaColisaoJogadorPlataforma(jogador.getColisor());

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
                    jogador.setStatus(!jogador.getColisor().checaColisao(inimigo.getColisor()));
            }
        }

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

        for(unsigned int i = 0; i < plataformas.size(); i++)
        {
            Plataforma& plat = plataformas[i];
            plat.desenha(window);
        }

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
            objetivo.desenha(window);

        if(vivo)
            jogador.desenha(window);

        if(naFrente)
            objetivo.desenha(window);

        for(unsigned int i = 0; i < inimigos.size(); i++)
        {
            Inimigo& inimigo = inimigos[i];
            if(inimigo.getY() > jogador.getY())
                inimigo.desenha(window);
        }

        if(!objetivo.getTerminou())
            inventario.desenha(window, jogador.getPosicao());

        //FINAL DO JOGO

        if(objetivo.getTerminou())
        {
            objetivo.fimDeJogo();
            objetivo.desenhaFinal(window, view.getCenter());
        }

        ////
        window.display();
    }

    return 0;
}
