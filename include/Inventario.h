#ifndef INVENTARIO_H
#define INVENTARIO_H
#include <SFML/Graphics.hpp>


class Inventario
{
    public:
        Inventario(sf::Texture* texturaInventario, sf::Vector2u tamanhoDaImagemInventario, sf::Texture* texturaItem, sf::Vector2u tamanhoDaImagemItem, sf::Texture* texturaIndice, sf::Vector2u tamanhoDaImagemIndice);
        virtual ~Inventario();

        void pegouItem(char coletou);
        char soltouItem(int tecla);
        bool slotCheio(char coletou);

        void desenha(sf::RenderWindow& window, sf::Vector2f posicaoJogador);

    private:
        sf::RectangleShape corpoInventario;
        sf::IntRect inventarioRet;
        sf::RectangleShape corpoItem;
        sf::IntRect itemRet;
        sf::RectangleShape corpoIndice;
        sf::IntRect indiceRet;

        char coletados[10];
        int numColetados[9];
        int coletadosDiferentes;
};

#endif // INVENTARIO_H
