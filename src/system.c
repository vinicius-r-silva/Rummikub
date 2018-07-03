#include "libs/system.h"

void Cria_Carta(LISTA_CARTAS_PTR *Baralho, int Naipe, int Numero, GtkWidget *Painel, char Interacao){
    LISTA_CARTAS_PTR nova = (LISTA_CARTAS_PTR)malloc(sizeof(LISTA_CARTAS));
    nova->naipe = Naipe;
    nova->numero = Numero;
    nova->prox = *Baralho;
    nova->interacao = Interacao;
    nova->img = Insere_Carta_Interface(Naipe, Numero, Painel, Interacao);
    *Baralho = nova;
}

LISTA_CARTAS_PTR Busca_Carta(LISTA_CARTAS_PTR *Baralho, int Naipe, int Numero, char interacao){
    LISTA_CARTAS_PTR atual = *Baralho;
    while(atual != NULL){
        if(atual->naipe == Naipe && atual->numero == Numero && atual->interacao == interacao)
            return atual;
        atual = atual->prox;
    }
    return NULL;
}

LISTA_CARTAS_PTR Busca_Carta_Mesa(LISTA_MESA_PTR *Mesas, LISTA_MESA_PTR *Monte, int Naipe, int Numero, char interacao){
    LISTA_MESA_PTR atual = *Mesas;
    LISTA_CARTAS_PTR carta = NULL;
    while(atual != NULL){
        carta = Busca_Carta(&(atual->cartas), Naipe, Numero, interacao);
        if (carta != NULL)
            break;

        atual = atual->prox;
    }
    *Monte = atual;
    return carta;
}

void TrocaCarta(LISTA_CARTAS_PTR *Baralho, int Naipe_1, int Naipe_2, int Num_1, int Num_2, int inte1, int inte2){
    LISTA_CARTAS_PTR Carta1 = Busca_Carta(Baralho, Naipe_1, Num_1, inte1);
    LISTA_CARTAS_PTR Carta2 = Busca_Carta(Baralho, Naipe_2, Num_2, inte2);
    GtkWidget *Img1 = NULL;
    GtkWidget *Img2 = NULL;

    if(Carta1 != NULL){
        Carta1->numero = Num_2;
        Carta1->naipe = Naipe_2;
        Carta1->interacao = inte2;
        Img1 = Carta1->img;
    } else
        printf("Erro: Carta 1 não  encontrada. Na: %d, Nu: %d, inte: %d\n", Naipe_1, Num_1, inte1);

    if(Carta2 != NULL){
        Img2 = Carta2->img;
        Carta2->img = Img1;
        Carta2->numero = Num_1;
        Carta2->naipe = Naipe_1;
        Carta2->interacao = inte1;
    }else
        printf("Erro: Carta 2 não encontrada. Na: %d, Nu: %d, inte: %d\n", Naipe_2, Num_2, inte2);

    if(Carta1 != NULL)
        Carta1->img = Img2;
}

void Init_Baralho(LISTA_CARTAS_PTR *Baralho, GtkWidget *Painel){
    LISTA_CARTAS_PTR Baralho1 = NULL;
    LISTA_CARTAS_PTR Baralho2 = NULL;

    Cria_Baralho(&Baralho1, Painel, 1);
    Cria_Baralho(&Baralho2, Painel, 2);

    LISTA_CARTAS_PTR atual = Baralho1;
    while(atual->prox != NULL)
        atual = atual->prox;

    atual->prox = Baralho2;
    *Baralho = Baralho1;

    g_print("Imprime baralho:\n");
    Imprime_Baralho(*Baralho);
    g_print("fim imprime baralho\n\n");

    int i, Naipe, Numero, interacao;
    for (i = 0; i < 10; i++){
        for(Naipe = 1; Naipe < 5; Naipe++){
            for(Numero = 1; Numero < 14; Numero++){
                interacao = rand() % 2;
                TrocaCarta(Baralho, Naipe, rand() % 4 + 1 ,Numero, rand() % 13 + 1, interacao+1, !interacao+1);
            }
        }
        //TrocaCarta(Baralho, JOKER, rand() % 4 + 1 , JOKER, rand() % 13 + 1, interacao+1, !interacao+1);
    }
    g_print("Fim Init Trabalho\n\n");
}


