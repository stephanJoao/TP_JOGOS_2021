#include "Animacao.h"

Animacao::Animacao(sf::Texture* textura, sf::Vector2u tamanhoDaImagem, float tempoTroca)
{
    morreu = false;

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

void Animacao::atualiza(int linha, float deltaTempo, bool emMovimento, bool vivo)
{
    imagemAtual.y = linha;
    tempoTotal += 5 * deltaTempo;

    if(!vivo && !morreu)
    {
        imagemAtual.x = 0;
        morreu = true;
    }

    if(tempoTotal >= tempoTroca)
    {
        tempoTotal -= tempoTroca;
        if(!(!vivo && imagemAtual.x == 5))
            imagemAtual.x++;

        if((imagemAtual.x >= tamanhoDaImagem.x) && vivo)
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
