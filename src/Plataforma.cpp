#include "Plataforma.h"

Plataforma::Plataforma(sf::Texture* textura, sf::Vector2f posicao, sf::Vector2f tamanho)
{
    corpo.setSize(tamanho);
    corpo.setOrigin(tamanho / 2.0f);
    corpo.setTexture(textura);
    corpo.setPosition(posicao);
}

Plataforma::~Plataforma()
{
    //dtor
}

void Plataforma::desenha(sf::RenderWindow& window)
{
    //window.draw(corpo);
}
