#include <stdio.h>
#include <stdlib.h>
#include "libs/interfaceIO.h"
#include "libs/system.h"
#include "libs/data.h"


int main(){
    LISTA_CARTAS_PTR Baralho = NULL;
    
    Cria_Baralho(&Baralho);

    Imprime(Baralho);
    
    printf("\n\n\n\n");
    Imprime_Ordenado(Baralho);
    
    return 0;
}