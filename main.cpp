#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Jogador.h"
#include "Inimigo.h"
#include "Plataforma.h"
#include "Mapa.h"
#include "Item.h"
#include "Inventario.h"
#include "Objetivo.h"
#include "Cena.h"

#define MAX_RECORDES 5

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

float obtemXJogador(Jogador* j)
{
    return j->getX();
}

float obtemYJogador(Jogador* j)
{
    return j->getY();
}

void gravarRecordes(FILE *rec, float recordes[], int numeroRecordes)
{
    rec = fopen("recordes.txt", "wt");

    if (rec == NULL)
    {
        printf("Problemas ao abrir o arquivo\n");
    }

    fprintf(rec, "%d\n", numeroRecordes);

    for(int i = 0; i < numeroRecordes; i++)
        fprintf(rec, "%f\n", recordes[i]);

    fclose(rec);
}

///----------------------------------------------------------------------------------///
///                                     EXERCICIOS                                   ///
///----------------------------------------------------------------------------------///

///EXERCICIO 1

float distancia(float x1, float y1, float x2, float y2)
{
    float distanciaPontos = sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
    return distanciaPontos;
}

///EXERCICIO 2

int adicionaEventos(Jogador* j, float x[], float y[], int numeroEventos)
{
    x[numeroEventos] = obtemXJogador(j);
    y[numeroEventos] = obtemYJogador(j);
    numeroEventos++;
    return numeroEventos;
}

///EXERCICIO 3

float calculaDistanciaTotal(float x[], float y[], int numeroEventos)
{
    float distanciaTotal = 0;
    float dist;
    for(int i = 0; i < numeroEventos - 1; i++)
    {
        dist = distancia(x[i], y[i], x[i + 1], y[i + 1]);
        distanciaTotal += dist;
    }
    return distanciaTotal;
}

///EXERCICIO 4

float calculaPontos(float x[], float y[], int numeroEventos, float tempoTotal)
{
    float dist = calculaDistanciaTotal(x, y, numeroEventos);
    float pontos = dist / tempoTotal;
    return pontos;
}

///EXERCICIO 5

int organizaRecordes(float recordes[], int numeroRecordes, float pontos)
{
    int indiceDoMenor = -1;
    for(int i = 0; i < numeroRecordes; i++)
    {
        if(recordes[i] < pontos)
        {
            indiceDoMenor = i;
            break;
        }
    }
    if(indiceDoMenor != -1)
    {
        for(int i = MAX_RECORDES - 1; i > indiceDoMenor; i--)
            recordes[i] = recordes[i - 1];
        recordes[indiceDoMenor] = pontos;
        if(numeroRecordes < 5)
            numeroRecordes++;
    }
    else
    {
        if(numeroRecordes < 5)
        {
            recordes[numeroRecordes] = pontos;
            numeroRecordes++;
        }
    }
    return numeroRecordes;
}

///----------------------------------------------------------------------------------///
///                                                                                  ///
///----------------------------------------------------------------------------------///

