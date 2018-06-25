#include <stdio.h>
#include <stdlib.h>

/*TO DO
baralho_para_jogador DONE
jogador_para_monte
trocar_posicao DONE
colocar_carta_na_posicao
tirar_carta DONE
exibir_baralho DONE
*/
struct lista_cartas {
    int naipe; //se for coringa = -1
    int numero;
    struct lista_cartas *prox;
};

typedef struct lista_cartas LISTA_CARTAS;
typedef LISTA_CARTAS *LISTA_CARTAS_PTR;

//Tira a carta do baralho e coloca na mao do jogador, se
void baralho_para_jogador (LISTA_CARTAS_PTR *baralho, LISTA_CARTAS_PTR *mao_jogador){
    if (*baralho == NULL) return;

    LISTA_CARTAS_PTR atual_baralho = *baralho;
    LISTA_CARTAS_PTR atual_mao_jogador = *mao_jogador;

    //andar ate a ultima posicao
    while (atual_mao_jogador != NULL){
        atual_mao_jogador = atual_mao_jogador->prox;
    }

    atual_mao_jogador->prox = *baralho;
    *baralho = (*baralho)->prox;
}

void exibir_baralho (LISTA_CARTAS_PTR baralho){
    while(baralho != NULL){
        printf("%d%d ", baralho->naipe, baralho->numero);
        baralho = baralho->prox;
    }
}

//retira a carta da posição dada da lista, começando no 1
void tirar_carta (LISTA_CARTAS_PTR *lista_cartas, int pos){
    LISTA_CARTAS_PTR atual = *lista_cartas;
    if (pos == 1){
        *lista_cartas = *lista_cartas->prox;
        return;
    }

    for (int i=0; i<pos-1; i++){
        atual = atual->prox;
    }
    //Se não existir a posição não faz nada
    if (atual == NULL) return;
    LISTA_CARTAS_PTR temp = atual->prox;
    atual->prox = temp->prox;
}

}
//Tira a carta da posição 1 da mão do jogador e coloca na posição 2 do monte
void jogador_para_monte (LISTA_CARTAS_PTR *mao_jogador, LISTA_CARTAS_PTR *monte, int pos1, int pos2){
    LISTA_CARTAS_PTR lista_mao = *mao_jogador;
    LISTA_CARTAS_PTR lista_monte = *monte;


}


int main()
{
}
