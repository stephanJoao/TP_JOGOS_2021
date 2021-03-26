#include "Animacao.h"

Animacao::Animacao(sf::Texture* textura, sf::Vector2u tamanhoDaImagem, float tempoTroca)
{
    this->tamanhoDaImagem = tamanhoDaImagem;
    this->tempoTroca = tempoTroca;
    tempoTotal = 0.0f;
    imagemAtual.x = 0;

    frameRet.width = textura->getSize().x / (float)tamanhoDaImagem.x;
    frameRet.height = textura->getSize().y / (float)tamanhoDaImagem.y;
}

Animacao::~Animacao()
{
    //dtor
}

void Animacao::atualiza(int linha, float deltaTempo, bool emMovimento)
{
    imagemAtual.y = linha;
    tempoTotal += 5 * deltaTempo;

    if(tempoTotal >= tempoTroca)
    {
        tempoTotal -= tempoTroca;
        imagemAtual.x++;

        if(imagemAtual.x >= tamanhoDaImagem.x)
        {
            if(emMovimento)
                imagemAtual.x = 1;
            else
                imagemAtual.x = 0;
        }
    }

    frameRet.left = imagemAtual.x * frameRet.width;
    frameRet.width = abs(frameRet.width);
    frameRet.top = imagemAtual.y * frameRet.height;
}
