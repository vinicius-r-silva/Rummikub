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

void Cria_Carta(LISTA_CARTAS_PTR *Baralho, int Naipe, int Numero){
    if (Naipe > 4 || Numero > 13)
        return;

    LISTA_CARTAS_PTR nova = (LISTA_CARTAS_PTR)malloc(sizeof(LISTA_CARTAS));
    nova->naipe = Naipe;
    nova->numero = Numero;
    nova->prox = *Baralho;
    *Baralho = nova;
}

LISTA_CARTAS_PTR Busca_Carta(LISTA_CARTAS_PTR *Baralho, int Naipe, int Numero){
    LISTA_CARTAS_PTR atual = *Baralho;
    while(atual != NULL){
        if(atual->naipe == Naipe && atual->numero == Numero)
            return atual;
        atual = atual->prox;
    }
    return NULL;
}

void TrocaCarta(LISTA_CARTAS_PTR *Baralho, int Naipe_1, int Naipe_2, int Num_1, int Num_2){
    LISTA_CARTAS_PTR Carta1 = Busca_Carta(Baralho, Naipe_1, Num_1);
    LISTA_CARTAS_PTR Carta2 = Busca_Carta(Baralho, Naipe_2, Num_2);

    if(Carta1 != NULL){
        Carta1->numero = Num_2;
        Carta1->naipe = Naipe_2;
    } else
        printf("Erro: Carta 1 não encontrada\n");

    if(Carta2 != NULL){
        Carta2->numero = Num_1;
        Carta2->naipe = Naipe_1;
    }else
        printf("Erro: Carta 2 não encontrada\n");
}

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


//-----------------------FUNÇÕES INUTEIS---------------------------------------------------------------//
void Imprime(LISTA_CARTAS_PTR Baralho){
    int cont = 0;
    while(Baralho != NULL){
        printf("%2d  -  %d | %d\n", cont, Baralho->numero, Baralho->naipe);
        cont++;
        Baralho = Baralho->prox;
    }
    printf("\n");
}

void Imprime_Ordenado(LISTA_CARTAS_PTR Baralho){
    int Naipe;
    int Numero;
    LISTA_CARTAS_PTR Atual;

    for (Naipe = 0; Naipe < 5; Naipe++){
        for(Numero = 0; Numero < 14; Numero++){
            Atual = Baralho;
            while(Atual != NULL){
                if(Atual->naipe == Naipe && Atual->numero == Numero){
                    printf("%d | %d\n", Atual->numero, Atual->naipe);
                    break;
                }
                Atual = Atual->prox;
            }
            if(Atual != NULL){
                Atual = Atual->prox;
            }

            while(Atual != NULL){
                if(Atual->naipe == Naipe && Atual->numero == Numero){
                    printf("%d | %d\n", Atual->numero, Atual->naipe);
                    break;
                }
                Atual = Atual->prox;
            }
        }
    }
    printf("\n");
}




//verifica a validade da mesa (1-valido/0-invalido/-1 erro)
int verifica_mesa(LISTA_MESA_PTR *lista_mesa){
    LISTA_MESA_PTR atual_mesa = *lista_mesa;
    //percorre os ponteiros da mesa até o ultimo
    while(atual_mesa != NULL){
        int qtd = 0;
        LISTA_CARTAS_PTR monte1 = atual_mesa->cartas;
        while(monte1 != NULL){
            qtd++;
            monte1 = monte1->prox;
        }
        //se tiver menos de 3 cartas é inválido
        if (qtd < 3) return 0;

        monte1 = atual_mesa->cartas;   //reseta para a primera posição do monte
        LISTA_CARTAS_PTR monte2 = atual_mesa->cartas;
        monte2 = monte2->prox;

        //identifica o tipo de monte
        //tipo 0: inválido
        //tipo 1: sequencia de naipe igual
        //tipo 2: grupo (cartas de numeros iguais de naipes diferentes)

        //verificação de uso do naipe, utilizado no case 2
        int usado[4]; //[1, 2, 3, 4] 1-true, 0-false

        //seta todos para false
        for (int i=0; i<4; i++){
            usado[i] = 0;
        }


        int tipo = 0;
        if (monte1->naipe == monte2->naipe && monte1->numero == ((monte2->numero) -1)) tipo = 1;
        if (monte1->naipe != monte2->naipe && monte1->numero == monte2->numero) tipo = 2;
        if (tipo == 0) return 0;
        //marca como usados os naipes
        usado[(monte1->naipe) -1] = 1;
        usado[(monte2->naipe) -1] = 1;


        //anda uma posição em cada
        monte1 = monte1->prox;
        monte2 = monte2->prox;


        switch (tipo){
        case 1:
            while (monte2 != NULL){
                if (monte1->naipe != monte2->naipe || monte1->numero != ((monte2->numero) -1)) return 0;
                monte1 = monte1->prox;
                monte2 = monte2->prox;
            }
        break;

        case 2:
            while (monte2 != NULL){
                if (usado[(monte2->naipe) -1] == 1) return 0;
                usado[(monte1->naipe) -1] = 1;
                usado[(monte2->naipe) -1] = 1;
                if (monte1->naipe == monte2->naipe || monte1->numero != monte2->numero) return 0;
                monte1 = monte1->prox;
                monte2 = monte2->prox;
            }
        break;

        default:
            return -1;
        }
        atual_mesa = atual_mesa->prox;
    }
    return 1;
}


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
