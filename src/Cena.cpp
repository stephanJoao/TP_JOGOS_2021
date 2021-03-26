#include "Cena.h"

Cena::Cena(float platX[], float platComp[], float platY[], float platAlt[])
{
    for(int i = 0; i < NUMERO_PLATAFORMAS; i++)
    {
        dadosPlataformas[i].x = platX[i];
        dadosPlataformas[i].comp = platComp[i];
        dadosPlataformas[i].y = platY[i];
        dadosPlataformas[i].alt = platAlt[i];
    }
    for(int i = 0; i < NUMERO_ITENS; i++)
    {
        dadosItens[i].tamanho = 35;
    }
    for(int i = 0; i < NUMERO_INIMIGOS; i++)
    {
        dadosInimigos[i].comp = 30;
        dadosInimigos[i].alt = 15;
    }
}

Cena::~Cena()
{
    //dtor
}
