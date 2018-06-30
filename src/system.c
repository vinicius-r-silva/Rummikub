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

void Pixel_2_LinCol(int *lin, int *col, int x, int y){
    //if (x < INICIO_X_MESA || x > (FIM_X_MESA - TAM_X_CARTA) || y < INICIO_Y_MESA || y > (FIM_Y_MESA - TAM_Y_CARTA))
    //if (x < INICIO_X_MESA){
    //    return;
   // }
    y += TAM_Y_CARTA/2;
    x += TAM_X_CARTA/2;

    if(y > FIM_Y_MESA - TAM_Y_CARTA){
        *lin = 0;
        *col = 0;
        return;
    }
    
    int Espaco_X_Carta = TAM_X_CARTA + TAM_X_ESPACO;
    int Espaco_Y_Carta = TAM_Y_CARTA + TAM_Y_ESPACO;

    int Pos_X_Carta = x - INICIO_X_MESA;
    int Pos_Y_Carta = y - INICIO_Y_MESA;

    if(Pos_X_Carta < 0)
        Pos_X_Carta = 0;
    if(Pos_Y_Carta < 0)
        Pos_Y_Carta = 0;

    int coluna = Pos_X_Carta / Espaco_X_Carta;
    int linha  = Pos_Y_Carta / Espaco_Y_Carta;

    int dir = (Pos_X_Carta % Espaco_X_Carta > Espaco_X_Carta/2) ? 1 : 0;
    int inf = (Pos_Y_Carta % Espaco_Y_Carta > Espaco_Y_Carta/1.5) ? 1 : 0;

    if (dir)
        coluna++;
    if (inf)
        linha++;

    *lin = linha;
    *col = coluna;
}

void LinCol_2_Monte(LISTA_MESA_PTR *Monte, LISTA_MESA_PTR *Mesa, int *pos, int linha, int coluna){
    LISTA_MESA_PTR prev = NULL;
    LISTA_MESA_PTR Atual = *Mesa;
    g_print("Atual->y: %d, l: %d, c: %d\n", Atual->y, linha, coluna);
    if(Atual == NULL || Atual->y > linha || (Atual->y == linha && Atual->x > coluna)){
        g_print("Entrou\n");
        *Monte = *Mesa;
        *pos = -1;
        return;
    }

    while(Atual != NULL && Atual->y < linha){
        prev = Atual;
        Atual = Atual->prox;
    }
    while(Atual != NULL && Atual->y == linha && Atual->x < coluna){
        prev = Atual;
        Atual = Atual->prox;
    }

    if(Atual != NULL && (Atual->y == linha && Atual->x <= coluna && Atual->x+Atual->N_Cartas + 1 >= coluna)){
        *Monte = Atual;
        *pos = coluna - Atual->x;
        return;
    }
    else if(prev != NULL && (prev->y == linha && prev->x <= coluna && prev->x+prev->N_Cartas + 1 >= coluna)){
        *Monte = prev;
        *pos = coluna - prev->x;
        return;
    }

    *pos = -1;
    if (prev == NULL || (Atual != NULL && (Atual->y < linha || (Atual->y == linha && Atual->x < coluna))))
        *Monte = Atual;
    else    
        *Monte = prev;

    /*if (Atual != NULL && (Atual->y > linha || (Atual->y == linha && Atual->x != coluna)))
        *pos = -1;
    else if (prev != NULL && (prev->y > linha || prev->y != linha || ((prev->x + prev->N_Cartas+1) < coluna)))
        *pos = -1;
    else if (prev != NULL)
        *pos = coluna - prev->x;
    else
        *pos = 0;

    if(Atual != NULL && Atual->x == coluna)
        *Monte = Atual;
    else
        *Monte = prev;*/
}

LISTA_CARTAS_PTR Mao_Jogador_Atual(JOGADORES_PTR *Lista_Jogadores){
    JOGADORES_PTR atual = *Lista_Jogadores;
    while(!atual->Sua_Vez)
        atual = atual->prox;
    
    return atual->cartas;
}

void mao_2_monte(LISTA_CARTAS_PTR *mao, LISTA_MESA_PTR *mesa, int Naipe, int Numero, int Pos, bool Nova_Lista){
    LISTA_CARTAS_PTR prev_mao = NULL;
    LISTA_CARTAS_PTR atual_mao = *mao;
    while(atual_mao != NULL && (atual_mao->naipe != Naipe || atual_mao->numero != Numero)){
        prev_mao = atual_mao;
        atual_mao = atual_mao->prox;
    }
    if(atual_mao == NULL){
        g_print("Erro 10 - Carta Nao encontrada\n");
        return;
    }

    if(prev_mao == NULL)
        *mao = atual_mao->prox;
    else
        prev_mao->prox = atual_mao->prox;

    atual_mao->prox = NULL;
    LISTA_MESA_PTR Mesa_Atual;

    if(Nova_Lista){
        LISTA_MESA_PTR Nova_mesa = (LISTA_MESA_PTR)malloc(sizeof(LISTA_MESA));
        Nova_mesa->x = 0;
        Nova_mesa->y = 0;
        Nova_mesa->N_Cartas = 0;
        Nova_mesa->prox = NULL;
        Nova_mesa->cartas = NULL;
        
        if(*mesa == NULL)
            *mesa = Nova_mesa;
        else{
            Nova_mesa->prox = (*mesa)->prox;
            (*mesa)->prox = Nova_mesa;
        }

        Pos = 0;
        Mesa_Atual = Nova_mesa;
    }
    else
        Mesa_Atual = *mesa;

    int cont = 0;
    LISTA_CARTAS_PTR prev_destino = NULL;
    LISTA_CARTAS_PTR atual_destino = Mesa_Atual->cartas;

    while(atual_destino != NULL && cont < Pos){
        prev_destino = atual_destino;
        atual_destino = atual_destino->prox;
        cont++;
    }
    if(prev_destino == NULL)
        Mesa_Atual->cartas = atual_mao;
    else
        prev_destino->prox = atual_mao;

    Mesa_Atual->N_Cartas++;
    atual_mao->prox = atual_destino;
}

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
            return -2;
    }
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
    else
        Numero = -2;

    return (int)Numero;
}

void EventBox_2_Carta(GtkWidget *EventBox, int *Naipe, int *Numero){
    char *nome;// = (char*)malloc(10*sizeof(char)); memset(nome, 0, sizeof(char)*10);
    nome = (char*)gtk_widget_get_name(EventBox);

    *Numero = Hexa_2_int (nome[3]);
    *Naipe = Naipe_2_int (nome[4]);

    g_print("\n\nNome: %s, Na: %d (%c), Nu: %d (%c)\n\n", nome, *Naipe, nome[4], *Numero, nome[3]);
}