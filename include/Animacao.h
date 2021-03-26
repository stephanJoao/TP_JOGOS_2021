#ifndef ANIMACAO_H
#define ANIMACAO_H
#include <SFML/Graphics.hpp>

class Animacao
{
    ///FUNCOES
public:
    Animacao(sf::Texture* textura, sf::Vector2u tamanhoDaImagem, float tempoTroca);
    virtual ~Animacao();

    void atualiza(int linha, float deltaTempo, bool emMovimento, bool vivo);

    void setNumFrames(int numFrames) { tamanhoDaImagem.x = numFrames; };
    void setFrameAtual(int frame) { imagemAtual.x = frame; };

    ///VARIAVEIS
public:
    sf::IntRect frameRet;

private:
    sf::Vector2u tamanhoDaImagem;
    sf::Vector2u imagemAtual;

    bool morreu;

    float tempoTotal;
    float tempoTroca;
};

#endif // Animacao_H
