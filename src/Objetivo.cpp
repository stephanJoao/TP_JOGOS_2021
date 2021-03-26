#include "Objetivo.h"
#include <sstream>


Objetivo::Objetivo(sf::Texture* texturaObjetivo, sf::Vector2u tamanhoDaImagemObjetivo, sf::Texture* texturaFala, sf::Vector2u tamanhoDaImagemFala, sf::Texture* texturaItem, sf::Vector2u tamanhoDaImagemItem)
{
    fonte.loadFromFile("bitmapFont.ttf");

    terminou = false;
    ganhou = false;

    for(int i = 0; i < 9; i++)
        letras[i] = 'a' + i;
    letras[9] = '\0';

    int indice;
    for(int i = 0; i < 5; i++)
    {
        indice = rand() % (9 - i);
        resposta[i] = letras[indice];
        for(int i = indice; letras[i] != '\0'; i++)
        {
            letras[i] = letras[i + 1];
        }
    }
    resposta[5] = '\0';

    recebidos[0] = '\0';
    numRecebidos = 0;

    //OBJETIVO
    corpoObjetivo.setPosition(500.0, 200.0);
    corpoObjetivo.setSize(sf::Vector2f(64.0f, 64.0f));
    corpoObjetivo.setOrigin(corpoObjetivo.getSize() / 2.0f);
    corpoObjetivo.setTexture(texturaObjetivo);

    objetivoRet.width = texturaObjetivo->getSize().x / (float)tamanhoDaImagemObjetivo.x;
    objetivoRet.height = texturaObjetivo->getSize().y / (float)tamanhoDaImagemObjetivo.y;
    objetivoRet.left = 0 * objetivoRet.width;
    objetivoRet.top = 2 * objetivoRet.height;
    corpoObjetivo.setTextureRect(objetivoRet);

    //FALA OBJETIVO
    corpoFala.setSize(sf::Vector2f(35.0f, 90.0f));
    corpoFala.setTexture(texturaFala);
    corpoFala.setOrigin(corpoFala.getSize() / 2.0f);
    corpoFala.setPosition(corpoObjetivo.getPosition().x - 64, corpoObjetivo.getPosition().y - 48);

    falaRet.width = texturaFala->getSize().x / (float)tamanhoDaImagemFala.x;
    falaRet.height = texturaFala->getSize().y / (float)tamanhoDaImagemFala.y * 3;

    //RECORDES
    corpoRec.setSize(sf::Vector2f(35.0f, 35.0f));
    corpoRec.setTexture(texturaFala);
    corpoRec.setOrigin(corpoRec.getSize() / 2.0f);
    corpoRec.setPosition(corpoObjetivo.getPosition().x - 64, corpoObjetivo.getPosition().y - 48);

    recRet.width = texturaFala->getSize().x / (float)tamanhoDaImagemFala.x;
    recRet.height = texturaFala->getSize().y / (float)tamanhoDaImagemFala.y;

    //ITEM OBJETIVO
    corpoItem.setSize(sf::Vector2f(32.0f, 32.0f));
    corpoItem.setTexture(texturaItem);
    corpoItem.setOrigin(corpoItem.getSize() / 2.0f);

    itemRet.width = texturaItem->getSize().x / (float)tamanhoDaImagemItem.x;
    itemRet.height = texturaItem->getSize().y / (float)tamanhoDaImagemItem.y;

    //CORPO
    corpo.setSize(sf::Vector2f(26.0f, 15.0f));
    corpo.setOrigin(corpo.getSize() / 2.0f);
    corpo.setPosition(corpoObjetivo.getPosition().x, corpoObjetivo.getPosition().y + 27);
}

Objetivo::~Objetivo()
{
    //dtor
}

void Objetivo::recebeuItem(char recebeu)
{
    recebidos[numRecebidos] = recebeu;
    recebidos[numRecebidos + 1] = '\0';
    numRecebidos++;

    if(numRecebidos == 5)
        terminou = true;
}

void Objetivo::fimDeJogo()
{
    ganhou = true;
    for(int i = 0; i < 5; i++)
    {
        if(recebidos[i] != resposta[i])
        {
            ganhou = false;
            break;
        }
    }
}