void Imprime_Baralho(LISTA_CARTAS_PTR Lista_Carta){
    while(Lista_Carta != NULL){
        g_print("%2d | %2d  (%c, %c) inte: %d\n", Lista_Carta->numero, Lista_Carta->naipe, int_2_hexa(Lista_Carta->numero), Int_2_Naipe(Lista_Carta->naipe),Lista_Carta->interacao);
        Lista_Carta = Lista_Carta->prox;
    }
    g_print("\n\n\n");
}

void Cria_Baralho(LISTA_CARTAS_PTR *Baralho, GtkWidget *Painel, char interacao){
    srand(time(NULL));
    int Numero, Naipe;
    for(Naipe = 1; Naipe < 5; Naipe++){
        for(Numero = 1; Numero < 14; Numero++){
            Cria_Carta(Baralho, Naipe, Numero, Painel, interacao);
        }
    }
    Cria_Carta(Baralho, JOKER, JOKER, Painel, interacao);
    Imprime_Baralho(*Baralho);
    int i;
    for (i = 0; i < 10; i++){
        for(Naipe = 1; Naipe < 5; Naipe++){
            for(Numero = 1; Numero < 14; Numero++){
                TrocaCarta(Baralho, Naipe, rand() % 4 + 1 ,Numero, rand() % 13 + 1, interacao, interacao);
            }
        }
        TrocaCarta(Baralho, JOKER, rand() % 4 + 1 , JOKER, rand() % 13 + 1, interacao, interacao);
    }
}


void Baralho_2_mao(LISTA_CARTAS_PTR *baralho, LISTA_CARTAS_PTR *mao){
    LISTA_CARTAS_PTR Carta = *baralho;
    g_print("2\n");
    if (Carta == NULL)
        return;

    if(Carta->prox != NULL)
        g_print("1 Na: %d, Nu: %d, P_Na: %d, P_Nu: %d\n", Carta->naipe, Carta->numero, Carta->prox->naipe, Carta->prox->numero);
    *baralho = (*baralho)->prox;

    if(Carta->prox != NULL)
        g_print("3 Na: %d, Nu: %d, P_Na: %d, P_Nu: %d\n", Carta->naipe, Carta->numero, Carta->prox->naipe, Carta->prox->numero);
    Carta->prox = *mao;

    if(Carta->prox != NULL)
        g_print("4 Na: %d, Nu: %d, P_Na: %d, P_Nu: %d\n", Carta->naipe, Carta->numero, Carta->prox->naipe, Carta->prox->numero);
    *mao = Carta;

    if(Carta->prox != NULL)
        g_print("5 Na: %d, Nu: %d, P_Na: %d, P_Nu: %d\n", Carta->naipe, Carta->numero, Carta->prox->naipe, Carta->prox->numero);
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
    if (Numero == JOKER)
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

        case (JOKER):
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
    atual->Ja_Comprou = 0;
    atual->Jogada_Inicial = 1;
    Insere_Img_Jogador(atual);

    for (i = 1; i < Qtd && i < 5; i++){ //nao pode ter mais de 5 jogadores
        prev = atual;

        atual = (JOGADORES_PTR)malloc(sizeof(JOGADORES));
        atual->Id = i;
        atual->Sua_Vez = 0;
        atual->cartas = NULL;
        atual->Ja_Comprou = 0;
        atual->Jogada_Inicial = 1;
        Insere_Img_Jogador(atual);

        prev->prox = atual;
    }
    atual->prox = *Lista_Jogadores;
    
    return;
}

