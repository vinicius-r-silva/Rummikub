#include <stdio.h>
#include <stdlib.h>

/*TO DO
colocar_carta_baralho
colocar_carta
tirar_carta
excluir_baralho
exibir_baralho
*/
struct lista_cartas {
    int naipe; //se for coringa = -1
    int numero;
    struct lista_cartas *prox;
};

typedef struct lista_cartas LISTA_CARTAS;
typedef LISTA_CARTAS *LISTA_CARTAS_PTR;

void colocar_carta_baralho (LISTA_CARTAS_PTR baralho, int naipe, int numero){
    //andar ate a ultima posição
    while (baralho != NULL){
        baralho = atual->prox;
    }
    LISTA_CARTAS_PTR atual = baralho;
    atual->prox = NULL;
    atual->naipe = naipe;
    atual->numero = numero;
    baralho->prox = atual;
}

void exibir_baralho (LISTA_CARTAS baralho){
    while(baralho != NULL){
        printf("%d%d", baralho->naipe, baralho->numero)


    }

}





int main()
{
}
