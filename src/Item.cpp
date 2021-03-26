#include "Item.h"

Item::Item(sf::Texture* textura, sf::Vector2u tamanhoDaImagem, sf::Vector2f posicao, char tipo)
{
    this->tipo = tipo;
    coletado = false;

    corpoItem.setSize(sf::Vector2f(35.0f, 35.0f));
    corpoItem.setOrigin(corpoItem.getSize() / 2.0f);
    corpoItem.setPosition(posicao);
    corpoItem.setTexture(textura);

    itemRet.width = textura->getSize().x / (float)tamanhoDaImagem.x;
    itemRet.height = textura->getSize().y / (float)tamanhoDaImagem.y;

    switch(tipo)
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
}

Item::~Item()
{
    //dtor
}

void Item::desenha(sf::RenderWindow& window)
{
    if(!coletado)
        window.draw(corpoItem);
}
