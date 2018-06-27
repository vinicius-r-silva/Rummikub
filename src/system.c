#include "libs/system.h"


void Cria_Baralho(LISTA_CARTAS_PTR *Baralho){
    bool Recursiva = false;
    if(*Baralho == NULL)
        Recursiva = true;

    srand(time(NULL));
    int Numero, Naipe;
    for(Naipe = 1; Naipe < 5; Naipe++){
        for(Numero = 1; Numero < 14; Numero++){
            Cria_Carta(Baralho, Naipe, Numero);
        }
    }
    Cria_Carta(Baralho, -1, -1);

    for(Naipe = 1; Naipe < 5; Naipe++){
        for(Numero = 1; Numero < 14; Numero++){
            TrocaCarta(Baralho, Naipe, rand() % 4 + 1 ,Numero, rand() % 13 + 1);
        }
    }
    TrocaCarta(Baralho, -1, rand() % 4 + 1 , -1, rand() % 13 + 1);

    if(Recursiva)
        Cria_Baralho(Baralho);
}


void Baralho_2_mao(LISTA_CARTAS_PTR *baralho, LISTA_CARTAS_PTR *mao){
    LISTA_CARTAS_PTR Carta = *baralho;
    if (Carta == NULL)
        return;
    
    *baralho = Carta->prox;
    Carta->prox = *mao;
    *mao = Carta;
}

void Imprime_mao_jogador(LISTA_CARTAS_PTR *mao){
    int Naipe, Numero;
    int x = INICIO_X_MAO, y = INICIO_Y_MAO;
    int cont;

    LISTA_CARTAS_PTR atual = *mao;
    while (atual != NULL){
        Naipe = atual->Naipe;
        Numero = atual->Numero;

        if(cont == N_MAX_COLUNAS){
            cont = 0;
            x = INICIO_X_MAO;
            y+= TAM_Y_CARTA + TAM_Y_ESPACO;
        }
        x += TAM_X_CARTA + TAM_X_ESPACO;

        


        cont++;
    }
}