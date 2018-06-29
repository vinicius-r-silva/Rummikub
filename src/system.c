#include "libs/system.h"

GtkWidget* Insere_Img_Interface(int Naipe, int Valor, GtkWidget *Painel, char Interacao){
  GtkWidget *img_carta;
  GtkWidget *event_box;

  char V = int_2_hexa(Valor);
  char N = Int_2_Naipe(Naipe);

  char resultado[27]; memset(resultado, 0, sizeof(char)*27);
  sprintf(resultado,"src/image/cartas/%c%c.png",V,N);
  //g_print("N: %2d (%c), V: %2d (%c)\n", Naipe, N, Valor, V);

  char NomeCarta[6];
  sprintf(NomeCarta,"%cC_%c%c",Interacao, V, N);
  NomeCarta[5] = '\0';

  char NomeEventBox[6];
  sprintf(NomeEventBox,"%cE_%c%c",Interacao, V,N);
  NomeEventBox[5] = '\0';

  event_box = gtk_event_box_new();
  gtk_fixed_put(GTK_FIXED(Painel), event_box,0, 0);
  gtk_widget_set_child_visible(event_box, 0);
  gtk_widget_set_name(event_box, NomeEventBox);

  img_carta = gtk_image_new_from_file(resultado);
  gtk_widget_set_name(img_carta, NomeCarta);
  gtk_container_add(GTK_CONTAINER(event_box), img_carta);

  g_signal_connect (G_OBJECT(event_box),"button_press_event",G_CALLBACK(clique_mouse), NULL);
  g_signal_connect (G_OBJECT(event_box),"motion_notify_event",G_CALLBACK(mouse_moved), NULL);
  g_signal_connect (G_OBJECT(event_box), "button-release-event",G_CALLBACK(focus_out), NULL);
  return event_box;
}

void Cria_Carta(LISTA_CARTAS_PTR *Baralho, int Naipe, int Numero, GtkWidget *Painel, char Interacao){
    if (Naipe > 4 || Numero > 13)
        return;

    LISTA_CARTAS_PTR nova = (LISTA_CARTAS_PTR)malloc(sizeof(LISTA_CARTAS));
    nova->naipe = Naipe;
    nova->numero = Numero;
    nova->prox = *Baralho;
    nova->img = Insere_Img_Interface(Naipe, Numero, Painel, Interacao);
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