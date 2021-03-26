#ifndef MAPA_H
#define MAPA_H
#include <SFML/Graphics.hpp>
#define TAMANHO_MAPA_X 20
#define TAMANHO_MAPA_Y 20
#define TAMANHO_BLOCOS 48

using namespace std;

typedef struct
{
    sf::IntRect corpoBloco;
    sf::Vector2f posicaoBloco;
    sf::Vector2i posicaoNaImagem;
}Bloco;

class Mapa
{
    public:
        Mapa(sf::Texture *texturaMapa);
        virtual ~Mapa();
        void desenha(sf::RenderWindow& window);

    private:
        sf::Vector2i numBlocos;
        int tamanhoBlocos;
        sf::Vector2i tamanhoDaImagem;
        sf::RectangleShape textura;
        Bloco padrao;
        Bloco blocos[TAMANHO_MAPA_X][TAMANHO_MAPA_Y];
        int tipoBlocos[TAMANHO_MAPA_X][TAMANHO_MAPA_Y] = {
                                                            {2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1},
                                                            {1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2},
                                                            {2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1},
                                                            {1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2},
                                                            {2, 1, 2, 1, 6, 4, 6, 4, 6, 4, 6, 4, 6, 4, 6, 4, 2, 1, 2, 1},
                                                            {1, 2, 1, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 2, 1, 2},
                                                            {2, 1, 2, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 1, 2, 1},
                                                            {1, 2, 1, 6, 0, 0, 0, 7, 8, 0, 0, 0, 0, 0, 0, 0, 4, 2, 1, 2},
                                                            {2, 1, 2, 5, 0, 0, 0, 8, 7, 0, 0, 0, 0, 0, 0, 0, 3, 1, 2, 1},
                                                            {1, 2, 1, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 2, 1, 2},
                                                            {2, 1, 2, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 1, 2, 1},
                                                            {1, 2, 1, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 2, 1, 2},
                                                            {2, 1, 2, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 1, 2, 1},
                                                            {1, 2, 1, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 2, 1, 2},
                                                            {2, 1, 2, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 1, 2, 1},
                                                            {1, 2, 1, 2, 5, 3, 5, 3, 5, 3, 5, 3, 5, 3, 5, 3, 1, 2, 1, 2},
                                                            {2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1},
                                                            {1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2},
                                                            {2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1},
                                                            {1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2}
                                                         };
};
#endif // MAPA_H
