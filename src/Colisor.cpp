#include "Colisor.h"

Colisor::Colisor(sf::RectangleShape& corpo) :
    corpo(corpo)
{
    //ctor
}

Colisor::~Colisor()
{
    //dtor
}

bool Colisor::checaColisao(Colisor outro, char* direcao)
{
    sf::Vector2f posicaoOutro = outro.getPosicao();
    sf::Vector2f metadeOutro = outro.getMetade();
    sf::Vector2f posicao = getPosicao();
    sf::Vector2f metade = getMetade();

    float deltaX = posicaoOutro.x - posicao.x;
    float deltaY = posicaoOutro.y - posicao.y;

    float intersecaoX = abs(deltaX) - (metadeOutro.x + metade.x);
    float intersecaoY = abs(deltaY) - (metadeOutro.y + metade.y);

    if(intersecaoX < 0.0f && intersecaoY < 0.0f)
    {
        if(intersecaoX > intersecaoY)
        {
            if(deltaX > 0.0f)
            {
                outro.Move(-intersecaoX, 0.0f);
                *direcao = 'e';
            }
            else
            {
                outro.Move(intersecaoX, 0.0f);
                *direcao = 'd';
            }
        }
        else
        {
            if(deltaY > 0.0f)
            {
                outro.Move(0.0f, -intersecaoY);
                *direcao = 'b';
            }
            else
            {
                outro.Move(0.0f, intersecaoY);
                *direcao = 'c';
            }
        }
        return true;
    }
    return false;
}

