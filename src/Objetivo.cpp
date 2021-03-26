#include "Objetivo.h"

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

void Objetivo::desenha(sf::RenderWindow& window)
{
    if(ganhou)
    {
        objetivoRet.left = 5 * objetivoRet.width;
        objetivoRet.top = 2 * objetivoRet.height;
        corpoObjetivo.setTextureRect(objetivoRet);
    }
    window.draw(corpoObjetivo);
    if(!terminou)
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

void Objetivo::desenhaFinal(sf::RenderWindow& window, sf::Vector2f posicao)
{
    corpoFala.setSize(sf::Vector2f(40.0f, 90.0f));
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
        corpoFala.setPosition(posicao.x - 80 + 40 * i, posicao.y);
        corpoFala.setTextureRect(falaRet);
        window.draw(corpoFala);
    }
    texto.setFont(fonte);
    texto.setFillColor(sf::Color::Black);
    texto.setCharacterSize(22);
    if(ganhou)
        texto.setString("Você ganhou!");
    else
        texto.setString("Você perdeu!");
    texto.setPosition(posicao.x - texto.getLocalBounds().width / 2, posicao.y - texto.getLocalBounds().height / 2 - 7);
    window.draw(texto);
}