void Pixel_2_LinCol(int *lin, int *col, int x, int y, int Inicio_x, int Inicio_y, int Tam_x, int Tam_y){
    g_print("\t Pixel_2_LinCol:\n");
    y += TAM_Y_CARTA/2;
    x += TAM_X_CARTA/2;
    
    Inicio_y += TAM_Y_CARTA/2;
    Inicio_x += TAM_X_CARTA/2;

    int Pos_X_Carta = x - Inicio_x;
    int Pos_Y_Carta = y - Inicio_y;

    if(Pos_X_Carta < 0)
        Pos_X_Carta = 0;
    if(Pos_Y_Carta < 0)
        Pos_Y_Carta = 0;

    int coluna = Pos_X_Carta / Tam_x;
    int linha  = Pos_Y_Carta / Tam_y;

    g_print("\t lin1: %d, col1: %d, Pos X: %d, Pos Y: %d\n", linha, coluna, Pos_X_Carta, Pos_Y_Carta);
 

    int dir = ((Pos_X_Carta % Tam_x) > (Tam_x/2.5)) ? 1 : 0;
    int inf = ((Pos_Y_Carta % Tam_y) > (Tam_y/1.5)) ? 1 : 0;
    g_print("\t lin2: %d, col2: %d, Pos_P_Tam_X: %d, Pos_P_Tam_Y: %d, Tam_x: %d, Tam_y: %d\n", linha, coluna, (Pos_X_Carta % Tam_x), (Pos_Y_Carta % Tam_y), Tam_x, Tam_y);

    if (dir)
        coluna++;
    if (inf)
        linha++;

    if(coluna > N_MAX_COLUNAS)
        coluna = N_MAX_COLUNAS;

    g_print("\t lin3: %d, col3: %d:\n", linha, coluna);

    *lin = linha;
    *col = coluna;
}

void LinCol_2_Monte(LISTA_MESA_PTR *Monte, LISTA_MESA_PTR *Mesa, int *pos, int linha, int coluna){
    g_print("\t\t Entrou LinCol_2_Monte\n");
    LISTA_MESA_PTR prev = NULL;
    LISTA_MESA_PTR Atual = *Mesa;
    
    if(Atual == NULL || Atual->y > linha || (Atual->y == linha && Atual->x > coluna)){
        *Monte = *Mesa;
        *pos = -1;
        g_print("\t\t ");
        if (*Monte != NULL)
            g_print("*Monte: x: %d, y: %d  | ", (*Monte)->x, (*Monte)->y);
        g_print("pos: %d\n", *pos);
        g_print("\t\t Saida 1 LinCol_2_Monte\n\n");
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
        g_print("\t\t ");
        if (Atual != NULL)
            g_print("Atual: x: %d, y: %d  | ", Atual->x, Atual->y);
        g_print("pos: %d\n", *pos);
        g_print("\t\t Saida 2 LinCol_2_Monte\n\n");
        return;
    }
    else if(prev != NULL && (prev->y == linha && prev->x <= coluna && prev->x+prev->N_Cartas + 1 >= coluna)){
        *Monte = prev;
        // if (prev != NULL && prev->x+prev->N_Cartas == coluna)
        //     *pos = -1;
        // else
            *pos = coluna - prev->x;

        g_print("\t\t ");
        if ((*Monte) != NULL)
            g_print("Monte: x: %d, y: %d  | ", (*Monte)->x, (*Monte)->y);
        g_print("pos: %d\n", *pos);
        g_print("\t\t Saida 3 LinCol_2_Monte\n\n");

        return;
    }

    *pos = -1;
    if (prev == NULL || (Atual != NULL && (Atual->y < linha || (Atual->y == linha && Atual->x < coluna))))
        *Monte = Atual;
    else    
        *Monte = prev;
        
    g_print("\t\t ");
    if ((*Monte) != NULL)
        g_print("Monte: x: %d, y: %d  | ", (*Monte)->x, (*Monte)->y);
    g_print("pos: %d\n", *pos);
    g_print("\t\t Saida 4 LinCol_2_Monte\n\n");
}


