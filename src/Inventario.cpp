#include "Inventario.h"

Inventario::Inventario(sf::Texture* texturaInventario, sf::Vector2u tamanhoDaImagemInventario, sf::Texture* texturaItem, sf::Vector2u tamanhoDaImagemItem, sf::Texture* texturaIndice, sf::Vector2u tamanhoDaImagemIndice)
{
    coletados[0] = '\0';
    for(int i = 0; i < 9; i++)
        numColetados[i] = 0;
    coletadosDiferentes = 0;

    //QUADRADOS INVENTARIO
    corpoInventario.setSize(sf::Vector2f(32.0f, 32.0f));
    corpoInventario.setTexture(texturaInventario);

    inventarioRet.width = texturaInventario->getSize().x / (float)tamanhoDaImagemInventario.x;
    inventarioRet.height = texturaInventario->getSize().y / (float)tamanhoDaImagemInventario.y;
    corpoInventario.setTextureRect(inventarioRet);

    //ITENS INVENTARIO
    corpoItem.setSize(sf::Vector2f(32.0f, 32.0f));
    corpoItem.setTexture(texturaItem);

    itemRet.width = texturaItem->getSize().x / (float)tamanhoDaImagemItem.x;
    itemRet.height = texturaItem->getSize().y / (float)tamanhoDaImagemItem.y;
    corpoItem.setTextureRect(itemRet);

    //INDICE INVENTARIO
    corpoIndice.setSize(sf::Vector2f(16.0f, 16.0f));
    corpoIndice.setTexture(texturaIndice);

    indiceRet.width = texturaIndice->getSize().x / (float)tamanhoDaImagemIndice.x;
    indiceRet.height = texturaIndice->getSize().y / (float)tamanhoDaImagemIndice.y;
    corpoIndice.setTextureRect(indiceRet);
}

Inventario::~Inventario()
{
    //dtor
}

void Inventario::pegouItem(char coletou)
{
    if(numColetados[coletou - 'a'] == 0)
    {
        coletados[coletadosDiferentes] = coletou;
        coletados[coletadosDiferentes + 1] = '\0';
        coletadosDiferentes++;
    }
    numColetados[coletou - 'a']++;
}

char Inventario::soltouItem(int tecla)
{
    if(tecla <= coletadosDiferentes)
    {
        int indice = coletados[tecla - 1] - 'a';
        char tipo = coletados[tecla - 1];

        if(numColetados[indice] == 1)
        {
            for(int i = tecla - 1; coletados[i] != '\0'; i++)
            {
                coletados[i] = coletados[i + 1];
            }
            coletadosDiferentes--;
        }
        if(numColetados[indice] > 0)
            numColetados[indice]--;

        return tipo;
    }
    else
        return ' ';
}

void Inventario::desenha(sf::RenderWindow& window, sf::Vector2f posicao)
{
    for(int i = 0; i < 9; i++)
    {
        //cout <<
        corpoInventario.setPosition(posicao.x - 240 + (corpoInventario.getSize().x * i), posicao.y + 120);
        window.draw(corpoInventario);

        if(i < coletadosDiferentes)
        {
            corpoItem.setPosition(posicao.x - 240 + (corpoInventario.getSize().x * i), posicao.y + 112);
            switch(coletados[i])
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
            window.draw(corpoItem);

            corpoIndice.setPosition(posicao.x - 242 + (corpoInventario.getSize().x * i), posicao.y + 116);
            indiceRet.left = numColetados[coletados[i] - 'a'] * indiceRet.width;
            corpoIndice.setTextureRect(indiceRet);
            window.draw(corpoIndice);
        }
    }
}
