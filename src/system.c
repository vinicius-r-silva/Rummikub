#define _CRT_SECURE_NO_DEPRECATE
#include "libs/system.h"


void Organiza_Mesa(LISTA_MESA_PTR *Mesa){
    if(*Mesa == NULL)
        return;

    int linha = 0;
    int coluna = 0;

    LISTA_MESA_PTR mesa_atual = *Mesa;

    while(mesa_atual != NULL){
        if (coluna + mesa_atual->N_Cartas > N_MAX_COLUNAS && coluna != 0){
            coluna = 0;
            linha++;
        }

        mesa_atual->x = coluna;
        mesa_atual->y = linha;

        coluna += mesa_atual->N_Cartas + 1;
        mesa_atual = mesa_atual->prox;
    }
}


//verifica a validade da mesa (1-valido/0-invalido/-1 erro)
int verifica_mesa(LISTA_MESA_PTR *lista_mesa){
    LISTA_MESA_PTR atual_mesa = *lista_mesa;
    //percorre os ponteiros da mesa atÃ© o ultimo
    while(atual_mesa != NULL){
        int qtd_cartas = 0;
        LISTA_CARTAS_PTR monte1 = atual_mesa->cartas;
        while(monte1 != NULL){
            qtd_cartas++;
            monte1 = monte1->prox;
        }
        //se tiver menos de 3 cartas Ã© invÃ¡lido
        if (qtd_cartas < 3) return 0;

        monte1 = atual_mesa->cartas;   //reseta para a primera posiÃ§Ã£o do monte
        LISTA_CARTAS_PTR monte2 = atual_mesa->cartas;
        monte2 = monte2->prox;

        //identifica o tipo de monte
        //tipo 0: invÃ¡lido
        //tipo 1: sequencia de naipe igual
        //tipo 2: grupo (cartas de numeros iguais de naipes diferentes)
        //tipo 3: grupo com dois coringas e tres cartas, sem tipo nenhum, apenas e aceitavel

        //verificaÃ§Ã£o de uso do naipe, utilizado no case 2
        int usado[4]; //[1, 2, 3, 4] 1-true, 0-false

        //seta todos para false
        for (int i=0; i<4; i++){
            usado[i] = 0;
        }


        /**----------VERIFICACAO DE TIPO-----------------------**/
        /**
        se, e SOMENTE SE!! tiver algum joker fazer o seguinte:
        colocar as informações (numero) das struct num  vetor de structs
        ordenar e colocar o joker la no fim
        depois disso proseguir o restante
        **/

        int tipo = 0;
        //monte_joker: ajuda na contagem do joker
        LISTA_CARTAS_PTR monte_joker = monte1;

        int qtd_joker = 0;
        while(monte_joker != NULL){
            if (monte_joker->naipe == -1) qtd_joker++;
            monte_joker = monte_joker->prox;
        }
        if (qtd_joker == 2 && qtd_cartas == 3) tipo = 3;

//        while (monte1->naipe == -1 || monte2->naipe == -1){
//            monte1 = monte1->prox;
//            monte2 = monte2->prox;
//        }

        /**ORDENACAO E VERIFICACAO DE TIPO OCORRE NO VETOR, CASO HAJA JOKER**/
        LISTA_CARTAS_PTR monte_aux = monte1;
        if (qtd_joker > 0){
            LISTA_CARTAS vetor[qtd_cartas];
            for (int i=0; i<qtd_cartas; i++){
                (vetor[i]).numero = monte_aux->numero;
                (vetor[i]).naipe = monte_aux->naipe;
                monte_aux = monte_aux->prox;
            }
            //ordenacao no bubble sort
            int troca = 1;
            while (troca == 1){
                troca = 0;
                for (int j=0; j<qtd_cartas-1; j++){
                    if (vetor[j].numero > vetor[j+1].numero){
                        troca = 1;
                        LISTA_CARTAS aux = vetor[j];
                        vetor[j] = vetor[j+1];
                        vetor[j+1] = aux;
                    }
                }
            }







        }


        if (monte1->naipe == monte2->naipe && monte1->numero == ((monte2->numero) -1)) tipo = 1;
        if (monte1->naipe != monte2->naipe && monte1->numero == monte2->numero) tipo = 2;
        if (tipo == 0) return 0;


        /**------FIM DA VERIFICACAO DE TIPO----------------------------**/

        //Assim que verificado o tipo, reseta para as posicoes iniciais, monte 1 no primeiro e monte2 no segundo
        monte1 = atual_mesa->cartas;
        monte2 = monte1;
        monte2 = monte2->prox;


        //marca como usados os naipes
        usado[(monte1->naipe) -1] = 1;
        usado[(monte2->naipe) -1] = 1;


        //anda uma posiÃ§Ã£o em cada
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

void Baralho_2_mao(LISTA_CARTAS_PTR *baralho, LISTA_CARTAS_PTR *mao){
    LISTA_CARTAS_PTR Carta = *baralho;
    if (Carta == NULL)
        return;

    *baralho = Carta->prox;
    Carta->prox = *mao;
    *mao = Carta;
}


void mao_2_monte(LISTA_CARTAS_PTR *mao, LISTA_MESA_PTR *mesa, int Naipe, int Numero, int Pos, bool Nova_Lista){
    LISTA_CARTAS_PTR prev_mao = NULL;
    LISTA_CARTAS_PTR atual_mao = *mao;
    while(atual_mao != NULL && atual_mao->naipe != Naipe && atual_mao->numero != Numero){
        prev_mao = atual_mao;
        atual_mao = atual_mao->prox;
    }
    if(atual_mao == NULL){
        printf("Erro 10 - Carta Nao encontrada\n");
        return;
    }

    if(prev_mao == NULL)
        *mao = atual_mao->prox;
    else
        prev_mao->prox = atual_mao->prox;

    atual_mao->prox = NULL;
    LISTA_MESA_PTR Mesa_Atual;

    if(Nova_Lista){
        LISTA_MESA_PTR prev_mesa = NULL;
        LISTA_MESA_PTR atual_mesa = *mesa;

        LISTA_MESA_PTR Nova_mesa = (LISTA_MESA_PTR)malloc(sizeof(LISTA_MESA));
        Nova_mesa->x = 0;
        Nova_mesa->y = 0;
        Nova_mesa->N_Cartas = 0;
        Nova_mesa->prox = NULL;
        Nova_mesa->cartas = NULL;

        while(atual_mesa != NULL){
            prev_mesa = atual_mesa;
            atual_mesa = atual_mesa->prox;
        }
        if(prev_mesa == NULL)
            *mesa = Nova_mesa;
        else
            prev_mesa->prox = Nova_mesa;

        Pos = 0;
        Mesa_Atual = Nova_mesa;
    }
    else
        Mesa_Atual = *mesa;

    int cont = 1;
    LISTA_CARTAS_PTR prev_destino = NULL;
    LISTA_CARTAS_PTR atual_destino = Mesa_Atual->cartas;

    while(atual_destino != NULL && cont < Pos){
        prev_destino = atual_destino;
        atual_destino = atual_destino->prox;
    }
    if(prev_destino == NULL)
        Mesa_Atual->cartas = atual_mao;
    else
        prev_destino->prox = atual_mao;

    Mesa_Atual->N_Cartas++;
    atual_mao->prox = atual_destino;
}

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
        printf("Erro: Carta 1 não  encontrada\n");

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

int Hexa_2_int(char Numero){
    if (Numero >= '0' && Numero <= '9')
        Numero -= '0';
    else if (Numero >= 'A' && Numero <= 'Z')
        Numero -= 'A' - 10;
    else if (Numero >= 'a' && Numero <= 'z')
        Numero -= 'a' - 10;
    else if (Numero == '*')
        Numero = -1;

    return (int)Numero;
}

char int_2_hexa(int Numero){
    if (Numero >= 0 && Numero <= 9)
        Numero += '0';
    else
        Numero += 'A';

    return (char)Numero;
}

char Int_2_Naipe(int Naipe){
    switch(Naipe){
        case (1):
            return NAIPE_1;

        case (2):
            return NAIPE_2;

        case (3):
            return NAIPE_3;

        case (4):
            return NAIPE_4;

        case (-1):
            return CORINGA;

        default:
            return -1;
    }
}

int Naipe_2_int(char Naipe){
    switch(Naipe){
        case (NAIPE_1):
            return 1;

        case (NAIPE_2):
            return 2;

        case (NAIPE_3):
            return 3;

        case (NAIPE_4):
            return 4;

        case (CORINGA):
            return -1;

        default:
            return -1;
    }
}

void Inverte_Lista(LISTA_CARTAS_PTR *Lista){
    LISTA_CARTAS_PTR atual = *Lista;
    LISTA_CARTAS_PTR prev = NULL;
    LISTA_CARTAS_PTR pos = NULL;

    if(atual == NULL)
        return;

    prev = atual;
    atual = atual->prox;
    pos = atual->prox;
    prev->prox = NULL;
    while(pos != NULL){
        atual->prox = prev;
        prev = atual;
        atual = pos;
        pos = atual->prox;
    }
    if(atual != NULL){
        atual->prox = prev;
        *Lista = atual;
    }
    else
        *Lista = prev;
}

void Carrega_Baralho(LISTA_CARTAS_PTR *Baralho){
    Deleta_Lista(Baralho);

    FILE *Arquivo = fopen(LOCAL_FILE_BARALHO, "r");
    if(Arquivo == NULL){
        printf("Erro ao abrir o arquivo\n");
        return;
    }

    int Naipe;
    int Numero;
    char Leitura;
    while(!feof(Arquivo)){
        Leitura = getc(Arquivo);
        while(Leitura == '\n')
            Leitura = getc(Arquivo);

        Numero = Hexa_2_int(Leitura);

        Leitura = getc(Arquivo);
        while(Leitura == '\n')
            Leitura = getc(Arquivo);

        Naipe = Naipe_2_int(Leitura);

        if (Leitura == -1)
            break;

        Cria_Carta(Baralho, Naipe, Numero);
    }

    Inverte_Lista(Baralho);
}


//-----------------------------------------------------------------------------------------------//
void Imprime_Mesa_Organizado(LISTA_MESA_PTR *Mesa){

}

void Imprime_Mesa(LISTA_MESA_PTR *Mesa){
    LISTA_MESA_PTR Atual = *Mesa;
    int cont = 0;
    printf("--------------------------------------\n\n");
    while(Atual != NULL){
        printf("Mesa: %d.   X: %d, Y: %d\n", cont, Atual->x, Atual->y);
        Imprime(Atual->cartas);
        cont++;
        Atual = Atual->prox;
    }
}

void Imprime(LISTA_CARTAS_PTR Baralho){
    while(Baralho != NULL){
        printf("%d | %d\n", Baralho->numero, Baralho->naipe);
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


LISTA_MESA_PTR duplicar_mesa (LISTA_MESA_PTR *lista_mesa){

    LISTA_CARTAS_PTR nova_carta2 = NULL;
    LISTA_MESA_PTR atual_mesa = *lista_mesa;
    LISTA_MESA_PTR primeira_pos_mesa = NULL;
    int i = 1;

    //se estiver vazio retorna NULL
    if (*lista_mesa == NULL) return NULL;


    LISTA_MESA_PTR prev = NULL;
    while (atual_mesa != NULL){

        LISTA_MESA_PTR nova_mesa = (LISTA_MESA_PTR)malloc(sizeof(LISTA_MESA));
        nova_mesa->prox = NULL;
        if (prev != NULL){
            prev->prox = nova_mesa;
        }

        //se for a primeira vez, armazena o ponteiro de inicio

        if (i == 1){
            primeira_pos_mesa = nova_mesa;
        }

        nova_mesa->N_Cartas = atual_mesa->N_Cartas;


        nova_mesa->x = atual_mesa->x;

        nova_mesa->y = atual_mesa->y;

        LISTA_CARTAS_PTR atual_cartas = atual_mesa->cartas;

        LISTA_CARTAS_PTR nova_carta1 = (LISTA_CARTAS_PTR)malloc(sizeof(LISTA_CARTAS));

        nova_carta1->naipe = atual_cartas->naipe;
        nova_carta1->numero = atual_cartas->numero;

        nova_mesa->cartas = nova_carta1;
        atual_cartas = atual_cartas->prox;
        while (atual_cartas != NULL){
            printf("6\n");
            nova_carta2 = (LISTA_CARTAS_PTR)malloc(sizeof(LISTA_CARTAS));
            printf("a\n");
            nova_carta2->naipe = atual_cartas->naipe;
            printf("b\n");
            nova_carta2->numero = atual_cartas->numero;
            printf("c\n");
            nova_carta1->prox = nova_carta2;
            nova_carta1 = nova_carta2;
            atual_cartas = atual_cartas->prox;
        }
        nova_carta2->prox = NULL;
        i++;
        printf("7\n");
        atual_mesa = atual_mesa->prox;
        prev = nova_mesa;
    }
    printf("8\n");
    return primeira_pos_mesa;
}

LISTA_CARTAS_PTR duplicar_mao (LISTA_CARTAS_PTR *lista_cartas){
    LISTA_CARTAS_PTR atual_carta = *lista_cartas;
    LISTA_CARTAS_PTR nova_mao = (LISTA_CARTAS_PTR)malloc(sizeof(LISTA_CARTAS));
    LISTA_CARTAS_PTR primeira_posicao = nova_mao;
    nova_mao->naipe = atual_carta->naipe;
    nova_mao->numero = atual_carta->numero;
    nova_mao->prox = NULL;

    atual_carta = atual_carta->prox;
    while(atual_carta != NULL){
        LISTA_CARTAS_PTR nova_mao2 = (LISTA_CARTAS_PTR)malloc(sizeof(LISTA_CARTAS));
        nova_mao2->naipe = atual_carta->naipe;
        nova_mao2->numero = atual_carta->numero;
        nova_mao->prox = nova_mao2;
        nova_mao = nova_mao2;


        atual_carta = atual_carta->prox;
    }
    //nova_mao aponta para o ultimo, logo o prox do ultimo deve ser NULL
    nova_mao->prox = NULL;



    return primeira_posicao;
}

JOGADORES_PTR criar_jogadores (int qtd_jogadores){
    JOGADORES_PTR jog1 = NULL;
    JOGADORES_PTR primeira_posicao = NULL;
    for (int i=0; i<qtd_jogadores-1 && qtd_jogadores <= 6 && qtd_jogadores >=2; i++){ //nao pode ter mais de 6 jogadores
        if (i == 0){ //se for o primeiro loop
            jog1 = (JOGADORES_PTR)malloc(sizeof(JOGADORES));
            primeira_posicao = jog1;
            jog1->prox = NULL;
            jog1->id = i;
            jog1->cartas = NULL;
        }
        JOGADORES_PTR jog2 = (JOGADORES_PTR)malloc(sizeof(JOGADORES));
        jog2->prox = primeira_posicao; //o ultimo jogador aponta para o primeiro, criando um loop
        jog2->id = i+1;
        jog2->cartas = NULL;
        jog1->prox = jog2;
        jog1 = jog1->prox;
    }

    return primeira_posicao;
}


void excluir_jogadores (JOGADORES_PTR *lista_jogadores){
    JOGADORES_PTR jog1 = *lista_jogadores;
    JOGADORES_PTR jog2 = *lista_jogadores;
    jog2 = jog2->prox;
    int qtd_jogadores = 1;
    while(jog2->id != 0){
        qtd_jogadores++;
        jog2 = jog2->prox;
    }
    jog2 = jog2->prox;
    for(int i=0; i<qtd_jogadores-2; i++){
        free(jog1);
        jog1 = jog2;
        jog2 = jog2->prox;
    }
    free(jog1);
    free(jog2);
}

