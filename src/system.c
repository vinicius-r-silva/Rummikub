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


//--------------------------------------------------------------------------------------//
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