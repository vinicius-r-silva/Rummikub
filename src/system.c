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

//Troca a posição 1 com a 2
void trocar_posicao (LISTA_CARTAS_PTR *lista_cartas, int pos1, int pos2){
    //O esquerda fica a esquerda da posição que será trocada, já o trocada, aponta para a posição que mudará de lugar, e o direita fica a direita da posição
    LISTA_CARTAS_PTR esquerda1 = *lista_cartas;
    LISTA_CARTAS_PTR trocada1 = *lista_cartas;
    LISTA_CARTAS_PTR direita1 = *lista_cartas;
    LISTA_CARTAS_PTR esquerda2 = *lista_cartas;
    LISTA_CARTAS_PTR trocada2 = *lista_cartas;
    LISTA_CARTAS_PTR direita2 = *lista_cartas;


    //vai até as posições corretas
    if (pos1 == 1){
        direita1 = direita1->prox;
    }
    else {
        trocada1 = trocada1->prox;
        direita1 = direita1->prox;
        direita1 = direita1->prox;
        for (int i=0; i<pos1-1; i++){
            esquerda1 = esquerda1->prox;
            trocada1 = trocada1->prox;
            direita1 = direita1->prox;
        }
    }


    direita2 = direita2->prox;
    direita2 = direita2->prox;
    trocada2 = trocada2->prox;
    for (int j=0; j<pos2-1; j++){
        atual2 = atual2->prox;
        direita2 = direita2->prox;
        trocada2 = trocada2->prox;
    }
    //Execução da troca
    esquerda1->prox = trocada2;
    trocada2->prox = direita1;
    esquerda2->prox = trocada1;
    trocada1->prox = direita2;
}

void trocar_posicao (LISTA_CARTAS_PTR *lista_cartas, int pos1, int pos2){
    LISTA_CARTAS_PTR temp1 = *lista_cartas;
    LISTA_CARTAS_PTR temp2 = *lista_cartas;



}
//Tira a carta da posição 1 da mão do jogador e coloca na posição 2 do monte
void jogador_para_monte (LISTA_CARTAS_PTR *mao_jogador, LISTA_CARTAS_PTR *monte, int pos1, int pos2){
    LISTA_CARTAS_PTR lista_mao = *mao_jogador;
    LISTA_CARTAS_PTR lista_monte = *monte;


}


int main()
{
}
