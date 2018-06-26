#include <stdio.h>
#include <stdlib.h>
#include "libs/interfaceIO.h"
#include "libs/system.h"
#include "libs/data.h"

int main(){
    LISTA_CARTAS_PTR Baralho = NULL;
    //LISTA_CARTAS_PTR mao = NULL;
    LISTA_MESA_PTR Mesa = NULL;
    
    //Cria_Baralho(&Baralho);
    Carrega_Baralho(&Baralho);

    Imprime(Baralho);
    
    printf("\n\n\n\n");
    //Imprime_Ordenado(Baralho);
    //printf("\n\n\n\n");
    int x;
    int cont;
    LISTA_MESA_PTR Mesa_atual = NULL;
    int define;
    

    while(Baralho != NULL){
        if (!ReadInt(&x))
            continue;
        
        mao_2_monte(&Baralho, &Mesa, Baralho->naipe, Baralho->numero, 1, 1);
        Mesa_atual = Mesa;
        while(Mesa_atual->prox != NULL)
            Mesa_atual = Mesa_atual->prox;

        for (cont = 1; cont < x; cont++){
            mao_2_monte(&Baralho, &Mesa_atual, Baralho->naipe, Baralho->numero, 1, 0);
        }

        Organiza_Mesa(&Mesa);

        Imprime_Mesa(&Mesa);
    }
    
    return 0;
}