void Objetivo::desenha(sf::RenderWindow& window, bool vivo)
{
    if(ganhou)
    {
        objetivoRet.left = 5 * objetivoRet.width;
        objetivoRet.top = 2 * objetivoRet.height;
        corpoObjetivo.setTextureRect(objetivoRet);
    }
    window.draw(corpoObjetivo);
    if(!terminou && vivo)
    {
        for(int i = 0; i < 5; i++)
        {
            if(i == 0)
            {
                falaRet.left = 11 * falaRet.width;
                falaRet.top = 1 * falaRet.height / 3;
            }
            else if(i == 4)
            {
                falaRet.left = 13 * falaRet.width;
                falaRet.top = 1 * falaRet.height / 3;
            }
            else
            {
                falaRet.left = 12 * falaRet.width;
                falaRet.top = 1 * falaRet.height / 3;
            }
            corpoFala.setPosition(corpoObjetivo.getPosition().x - 70 + 35 * i, corpoObjetivo.getPosition().y - 67);
            corpoFala.setTextureRect(falaRet);
            window.draw(corpoFala);

            switch(resposta[i])
            {
                case 'a':
                    itemRet.left = 12 * itemRet.width;
                    itemRet.top = 3 * itemRet.height;
                    break;
                case 'b':
                    itemRet.left = 12 * itemRet.width;
                    itemRet.top = 4 * itemRet.height;
                    break;
                case 'c':
                    itemRet.left = 12 * itemRet.width;
                    itemRet.top = 5 * itemRet.height;
                    break;
                case 'd':
                    itemRet.left = 13 * itemRet.width;
                    itemRet.top = 6 * itemRet.height;
                    break;
                case 'e':
                    itemRet.left = 13 * itemRet.width;
                    itemRet.top = 5 * itemRet.height;
                    break;
                case 'f':
                    itemRet.left = 9 * itemRet.width;
                    itemRet.top = 3 * itemRet.height;
                    break;
                case 'g':
                    itemRet.left = 3 * itemRet.width;
                    itemRet.top = 5 * itemRet.height;
                    break;
                case 'h':
                    itemRet.left = 4 * itemRet.width;
                    itemRet.top = 5 * itemRet.height;
                    break;
                case 'i':
                    itemRet.left = 5 * itemRet.width;
                    itemRet.top = 5 * itemRet.height;
                    break;
                default:
                    break;
            }
            corpoItem.setTextureRect(itemRet);
            corpoItem.setPosition(corpoObjetivo.getPosition().x - 64 + 32 * i, corpoObjetivo.getPosition().y - 73);
            if(recebidos[i] != resposta[i])
                window.draw(corpoItem);
        }
    }
}

void Objetivo::desenhaFinal(sf::RenderWindow& window, sf::Vector2f posicao, float p, bool desenhaRecordes)
{
    corpoFala.setSize(sf::Vector2f(40.0f, 150.0f));
    for(int i = 0; i < 5; i++)
    {
        if(i == 0)
        {
            falaRet.left = 11 * falaRet.width;
            falaRet.top = 1 * falaRet.height / 3;
        }
        else if(i == 4)
        {
            falaRet.left = 13 * falaRet.width;
            falaRet.top = 1 * falaRet.height / 3;
        }
        else
        {
            falaRet.left = 12 * falaRet.width;
            falaRet.top = 1 * falaRet.height / 3;
        }
        corpoFala.setPosition(posicao.x - 80 + 40 * i, posicao.y - 15);
        corpoFala.setTextureRect(falaRet);
        window.draw(corpoFala);
    }

    texto.setFont(fonte);
    pontos.setFont(fonte);
    texto.setFillColor(sf::Color::Black);
    pontos.setFillColor(sf::Color::Black);
    texto.setCharacterSize(22);
    pontos.setCharacterSize(16);

    if(ganhou)
        texto.setString("Você ganhou!");
    else
        texto.setString("Você perdeu!");

    std::string a = "Pontos: ";
    p = ((int)(p * 100)) / 100.0;
    std::ostringstream ss;
    ss << p;
    std::string b(ss.str());
    pontos.setString(a + b);
    texto.setPosition(posicao.x - texto.getLocalBounds().width / 2, posicao.y - texto.getLocalBounds().height / 2 - 7);
    pontos.setPosition(posicao.x - pontos.getLocalBounds().width / 2, posicao.y - pontos.getLocalBounds().height / 2 + 22);
    window.draw(texto);
    window.draw(pontos);

    if(!desenhaRecordes)
    {
        texto.setFillColor(sf::Color::White);
        texto.setString("Para ver os recordes segure TAB");
        texto.setPosition(posicao.x - texto.getLocalBounds().width / 2, posicao.y - texto.getLocalBounds().height / 2 + 115);
        window.draw(texto);
    }
}

void Objetivo::desenhaRecordes(sf::RenderWindow& window, sf::Vector2f posicao, int numRecordes, float recordes[])
{
    corpoRec.setSize(sf::Vector2f(40.0f, 40.0f));
    int linhas = 8, colunas = 6;
    float posicaoX = posicao.x + corpoRec.getSize().x / 2 - corpoRec.getSize().x * ((float)colunas / 2.0);
    float posicaoY = posicao.y + corpoRec.getSize().y / 2 - corpoRec.getSize().y * ((float)linhas / 2.0);

    for(int i = 0; i < colunas; i++)
    {
        if(i == 0)
            recRet.left = 11 * recRet.width;
        else if(i == colunas - 1)
            recRet.left = 13 * recRet.width;
        else
            recRet.left = 12 * recRet.width;

        for(int j = 0; j < linhas; j++)
        {
            if(j == 0)
                recRet.top = 1 * recRet.height;
            else if(j == linhas - 1)
                recRet.top = 3 * recRet.height;
            else
                recRet.top = 2 * recRet.height;

            corpoRec.setPosition(posicaoX + corpoRec.getSize().x * i, posicaoY + corpoRec.getSize().y * j);
            corpoRec.setTextureRect(recRet);
            window.draw(corpoRec);
        }
    }

    recorde.setFont(fonte);
    recorde.setFillColor(sf::Color::Black);
    recorde.setCharacterSize(22);
    recorde.setString("Recordes");
    recorde.setPosition(posicao.x - recorde.getLocalBounds().width / 2, posicaoY + 20);
    window.draw(recorde);

    for(int i = 0; i < numRecordes; i++)
    {
        std::string b = "º - ";
        std::ostringstream s1;
        s1 << i + 1;
        std::string a(s1.str());
        std::ostringstream s2;
        s2 << recordes[i];
        std::string c(s2.str());
        recorde.setString(a + b + c);
        recorde.setPosition(posicaoX + 10, posicaoY + 60 + i * 40);
        window.draw(recorde);
    }
}
