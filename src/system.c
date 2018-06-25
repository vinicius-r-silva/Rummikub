#include "libs/system.h"

void Deleta_Lista(LISTA_CARTAS_PTR *Lista){
    LISTA_CARTAS_PTR atual = *Lista;
    LISTA_CARTAS_PTR prev = NULL;

    while(atual != NULL){
        prev = atual;
        atual = atual->prox;
        free(prev);
    }
    *Lista = NULL;
}

void Cria_Baralho(LISTA_CARTAS_PTR *Baralho){
    Deleta_Lista(Baralho);
    bool Cartas_Usadas[14][8]; memset(Cartas_Usadas, 0, sizeof(bool));
    Cartas_Usadas[13][0] = 1;
    Cartas_Usadas[13][1] = 1;
    Cartas_Usadas[13][2] = 1;
    Cartas_Usadas[13][3] = 1;
    Cartas_Usadas[13][4] = 1;
    Cartas_Usadas[13][5] = 1;

    srand(time(NULL));
    int Naipe;
    int numero;

    int usadas = 0;
    while (usadas != 106){
        Naipe = rand() % 8;
        
        //if ()
    }
}