int main()
{
    //VARIAVEIS DA CONFIGURACAO
    sf::RenderWindow window(sf::VideoMode(800, 512), "Jogo Aula 04", sf::Style::Close);
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

    ////REGISTRO DE EVENTOS

    float xEventos[1000];
    float yEventos[1000];
    int numeroEventos = 0;
    numeroEventos = adicionaEventos(&jogador, xEventos, yEventos, numeroEventos);

    ////RECORDES

    float recordes[5] = {0, 0, 0, 0, 0};
    int numeroRecordes;
    bool recordeAdicionado = false;
    bool pontosCalculados = false;
    bool desenhaRecordes = false;
    float delayRecordes;

    ////ARQUIVO RECORDES

    FILE *rec;

    rec = fopen("recordes.txt", "rt");

    if (rec == NULL)
    {
        printf("Problemas ao abrir o arquivo\n");
        return 0;
    }

    fscanf(rec, "%d", &numeroRecordes);

    for(int i = 0; i < numeroRecordes; i++)
    {
        fscanf(rec, "%f", &recordes[i]);
    }

    fclose(rec);

    ////TEMPO

    float tempoTotal = 0.01;
    float tempoAtual = 0.01;
    bool tempoAtualRecebido = false;

    ////CRIA CENA

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

    dadosCena.criaItens();
    std::vector<Item> itens;
    for(int i = 0; i < NUMERO_ITENS; i++)
        itens.push_back(Item(&texturaItem, sf::Vector2u(16, 16), sf::Vector2f(dadosCena.getItemX(i), dadosCena.getItemY(i)), dadosCena.getItemTipo(i)));

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
        //cout << tempoTotal << endl;

        if(delayRecordes > 0)
            delayRecordes -= deltaTempo;
        else
            delayRecordes = 0;

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
                numeroEventos = adicionaEventos(&jogador, xEventos, yEventos, numeroEventos);
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
                numeroEventos = adicionaEventos(&jogador, xEventos, yEventos, numeroEventos);
            }
        }

        for(unsigned int i = 0; i < itens.size(); i++)
        {
            Item& item = itens[i];
            if(item.getColisor().checaColisao(objetivo.getColisorItens()) && !item.getStatus() && objetivo.getNumRecebidos() != 5)
            {
                item.coletou();
                objetivo.recebeuItem(item.getTipo());
                numeroEventos = adicionaEventos(&jogador, xEventos, yEventos, numeroEventos);
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
                {
                    bool status = jogador.getColisor().checaColisao(inimigo.getColisor());
                    if(status)
                    {
                        jogador.setStatus(!status);
                        numeroEventos = adicionaEventos(&jogador, xEventos, yEventos, numeroEventos);
                    }
                }
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
            inventario.desenha(window, jogador.getPosicao());

        //FINAL DO JOGO

        if(!jogador.getStatus() && !objetivo.getTerminou())
        {
            float p;
            if(!tempoAtualRecebido)
            {
                tempoAtual = tempoTotal;
                tempoAtualRecebido = true;
            }
            if(!pontosCalculados)
            {
                p = calculaPontos(xEventos, yEventos, numeroEventos, tempoAtual) * 0.5;
                pontosCalculados = true;
            }
            if(!recordeAdicionado)
            {
                numeroRecordes = organizaRecordes(recordes, numeroRecordes, p);
                recordeAdicionado = true;
                gravarRecordes(rec, recordes, numeroRecordes);
            }

            objetivo.desenhaFinal(window, view.getCenter(), p, desenhaRecordes);

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Tab))
                desenhaRecordes = true;
            else
                desenhaRecordes = false;
            if(desenhaRecordes)
                objetivo.desenhaRecordes(window, view.getCenter(), numeroRecordes, recordes);
        }


        if(objetivo.getTerminou())
        {
            float p;
            if(!tempoAtualRecebido)
            {
                tempoAtual = tempoTotal;
                tempoAtualRecebido = true;
            }
            if(!pontosCalculados)
            {
                p = calculaPontos(xEventos, yEventos, numeroEventos, tempoAtual) * 2.0;
                pontosCalculados = true;
            }
            if(!recordeAdicionado)
            {
                numeroRecordes = organizaRecordes(recordes, numeroRecordes, p);
                recordeAdicionado = true;
                gravarRecordes(rec, recordes, numeroRecordes);
            }

            objetivo.fimDeJogo();
            objetivo.desenhaFinal(window, view.getCenter(), p, desenhaRecordes);

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Tab))
                desenhaRecordes = true;
            else
                desenhaRecordes = false;
            if(desenhaRecordes)
                objetivo.desenhaRecordes(window, view.getCenter(), numeroRecordes, recordes);
        }

        ////
        window.display();
    }

    return 0;
}
