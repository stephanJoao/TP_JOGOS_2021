#ifndef COLISOR_H
#define COLISOR_H
#include <SFML/Graphics.hpp>

class Colisor
{
public:
    Colisor(sf::RectangleShape& corpo);
    virtual ~Colisor();

    bool checaColisao(Colisor outro);
    void checaColisaoJogadorPlataforma(Colisor outro);
    char checaColisaoInimigoPlataforma(Colisor outro);

    void Move(float dx, float dy) { corpo.move(dx, dy); };

    sf::Vector2f getPosicao() { return corpo.getPosition(); };

    sf::Vector2f getMetade() { return corpo.getSize() / 2.0f; };

private:
    sf::RectangleShape& corpo;
};

#endif // Colisor_H
