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

int Cena::colidiu(float itemX, float compItem, float itemY, float altItem, float objX, float compObj, float objY, float altObj)
{
    float deltaX = fabs(itemX - objX);
    float deltaY = fabs(itemY - objY);
    float distMinX = (compItem + compObj) / 2;
    float distMinY = (altItem + altObj) / 2;
    if((deltaX <= distMinX) && (deltaY <= distMinY))
        return 1;
    else
        return 0;
}

int Cena::colidiuPlataformasItens(int indiceItem)
{
    float platX, platY, compPlat, altPlat;
    float itemX = dadosItens[indiceItem].x;
    float itemY = dadosItens[indiceItem].y;
    float tamanhoItem = dadosItens[indiceItem].tamanho;

    for(int i = 0; i < NUMERO_PLATAFORMAS; i++)
    {
        platX = dadosPlataformas[i].x;
        platY = dadosPlataformas[i].y;
        compPlat = dadosPlataformas[i].comp;
        altPlat = dadosPlataformas[i].alt;
        if(colidiu(itemX, tamanhoItem, itemY, tamanhoItem, platX, compPlat, platY, altPlat))
            return 1;
    }
    return 0;
}

int Cena::colidiuPlataformasInimigos(int indiceInimigo)
{
    float platX, platY, compPlat, altPlat;
    float inimigoX = dadosInimigos[indiceInimigo].x;
    float inimigoY = dadosInimigos[indiceInimigo].y;;
    float inimigoComp = dadosInimigos[indiceInimigo].comp;
    float inimigoAlt = dadosInimigos[indiceInimigo].alt;

    for(int i = 0; i < NUMERO_PLATAFORMAS; i++)
    {
        platX = dadosPlataformas[i].x;
        platY = dadosPlataformas[i].y;
        compPlat = dadosPlataformas[i].comp;
        altPlat = dadosPlataformas[i].alt;
        if(colidiu(inimigoX, inimigoComp, inimigoY, inimigoAlt, platX, compPlat, platY, altPlat))
            return 1;
    }
    return 0;
}

int Cena::colidiuItens(int indiceItem)
{
    float item2X, item2Y, tamanhoItem2;
    float itemX = dadosItens[indiceItem].x;
    float itemY = dadosItens[indiceItem].y;
    float tamanhoItem = dadosItens[indiceItem].tamanho;

    for(int i = 0; i < indiceItem; i++)
    {
        item2X = dadosItens[i].x;
        item2Y = dadosItens[i].y;
        tamanhoItem2 = dadosItens[i].tamanho;
        if(colidiu(itemX, tamanhoItem, itemY, tamanhoItem, item2X, tamanhoItem2, item2Y, tamanhoItem2))
            return 1;
    }
    return 0;
}

int Cena::colidiuInimigos(int indiceInimigo)
{
    float inimigo2X, inimigo2Y, inimigo2Comp, inimigo2Alt;
    float inimigoX = dadosInimigos[indiceInimigo].x;
    float inimigoY = dadosInimigos[indiceInimigo].y;;
    float inimigoComp = dadosInimigos[indiceInimigo].comp;
    float inimigoAlt = dadosInimigos[indiceInimigo].alt;

    for(int i = 0; i < indiceInimigo; i++)
    {
        inimigo2X = dadosInimigos[i].x;
        inimigo2Y = dadosInimigos[i].y;
        inimigo2Comp = dadosInimigos[i].comp;
        inimigo2Alt = dadosInimigos[i].alt;
        if(colidiu(inimigoX, inimigoComp, inimigoY, inimigoAlt, inimigo2X, inimigo2Comp, inimigo2Y, inimigo2Alt))
            return 1;
    }
    return 0;
}

void Cena::criaItens()
{
    int colisaoPlat = 1;
    int colisaoItens = 1;

    float xItem, yItem, tamanhoItem;
    char tipoItem;

    for(int i = 0; i < NUMERO_ITENS; i++)
    {
        tipoItem = 'a' + (i%9);
        dadosItens[i].tipo = tipoItem;

        colisaoPlat = 1;
        colisaoItens = 1;

        while(colisaoPlat || colisaoItens)
        {
            tamanhoItem = dadosItens[i].tamanho;
            xItem = BORDA_ESQ + tamanhoItem / 2.0 + (rand() % (int)(BORDA_DIR - BORDA_ESQ - tamanhoItem));
            yItem = BORDA_CIMA + tamanhoItem / 2.0 + (rand() % (int)(BORDA_BAIXO - BORDA_CIMA - tamanhoItem));
            dadosItens[i].x = xItem;
            dadosItens[i].y = yItem;

            colisaoPlat = colidiuPlataformasItens(i);

            if(!colisaoPlat)
                colisaoItens = colidiuItens(i);
        }
    }
}

void Cena::criaInimigos()
{
    int colisaoPlat = 1;
    int colisaoInimigos = 1;

    float xInimigo, yInimigo, compInimigo, altInimigo, velInimigo;
    int movX, movY;

    for(int i = 0; i < NUMERO_INIMIGOS; i++)
    {
        movX = rand()%2;
        movY = !movX;
        dadosInimigos[i].movX = movX;
        dadosInimigos[i].movY = movY;

        velInimigo = 60 + rand()%60;
        dadosInimigos[i].vel = velInimigo;

        colisaoPlat = 1;
        colisaoInimigos = 1;

        while(colisaoPlat || colisaoInimigos)
        {
            compInimigo = dadosInimigos[i].comp;
            altInimigo = dadosInimigos[i].alt;
            xInimigo = BORDA_ESQ + compInimigo / 2.0 + (rand() % (int)(BORDA_DIR - BORDA_ESQ - compInimigo));
            yInimigo = BORDA_CIMA + altInimigo / 2.0 + (rand() % (int)(BORDA_BAIXO - BORDA_CIMA - altInimigo));
            dadosInimigos[i].x = xInimigo;
            dadosInimigos[i].y = yInimigo;

            colisaoPlat = colidiuPlataformasInimigos(i);

            if(!colisaoPlat)
                colisaoInimigos = colidiuInimigos(i);
        }
    }
}

Cena::~Cena()
{
    //dtor
}