JOGADORES_PTR Jogador_Atual(JOGADORES_PTR Lista_Jogadores){
    if(Lista_Jogadores == NULL)
        return NULL;
        
    while(!Lista_Jogadores->Sua_Vez)
        Lista_Jogadores = Lista_Jogadores->prox;
    
    return Lista_Jogadores;
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

void Retira_montes_Vazios(LISTA_MESA_PTR *Mesa){
    if (*Mesa == NULL)
        return;

    if((*Mesa)->prox == NULL && (*Mesa)->cartas == NULL){
        free(*Mesa);
        *Mesa = NULL;
        return;
    }

    LISTA_MESA_PTR temp = NULL;
    LISTA_MESA_PTR prev = NULL;
    LISTA_MESA_PTR atual = *Mesa;

    while(atual != NULL){
        if(atual->cartas == NULL){
            if (prev == NULL)
                *Mesa = atual->prox;
            else   
                prev->prox = atual->prox;
            
            temp = atual;
            atual = atual->prox;
            free(temp);
        }
        else {
            prev = atual;
            atual = atual->prox;
        }
    }
}

void Organiza_Mesa(LISTA_MESA_PTR *Mesa){
    if(*Mesa == NULL)
        return;

    Retira_montes_Vazios(Mesa);

    int linha = 0;
    int coluna = 0;

    LISTA_CARTAS_PTR Cartas;
    LISTA_MESA_PTR mesa_atual = *Mesa;
    int conta_cartas = 0;

    while(mesa_atual != NULL){
        conta_cartas = 0;
        Cartas = mesa_atual->cartas;
        while(Cartas != NULL){
            conta_cartas++;
            Cartas = Cartas->prox;
        }
        mesa_atual->N_Cartas = conta_cartas;

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
            return JOKER;

        default:
            return -2;
    }
}

int Hexa_2_int(char Hexa){
    int Numero = -1;

    if (Hexa >= '0' && Hexa <= '9')
        Numero = Hexa - '0';
    else if (Hexa >= 'A' && Hexa <= 'Z')
        Numero = Hexa - 'A' + 10;
    else if (Hexa >= 'a' && Hexa <= 'z')
        Numero = Hexa - 'a' + 10;
    else if (Hexa == '*')
        Numero = JOKER;
    else
        Numero = -2;

    return (int)Numero;
}

void EventBox_2_Carta(GtkWidget *EventBox, int *Naipe, int *Numero, char *interacao){
    char *nome;
    nome = (char*)gtk_widget_get_name(EventBox);

    *Numero = Hexa_2_int (nome[3]);
    *Naipe = Naipe_2_int (nome[4]);
    *interacao = Hexa_2_int (nome[0]);
    g_print("\t\t EventBox_2_Carta: %s\n", nome);
    g_print("\t\t Na: %d, nu: %d, inte: %d\n\n", *Naipe, *Numero, *interacao);
}

void cria_mao_jogadores(JOGADORES_PTR *Lista_Jogadores, LISTA_CARTAS_PTR *Baralho, LISTA_CARTAS_PTR *Backup_mao){
  JOGADORES_PTR atual = *Lista_Jogadores;
  int cont;
  int prev_id = 0;

  for(cont = 0; cont < 14; cont++){
    Baralho_2_mao(Baralho, &(atual->cartas));
  }
  atual = atual->prox;

  while(prev_id < atual->Id){
    for(cont = 0; cont < 14; cont++){
      Baralho_2_mao(Baralho, &(atual->cartas));
    }
    prev_id = atual->Id;
    atual = atual->prox;
  }
  //Inverte_Lista(&(atual->cartas));

  *Backup_mao = duplica_Cartas(&(atual->cartas));
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

void Deleta_Mesa(LISTA_MESA_PTR *Mesa){
    LISTA_MESA_PTR atual = *Mesa;
    LISTA_MESA_PTR prev = NULL;

    while(atual != NULL){
        prev = atual;
        atual = atual->prox;
        Deleta_Lista(&(prev->cartas));
        free(prev);
    }
    *Mesa = NULL;
}

//1: SIM; 0: NAO; -1: ERRO
int fim_do_jogo(LISTA_CARTAS_PTR *baralho_compras, JOGADORES_PTR *lista_jogadores){
    //ver se algum deles esta sem carta
    JOGADORES_PTR jog1 = *lista_jogadores;

    //conta os jogadores
    int qtd_jogadores = 1;
    jog1 = jog1->prox;
    while(jog1->Id != 0){
        qtd_jogadores++;
        jog1 = jog1->prox;
    }
    //reseta a posicao
    jog1 = *lista_jogadores;
    for (int i=0; i<qtd_jogadores; i++){
        if (jog1->cartas == NULL) return 1;
        jog1 = jog1->prox;
    }

    //qtd cartas baralho
    LISTA_CARTAS_PTR baralho = *baralho_compras;
    int qtd_baralho = 0;
    while(baralho != NULL){
        qtd_baralho++;
        baralho = baralho->prox;
    }
    if (qtd_baralho == 0) {
        return 1;
    } else {
        return 0;
    }
}

//retorna o id, se for -1 se o jogo ainda nao acabou; retorna -2 se der empate
int vencedor(JOGADORES_PTR *lista_jogadores, LISTA_CARTAS_PTR *lista_baralho){
    JOGADORES_PTR jog1 = *lista_jogadores;
    jog1 = jog1->prox;
    //conta os jogadores
    int qtd_jogadores = 1;
    while(jog1->Id != 0){
        qtd_jogadores++;
        jog1 = jog1->prox;
    }
    //reseta a posicao
    jog1 = *lista_jogadores;


    int pontuacoes[qtd_jogadores];
    for (int i=0; i<qtd_jogadores; i++){
        pontuacoes[i] = 0;
    }

    //verifica se algum deles esta sem cartas, alem disso soma as pontuacoes
    LISTA_CARTAS_PTR cartas = NULL;
    for (int i=0; i<qtd_jogadores; i++){
        if (jog1->cartas == NULL) return jog1->Id;
        cartas = jog1->cartas;
        while(cartas != NULL){
            if (cartas->numero == INT_MAX){ //o coringa vale 20 pontos, segundo as regras
                pontuacoes[i] += 20;
            } else {
                pontuacoes[i] += cartas->numero;
            }
            cartas = cartas->prox;
        }
        jog1 = jog1->prox;
    }
    LISTA_CARTAS_PTR baralho = *lista_baralho;
    int id_do_menor = -1;
    if (baralho == NULL){  //se tiver acabado as cartas de comprar
        //acha a menor soma de pontos e retorna como vencedor este jogador
        id_do_menor = -1;
        int menor_pontuacao = INT_MAX;
        for (int i=0; i<qtd_jogadores; i++){
            if (pontuacoes[i] == menor_pontuacao){ //se houver empate
                return -2;
            }
            if (pontuacoes[i] < menor_pontuacao){
                id_do_menor = i;
                menor_pontuacao = pontuacoes[i];
            }
        }
    } else {
        return -1; //se nao retornou o jogador sem cartas e ainda tem cartas para comprar o jogo ainda nao acabou
    }

    return id_do_menor;
}

//pega dois ponteiros de mesas, a antes da modificacao e a apos, ja supoe que sao validas e subtrai os pontos, se for maior que 30 ok
//0: invalido; 1:valido
int valida_jogada (JOGADORES_PTR Jogador, LISTA_CARTAS_PTR *Backup_Mao, LISTA_MESA_PTR *mesa_backup, LISTA_MESA_PTR *mesa_nova){
    LISTA_CARTAS_PTR check = *Backup_Mao;
    LISTA_CARTAS_PTR compara = Jogador->cartas;
    while(check != NULL){
        if(Busca_Carta(&compara, check->naipe, check->numero, check->interacao) == NULL)
             break;
        
        check = check->prox;
    }
    if(check == NULL && Jogador->Ja_Comprou != 1){
        g_print("Jogada invalida pelo backup\n");
         return 0;
    }

    if (Jogador->Jogada_Inicial == 0 || (check == NULL && Jogador->Ja_Comprou == 1))
        return 1;

    g_print("verificando priemira jogada\n");

    int pont_mesa1 = 0;
    int pont_mesa2 = 0;
    //soma os pontos da mesa
    LISTA_MESA_PTR m_backup = *mesa_backup;
    LISTA_MESA_PTR m_nova = *mesa_nova;
    LISTA_CARTAS_PTR atual_cartas = NULL;

    //mesa 1
    while (m_backup != NULL){
        atual_cartas = m_backup->cartas;
        while(atual_cartas != NULL){
            if (atual_cartas->numero == JOKER)
                pont_mesa1 += 20;
            else 
                pont_mesa1 += atual_cartas->numero;
            
            atual_cartas = atual_cartas->prox;
        }
        m_backup = m_backup->prox;
    }

    //mesa 2
    while (m_nova != NULL){
        atual_cartas = m_nova->cartas;
        while(atual_cartas != NULL){
            if (atual_cartas->numero == JOKER)
                pont_mesa2 += 20;
            else 
                pont_mesa2 += atual_cartas->numero;
            
            atual_cartas = atual_cartas->prox;
        }
        m_nova = m_nova->prox;
    }

    //subtrai e ve a validade
    int diferenca = pont_mesa2 - pont_mesa1;
    if (diferenca >= 30){
        return 1;
    } else {
        return 0;
    }
}

LISTA_CARTAS_PTR duplica_Cartas(LISTA_CARTAS_PTR *Origem){
    LISTA_CARTAS_PTR atual = *Origem;
    LISTA_CARTAS_PTR destino = NULL;

    LISTA_CARTAS_PTR temp = NULL;
    LISTA_CARTAS_PTR prev_temp = NULL;

    if(atual == NULL)
        return NULL;

    temp = (LISTA_CARTAS_PTR)malloc(sizeof(LISTA_CARTAS));
    temp->naipe = atual->naipe;
    temp->numero = atual->numero;
    temp->img = atual->img;
    temp->prox = NULL;
    temp->interacao = atual->interacao;
    destino = temp;  

    atual = atual->prox;
    while(atual != NULL){
        prev_temp = temp;
        temp = (LISTA_CARTAS_PTR)malloc(sizeof(LISTA_CARTAS));
        temp->prox = NULL;
        temp->img  = atual->img;
        temp->naipe = atual->naipe;
        temp->numero = atual->numero;
        temp->interacao = atual->interacao;

        prev_temp->prox = temp;
        atual = atual->prox;
    }

    return destino;
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

        nova_carta1->img = atual_cartas->img;
        nova_carta1->naipe = atual_cartas->naipe;
        nova_carta1->numero = atual_cartas->numero;
        nova_carta1->interacao = atual_cartas->interacao;

        nova_mesa->cartas = nova_carta1;
        atual_cartas = atual_cartas->prox;
        while (atual_cartas != NULL){
            nova_carta2 = (LISTA_CARTAS_PTR)malloc(sizeof(LISTA_CARTAS));
            nova_carta2->naipe = atual_cartas->naipe;
            nova_carta2->numero = atual_cartas->numero;
            nova_carta2->interacao = atual_cartas->interacao;
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
        //se tiver menos de 3 cartas sera invalido
        if (qtd_cartas < 3) return 0;

        monte1 = atual_mesa->cartas;   //reseta para a primera posicao do monte
        LISTA_CARTAS_PTR monte2 = atual_mesa->cartas;
        monte2 = monte2->prox;

        //identifica o tipo de monte
        //tipo 0: invalido
        //tipo 1: sequencia de naipe igual
        //tipo 2: grupo (cartas de numeros iguais de naipes diferentes)
        //tipo 3: grupo com dois coringas e tres cartas, sem tipo nenhum, apenas e aceitavel


        /**----------VERIFICACAO DE TIPO-----------------------**/
        /**
        Se, e SOMENTE SE houver algum joker fazer o seguinte:
        Colocar as informações das structs num  vetor de structs
        Ordenar e colocar o joker la no fim
        Proseguir para a verificacao de tipo
        **/

        int tipo = 0;
        //monte_joker: ajuda na contagem do joker
        LISTA_CARTAS_PTR monte_joker = monte1;

        int qtd_joker = 0;
        while(monte_joker != NULL){
            if (monte_joker->numero == JOKER) qtd_joker++;
            monte_joker = monte_joker->prox;
        }
        if (qtd_joker == 2 && qtd_cartas == 3) {
            tipo = 3;
            break; //como e valido, passa para a proxima posicao da mesa
        }

        /**ORDENACAO E VERIFICACAO DE TIPO OCORRE NO VETOR, CASO HAJA JOKER**/
        LISTA_CARTAS_PTR monte_aux = monte1;
        LISTA_CARTAS vetor[qtd_cartas];
        //passar para o vetor
        for (int i=0; i<qtd_cartas; i++){
                (vetor[i]).numero = monte_aux->numero;
                (vetor[i]).naipe = monte_aux->naipe;
                monte_aux = monte_aux->prox;
            }
        if (qtd_joker > 0 && tipo != 3){

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


        if (vetor[0].numero != vetor[1].numero){
            tipo = 1;
        } else {
            tipo = 2;
        }
        /**------FIM DA VERIFICACAO DE TIPO----------------------------**/

        //Assim que verificado o tipo, reseta para as posicoes iniciais, monte 1 no primeiro e monte2 no segundo
        monte1 = atual_mesa->cartas;
        monte2 = monte1;
        monte2 = monte2->prox;

        //--------------PASSAR AS INFORMACOES DAS STRUCTS PARA UM VETOR-------------//
        LISTA_CARTAS monte_clone[qtd_cartas]; //clone do monte de cartas
        monte_aux = monte1;
        for (int i=0; i<qtd_cartas; i++){
            monte_clone[i].numero = monte_aux->numero;
            monte_clone[i].naipe = monte_aux->naipe;
            monte_aux = monte_aux->prox;
        }
       //----------------------------------------------------------------------------//


        /*//verificao de uso do naipe, utilizado no case 2
        int usado[5]; //[0, 1, 2, 3, 4] 1-true, 0-false
        //nao usa a posicao 0

        //setando todos para false
        for (int i=0; i<5; i++){
            usado[i] = 0;
        }

        for (int i=0; i< qtd_cartas; i++){
            if (monte_clone[i].naipe != JOKER) 
                usado[monte_clone[i].naipe] = 1;
        }*/
        int jokers_restante = -1;
        switch (tipo){
        case 1:
            //substituicao dos jokers
            jokers_restante = qtd_joker;
            for (int i=0; i<qtd_cartas-1; i++){
                if (i == 0 && monte_clone[i].numero == JOKER){ //se o primeiro for joker
                    jokers_restante--;
                    if (monte_clone[1].numero == 1) return 0; //se o 1 for joker e o segundo for 1 nao vale
                    if (monte_clone[i+1].numero == JOKER){ // se o segundo tambem for joker
                        jokers_restante--;
                        monte_clone[i].numero = monte_clone[i+2].numero - 2;
                        monte_clone[i].naipe = monte_clone[i+2].naipe;
                        monte_clone[i+1].numero = monte_clone[i+2].numero - 1;
                        monte_clone[i+1].naipe = monte_clone[i+2].naipe;
                    } else { //se o segundo nao for joker e o primeiro sim
                        monte_clone[i].numero = monte_clone[i+1].numero - 1;
                        monte_clone[i].naipe = monte_clone[i+1].naipe;
                    }
                }

                if (monte_clone[i].numero == JOKER && jokers_restante > 0){
                    jokers_restante--;
                    monte_clone[i].numero = monte_clone[i-1].numero + 1;
                    monte_clone[i].naipe = monte_clone[i-1].naipe;
                }
            }
            //verificar a ultima posicao, que nao foi vista no for
            if (monte_clone[qtd_cartas-1].numero == JOKER && jokers_restante > 0){
                jokers_restante--;
                monte_clone[qtd_cartas-1].numero = monte_clone[qtd_cartas-2].numero + 1; //substitui o joker pelo valor correto
                monte_clone[qtd_cartas-1].naipe = monte_clone[qtd_cartas-2].naipe;
            }
            //verificacao com os jokers substituidos
            for (int i=0; i<qtd_cartas-1; i++){
                if ((monte_clone[i].numero != (monte_clone[i+1].numero - 1)) || (monte_clone[i].naipe != monte_clone[i+1].naipe)) return 0;
            }


        break;

        case 2:
            if (qtd_cartas < 3 || qtd_cartas > 4) return 0;
            //substituicao dos jokers
            jokers_restante = qtd_joker;
            for (int i=0; i<qtd_cartas-1; i++){
                if (monte_clone[i].numero == JOKER && i == 0){ //se a primeira carta for joker
                    jokers_restante--;
                    if (monte_clone[i+1].numero == JOKER){//se a segunda tambem for joker
                        jokers_restante--;
                        monte_clone[i].numero = monte_clone[i+2].numero;
                        monte_clone[i+1].numero = monte_clone[i+2].numero;
                    } else { //se so a primeira for joker
                        monte_clone[i].numero = monte_clone[i+1].numero;
                    }
                }

                if (monte_clone[i].numero == JOKER && jokers_restante > 0){
                    jokers_restante--;
                    monte_clone[i].numero = monte_clone[i-1].numero;
                }
            }
            //se a ultima posicao for joker
            if (monte_clone[qtd_cartas-1].numero == JOKER){
                monte_clone[qtd_cartas-1].numero = monte_clone[qtd_cartas-2].numero;
            }

            //verificacao com os jokers substituidos
            for (int i=0; i<qtd_cartas-1; i++){
                for (int j=i+1; j<qtd_cartas; j++){
                    if (monte_clone[i].numero != monte_clone[j].numero || (monte_clone[i].naipe == monte_clone[j].naipe)){
                        if (monte_clone[i].naipe != JOKER && monte_clone[j].naipe != JOKER){ //se algum deles for joker, esta permitido ter naipe diferente
                            return 0;
                        }
                    }
                }
            }

        break;

        default:
            return -1;
        }
        atual_mesa = atual_mesa->prox;
    }
    return 1;
}

void Inverte_Lista(LISTA_CARTAS_PTR *Lista){
    g_print("ïnicio inverte\n");
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
    g_print("fim inverte\n\n");
}

int Carrega_Baralho(LISTA_CARTAS_PTR *Baralho, GtkWidget *Painel){
    Deleta_Lista(Baralho);

    FILE *Arquivo = fopen(LOCAL_FILE_BARALHO, "r");
    if(Arquivo == NULL)
        return 0;

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

        char interacao = (Busca_Carta(Baralho, Naipe, Numero, 1) == NULL) ? 1 : 2;
        Cria_Carta(Baralho, Naipe, Numero, Painel, interacao);
    }

    Inverte_Lista(Baralho);
    Imprime_Baralho(*Baralho);
    return 1;
}