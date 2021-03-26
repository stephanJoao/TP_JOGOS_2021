#ifndef CENA_H
#define CENA_H
#include <math.h>
#include <cstdlib>

#define BORDA_ESQ 240
#define BORDA_DIR 1584
#define BORDA_CIMA 192
#define BORDA_BAIXO 1632

#define NUMERO_PLATAFORMAS 11
#define NUMERO_ITENS 27
#define NUMERO_INIMIGOS 30

typedef struct
{
    float x;
    float y;
    float comp;
    float alt;
}DadosPlataforma;

typedef struct
{
    float x;
    float y;
    float tamanho;
    char tipo;
}DadosItem;

typedef struct
{
    float x;
    float y;
    float comp;
    float alt;
    float vel;
    int movX;
    int movY;
}DadosInimigo;

class Cena
{
    public:
        Cena(float platX[], float platComp[], float platY[], float platAlt[]);
        virtual ~Cena();

        float getPlatX(int i){ return dadosPlataformas[i].x; }
        float getPlatComp(int i){ return dadosPlataformas[i].comp; }
        float getPlatY(int i){ return dadosPlataformas[i].y; }
        float getPlatAlt(int i){ return dadosPlataformas[i].alt; }

        float getItemX(int i){ return dadosItens[i].x; }
        float getItemY(int i){ return dadosItens[i].y; }
        float getItemTamanho(int i){ return dadosItens[i].tamanho; }
        char getItemTipo(int i){ return dadosItens[i].tipo; }
        void setItemX(int i, float a) { dadosItens[i].x = a; }
        void setItemY(int i, float a) { dadosItens[i].y = a; }
        void setItemTipo(int i, char a) { dadosItens[i].tipo = a; }

        float getInimX(int i){ return dadosInimigos[i].x; }
        float getInimComp(int i){ return dadosInimigos[i].comp; }
        float getInimY(int i){ return dadosInimigos[i].y; }
        float getInimAlt(int i){ return dadosInimigos[i].alt; }
        float getInimVel(int i){ return dadosInimigos[i].vel; }
        int getInimMovX(int i){ return dadosInimigos[i].movX; }
        int getInimMovY(int i){ return dadosInimigos[i].movY; }
        void setInimX(int i, float a) { dadosInimigos[i].x = a; }
        void setInimY(int i, float a) { dadosInimigos[i].y = a; }
        void setInimVel(int i, float a) { dadosInimigos[i].vel = a; }
        void setInimMovX(int i, int a) { dadosInimigos[i].movX = a; }
        void setInimMovY(int i, int a) { dadosInimigos[i].movY = a; }

        int colidiu(float itemX, float compItem, float itemY, float altItem, float objX, float compObj, float objY, float altObj);
        int colidiuPlataformasItens(int indiceItem);
        int colidiuPlataformasInimigos(int indiceInimigo);
        int colidiuItens(int indiceItem);
        int colidiuInimigos(int indiceInimigo);
        void criaItens();
        void criaInimigos();

    private:
        DadosPlataforma dadosPlataformas[NUMERO_PLATAFORMAS];
        DadosItem dadosItens[NUMERO_ITENS];
        DadosInimigo dadosInimigos[NUMERO_INIMIGOS];
};

#endif // CENA_H
