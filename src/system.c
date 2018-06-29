#include "libs/system.h"

void Cria_Carta(LISTA_CARTAS_PTR *Baralho, int Naipe, int Numero, GtkWidget *Painel, char Interacao){
    if (Naipe > 4 || Numero > 13)
        return;

    LISTA_CARTAS_PTR nova = (LISTA_CARTAS_PTR)malloc(sizeof(LISTA_CARTAS));
    nova->naipe = Naipe;
    nova->numero = Numero;
    nova->prox = *Baralho;
    nova->img = Insere_Carta_Interface(Naipe, Numero, Painel, Interacao);
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
    GtkWidget *Img1 = NULL;
    GtkWidget *Img2 = NULL;

    if(Carta1 != NULL){
        Carta1->numero = Num_2;
        Carta1->naipe = Naipe_2;
        Img1 = Carta1->img;
    } else
        printf("Erro: Carta 1 não  encontrada\n");

    if(Carta2 != NULL){
        Img2 = Carta2->img;
        Carta2->img = Img1;
        Carta2->numero = Num_1;
        Carta2->naipe = Naipe_1;
    }else
        printf("Erro: Carta 2 não encontrada\n");

    if(Carta1 != NULL)
        Carta1->img = Img2;
}

void Init_Baralho(LISTA_CARTAS_PTR *Baralho, GtkWidget *Painel){
    LISTA_CARTAS_PTR Baralho1 = NULL;
    LISTA_CARTAS_PTR Baralho2 = NULL;

    Cria_Baralho(&Baralho1, Painel, '1');
    Cria_Baralho(&Baralho2, Painel, '2');

    LISTA_CARTAS_PTR atual = Baralho1;
    while(atual->prox != NULL)
        atual = atual->prox;

    atual->prox = Baralho2;
    *Baralho = Baralho1;
}

void Cria_Baralho(LISTA_CARTAS_PTR *Baralho, GtkWidget *Painel, int Interacao){
    srand(time(NULL));
    int Numero, Naipe;
    for(Naipe = 1; Naipe < 5; Naipe++){
        for(Numero = 1; Numero < 14; Numero++){
            Cria_Carta(Baralho, Naipe, Numero, Painel, Interacao);
        }
    }
    Cria_Carta(Baralho, -1, -1, Painel, Interacao);

    for(Naipe = 1; Naipe < 5; Naipe++){
        for(Numero = 1; Numero < 14; Numero++){
            TrocaCarta(Baralho, Naipe, rand() % 4 + 1 ,Numero, rand() % 13 + 1);
        }
    }
    //TrocaCarta(Baralho, -1, rand() % 4 + 1 , -1, rand() % 13 + 1);
}


void Baralho_2_mao(LISTA_CARTAS_PTR *baralho, LISTA_CARTAS_PTR *mao){
    LISTA_CARTAS_PTR Carta = *baralho;
    if (Carta == NULL)
        return;
    
    *baralho = Carta->prox;
    Carta->prox = *mao;
    *mao = Carta;
}

void Grid_2_Pixel(int linha, int coluna, int *x, int *y, int Inicio_x, int Inicio_y){
    *x = Inicio_x;
    *y = Inicio_y;

    *x += (TAM_X_CARTA + TAM_X_ESPACO) * coluna;
    *y += (TAM_Y_CARTA + TAM_Y_ESPACO) * linha;
}

int Cartas_Mao(int *x, int *y, GtkWidget **Img, int pos, LISTA_CARTAS_PTR atual){
    int cont = 0;
    while(atual != NULL && cont < pos){
        atual = atual->prox;
        cont++;
    }

    if(atual == NULL)
        return 0;

    *Img = atual->img;
    int calc_x = INICIO_X_MAO;
    int calc_y = INICIO_Y_MAO;

    if(cont == N_MAX_COLUNAS){  
        pos -= N_MAX_COLUNAS;
        calc_y+= TAM_Y_CARTA + TAM_Y_ESPACO;
    }
    calc_x += (TAM_X_CARTA + TAM_X_ESPACO)*pos;

    *x = calc_x;
    *y = calc_y;

    return 1;
}

char int_2_hexa(int Numero){
    if (Numero == -1)
        Numero = '*';
    else if (Numero >= 0 && Numero <= 9)
        Numero += '0';
    else 
        Numero += 'A' - 10;

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

void excluir_jogadores (JOGADORES_PTR *Lista_Jogadores){
    JOGADORES_PTR atual = *Lista_Jogadores;
    JOGADORES_PTR prev = NULL;
    if(atual == NULL)
        return;

    prev = atual;
    atual = atual->prox;
    prev->prox = NULL;

    LISTA_CARTAS_PTR Prev_Mao = NULL;
    LISTA_CARTAS_PTR Atual_Mao = NULL;

    while(atual != NULL){
        prev = atual;
        atual = atual->prox;

        Prev_Mao = NULL;
        Atual_Mao = prev->cartas;
        while(Atual_Mao != NULL){
            Prev_Mao = Atual_Mao;
            Atual_Mao = Atual_Mao->prox;
            free(Prev_Mao);
        }
        free(prev);
    }
    *Lista_Jogadores = NULL;
}

void criar_jogadores (JOGADORES_PTR *Lista_Jogadores, int Qtd){
    excluir_jogadores(Lista_Jogadores);
    if(Qtd == 0)
        return;

    int i = 0;
    JOGADORES_PTR prev = NULL;
    JOGADORES_PTR atual = (JOGADORES_PTR)malloc(sizeof(JOGADORES));
    *Lista_Jogadores = atual;

    atual->Id = i;
    atual->Sua_Vez = 1;
    atual->prox = NULL;
    atual->cartas = NULL;
    atual->Jogada_Inicial = 1;
    Insere_Img_Jogador(atual);

    for (i = 1; i < Qtd && i < 5; i++){ //nao pode ter mais de 5 jogadores
        prev = atual;

        atual = (JOGADORES_PTR)malloc(sizeof(JOGADORES));
        atual->Id = i;
        atual->Sua_Vez = 0;
        atual->cartas = NULL;
        atual->Jogada_Inicial = 1;
        Insere_Img_Jogador(atual);

        prev->prox = atual;
    }
    atual->prox = *Lista_Jogadores;
    return;
}
