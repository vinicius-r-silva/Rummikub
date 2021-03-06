#include "libs/eventos.h"

int prev_X = 0;
int prev_Y = 0;
extern GdkDevice *mouse;
extern GtkWidget *fixed;

extern LISTA_MESA_PTR Mesa;
extern LISTA_MESA_PTR Mesa_Backup;
extern LISTA_CARTAS_PTR Mao_Backup;
extern JOGADORES_PTR Lista_Jogadores;
extern LISTA_CARTAS_PTR Baralho_Global;

void clique_mouse(GtkWidget *event_box,GdkEventButton *event,gpointer data){
  gint x,y;
  gdk_device_get_position (mouse, NULL, &x, &y);
  prev_X = x;
  prev_Y = y;
}

gboolean mouse_moved(GtkWidget *widget,GdkEventMotion *event, gpointer user_data) {
    if (event->state & GDK_BUTTON1_MASK) {
        gint x, y;
        gdk_device_get_position (mouse, NULL, &x, &y);
        g_print("Coordinates: (%u,%u)\n", x,y);
        move_imagem(widget,x-prev_X,y-prev_Y);
        prev_X = x;
        prev_Y = y;
    }
    return 1;
}

void Imprime_cartas(LISTA_CARTAS_PTR Lista_Carta){
    while(Lista_Carta != NULL){
        g_print("%c | %c\n", int_2_hexa(Lista_Carta->numero), Int_2_Naipe(Lista_Carta->naipe));
        Lista_Carta = Lista_Carta->prox;
    }
    g_print("\n");
}

void imprime_mesa(LISTA_MESA_PTR *Lista_Mesas){
  LISTA_MESA_PTR atual = *Lista_Mesas;
  printf("comeco mesa: \n");
  while(atual != NULL){
    printf("Mesa: x: %d, y: %d, Qtd: %d\n", atual->x, atual->y, atual->N_Cartas);
    Imprime_cartas(atual->cartas);
    atual = atual->prox;
  }
  printf("fim mesa \n\n\n");
}

void Muda_Pos_Carta(LISTA_CARTAS_PTR *Cartas, int Naipe, int Numero, int interacao, int nova_pos){
  g_print("\t\t Entrou Muda_Pos_Carta\n");
  LISTA_CARTAS_PTR atual = *Cartas;
  int Pos_Carta_a_trocar = 0;

  LISTA_CARTAS_PTR Prev_Carta = NULL;
  LISTA_CARTAS_PTR Carta_a_trocar = NULL;

  if(*Cartas == NULL)
    return;

  while(atual != NULL && (atual->naipe != Naipe || atual->numero != Numero || atual->interacao != interacao)){
    Prev_Carta = atual;
    atual = atual->prox;
    Pos_Carta_a_trocar++;
  }
  Carta_a_trocar = atual;

  g_print("\t\t Pos_Carta_a_trocar: %d, nova_pos: %d\n", Pos_Carta_a_trocar, nova_pos);
  if(Pos_Carta_a_trocar == nova_pos || (Carta_a_trocar->prox == NULL && Pos_Carta_a_trocar < nova_pos))
    return;

  if (nova_pos == 0){
    Prev_Carta->prox = Carta_a_trocar->prox;
    Carta_a_trocar->prox = *Cartas;
    *Cartas = Carta_a_trocar;
    return;
  }

  int cont = 0;
  atual = *Cartas;
  LISTA_CARTAS_PTR Pos_Destino = NULL;
  LISTA_CARTAS_PTR Prev_Destino = NULL;
  while(atual != NULL && cont < nova_pos){
    Prev_Destino = atual;
    atual = atual->prox;
    cont++;
  }
  Pos_Destino = atual;

  if(Pos_Destino == NULL){
    if (Prev_Carta == NULL)
      *Cartas = Carta_a_trocar->prox;
    else
      Prev_Carta->prox = Carta_a_trocar->prox;

    Prev_Destino->prox = Carta_a_trocar;
    Carta_a_trocar->prox = NULL;
    return;
  }

  if (Pos_Carta_a_trocar + 1 == nova_pos){
    if (Prev_Carta == NULL)
      *Cartas = Pos_Destino;
    else
      Prev_Carta->prox = Pos_Destino;
    
    Carta_a_trocar->prox = Pos_Destino->prox;
    Pos_Destino->prox = Carta_a_trocar;
    return;
  }

  if (nova_pos + 1 == Pos_Carta_a_trocar){
    if (Prev_Destino == NULL)
      *Cartas = Carta_a_trocar;
    else
      Prev_Destino->prox = Carta_a_trocar;
    
    Pos_Destino->prox = Carta_a_trocar->prox;
    Carta_a_trocar->prox = Pos_Destino;
    return;
  }

  if(Prev_Carta == NULL)
    *Cartas = (*Cartas)->prox;
  else 
    Prev_Carta->prox = Carta_a_trocar->prox;
  
  Carta_a_trocar->prox = Pos_Destino;
  if(Prev_Destino == NULL)
    *Cartas = Carta_a_trocar;
  else
    Prev_Destino->prox = Carta_a_trocar;
}

void interface_mao_2_mesa(int Naipe, int Numero, char interacao, JOGADORES_PTR Jogador, int img_x, int img_y, LISTA_MESA_PTR *Lista_mesas, LISTA_CARTAS_PTR *backup_mao){
  LISTA_CARTAS_PTR *Origem = &(Jogador->cartas);
  int linha = 0, coluna = 0;
  Pixel_2_LinCol(&linha, &coluna, img_x, img_y, INICIO_X_MESA, INICIO_Y_MESA, (TAM_X_CARTA + TAM_X_ESPACO), (TAM_Y_CARTA + TAM_Y_ESPACO));

  int pos = 0;
  LISTA_MESA_PTR Monte = NULL;
  LinCol_2_Monte(&Monte, Lista_mesas, &pos, linha, coluna);

  int Nova_Lista = (pos == -1) ? 1 : 0;
  Imprime_cartas(*backup_mao);

  g_print("20\n");
  if(Monte != NULL){
    int Naipe_monte = Monte->cartas->naipe;
    int Numero_monte = Monte->cartas->numero;
    char Interacao_monte = Monte->cartas->interacao;
    if(Nova_Lista == 0 && Jogador->Jogada_Inicial == 1 && Busca_Carta(backup_mao, Naipe_monte, Numero_monte, Interacao_monte) == NULL)
      return;
  }

  g_print("30\n");
  mao_2_monte(Origem, &Monte, Naipe, Numero, pos, Nova_Lista);
  if(*Lista_mesas == NULL)
     *Lista_mesas = Monte;
}

void interface_mesa_2_mesa(int Naipe, int Numero, char interacao, int img_x, int img_y, LISTA_MESA_PTR *Lista_mesas, JOGADORES_PTR Jogador, LISTA_CARTAS_PTR *backup_mao){ 
  g_print("entrou interface_mesa_2_mesa\n");

  int linha = 0, coluna = 0;
  Pixel_2_LinCol(&linha, &coluna, img_x, img_y, INICIO_X_MESA, INICIO_Y_MESA, (TAM_X_CARTA + TAM_X_ESPACO), (TAM_Y_CARTA + TAM_Y_ESPACO));

  int pos = 0;
  LISTA_MESA_PTR Monte = NULL;
  LinCol_2_Monte(&Monte, Lista_mesas, &pos, linha, coluna);

  if(Jogador->Jogada_Inicial == 1 && Monte != NULL){
    int Naipe_monte = Monte->cartas->naipe;
    int Numero_monte = Monte->cartas->numero;
    char Interacao_monte = Monte->cartas->interacao;
    
    int Destino_mao = (Busca_Carta(backup_mao, Naipe_monte, Numero_monte, Interacao_monte) == NULL) ? 0 : 1;
    int Origem_mao  = (Busca_Carta(backup_mao, Naipe, Numero, interacao) == NULL) ? 0 : 1;
    if(Destino_mao != Origem_mao)
      return;
  }

  if(Monte != NULL && pos != -1 && Busca_Carta(&(Monte->cartas), Naipe, Numero, interacao) != NULL && coluna == Monte->x+Monte->N_Cartas)
    pos = -1;


  LISTA_MESA_PTR Monte_Origem = NULL;
  Busca_Carta_Mesa(Lista_mesas, &Monte_Origem, Naipe, Numero, interacao); 
  if (pos != -1 && Monte_Origem->x == Monte->x && Monte_Origem->y == Monte->y){
    g_print("3\n");
    Muda_Pos_Carta(&(Monte->cartas), Naipe, Numero, interacao, pos);
  }
  else{
    g_print("4\n");
    int Nova_Lista = (pos == -1) ? 1 : 0;
    mao_2_monte(&(Monte_Origem->cartas), &Monte, Naipe, Numero, pos, Nova_Lista);
    if(*Lista_mesas == NULL)
      *Lista_mesas = Monte;
    Monte_Origem->N_Cartas--;
  }

  imprime_mesa(Lista_mesas);
  g_print("fim interface_mesa_2_mesa\n");
}

void interface_mesa_2_mao(int Naipe, int Numero, char interacao, LISTA_CARTAS_PTR *mao, LISTA_CARTAS_PTR *backup_mao, int img_x, int img_y, LISTA_MESA_PTR *Lista_mesas){
  if (Busca_Carta(backup_mao, Naipe, Numero, interacao) == NULL)
    return;

  LISTA_MESA_PTR Monte;
  LISTA_CARTAS_PTR Carta = Busca_Carta_Mesa(Lista_mesas, &Monte, Naipe, Numero, interacao);

  int nova_pos;
  int linha = 0, coluna = 0;
  Pixel_2_LinCol(&linha, &coluna, img_x, img_y, INICIO_X_MAO, INICIO_Y_MAO, (TAM_X_CARTA + TAM_X_ESPACO), TAM_Y_CARTA*2);
  nova_pos = coluna + linha*N_MAX_COLUNAS;

  LISTA_CARTAS_PTR prev = NULL;
  LISTA_CARTAS_PTR atual = Monte->cartas;
  while(atual->naipe != Naipe || atual->numero != Numero){
    prev = atual;
    atual = atual->prox;
  }
  if(prev == NULL)
    Monte->cartas = atual->prox;
  else 
    prev->prox = atual->prox;

  int i = 0;
  prev = NULL;
  atual = *mao;
  while(atual != NULL && i < nova_pos){
    prev = atual;
    atual= atual->prox;
    i++;
  }

  if(prev == NULL)
    *mao = Carta;
  else
    prev->prox = Carta;

  Carta->prox = atual;

}

void Limpa_Monte_Vazios(LISTA_MESA_PTR *Lista_Mesas){
  if (*Lista_Mesas == NULL)
    return;
  
  g_print("1\n");
  if((*Lista_Mesas)->cartas == NULL && (*Lista_Mesas)->prox == NULL){
    free(*Lista_Mesas);
    *Lista_Mesas = NULL;
    return;
  }

  g_print("2\n");
  LISTA_MESA_PTR prev = NULL;
  LISTA_MESA_PTR atual = *Lista_Mesas;

  while(atual != NULL){
    g_print("3\n");
    if(atual->cartas == NULL){
      g_print("4\n");
      if(prev != NULL){
        prev->prox = atual->prox;
        free(atual);
        atual = prev->prox;
      }
      else{
        g_print("5\n");
        prev = atual;
        *Lista_Mesas = atual->prox;
        free(prev);
        prev = NULL;
        atual = atual->prox;
      }
    }
    else {
      prev = atual;
      atual = atual->prox;
    }
    
  }
}

gboolean focus_out(GtkWidget *image, GdkEvent *event, gpointer user_data){
  g_print("inicio focus_out\n");
  JOGADORES_PTR Jogador =  Jogador_Atual(Lista_Jogadores);
  if(Jogador == NULL)
    return 1;

  char interacao;
  int Naipe, Numero;
  int img_x = 0, img_y = 0;
  gtk_widget_translate_coordinates(image, gtk_widget_get_toplevel(image), 0, 0, &img_x, &img_y);

  EventBox_2_Carta(image, &Naipe, &Numero, &interacao);
  int Carta_Origem_Mao = 0;
  int Carta_Destino_Mao = 0;

  g_print("Na: %d, Nu: %d, inte: %d\n", Naipe, Numero, interacao);
  if(Busca_Carta(&(Jogador->cartas), Naipe, Numero, interacao) != NULL)
    Carta_Origem_Mao = 1;
  
  if(img_y > (FIM_Y_MESA))
    Carta_Destino_Mao = 1;  

  if(Carta_Origem_Mao && !Carta_Destino_Mao && !Jogador->Ja_Comprou){
    interface_mao_2_mesa(Naipe, Numero, interacao, Jogador, img_x, img_y, &Mesa, &Mao_Backup);
  }

  else if (Carta_Origem_Mao && Carta_Destino_Mao){
    g_print("Carta_Destino_Mao e Carta_Origem_Mao\n");
    int linha = 0, coluna = 0, nova_pos = 0;;
    Pixel_2_LinCol(&linha, &coluna, img_x, img_y, INICIO_X_MAO, INICIO_Y_MAO, (TAM_X_CARTA + TAM_X_ESPACO), TAM_Y_CARTA*2);

    nova_pos = coluna + linha*N_MAX_COLUNAS;
    g_print("lin:%d, col: %d, nova_pos: %d\n", linha, coluna, nova_pos);
    Muda_Pos_Carta(&(Jogador->cartas), Naipe, Numero, interacao, nova_pos);
  }

  else if(!Carta_Origem_Mao && !Carta_Destino_Mao){
    interface_mesa_2_mesa(Naipe, Numero, interacao, img_x, img_y, &Mesa, Jogador, &Mao_Backup);
  }

  else if(!Carta_Origem_Mao && Carta_Destino_Mao){
    interface_mesa_2_mao(Naipe, Numero, interacao, &(Jogador->cartas), &Mao_Backup, img_x, img_y, &Mesa);
  }

  g_print("Limpando a mesa: \n");
  Limpa_Monte_Vazios(&Mesa);
  g_print("Nova mesa: \n");
  imprime_mesa(&Mesa);
  g_print("fim limpa mesa: \n\n");

  Imprime_mao_jogador(&(Jogador->cartas), 0, 0, INICIO_X_MAO, INICIO_Y_MAO);
  Organiza_Mesa(&Mesa);
  atualiza_cartas_mesa(&Mesa);
  
  g_print("Fim focus_out\n\n");
  return 1;
}

void comprar_cartas_user(GtkWidget *widget, gpointer data){
  JOGADORES_PTR Jogador = Jogador_Atual(Lista_Jogadores);
  if(Jogador->Ja_Comprou == 1)
    return;

  Jogador->Ja_Comprou = 1;
  Baralho_2_mao(&Baralho_Global, &(Jogador->cartas));
  Imprime_mao_jogador(&(Jogador->cartas), 0, 0, INICIO_X_MAO, INICIO_Y_MAO);
  bt_desabilita_compra();
  atualiza_janela();

  return;
}

void finaliza_jogada_user(GtkWidget *widget, gpointer data){
  JOGADORES_PTR atual = Jogador_Atual(Lista_Jogadores);
  if(!verifica_mesa(&Mesa)){
    g_print("verifica mesa gg\n");
  }
  if(!valida_jogada(atual, &Mao_Backup, &Mesa_Backup, &Mesa)){
    g_print("valida_jogada gg\n");
  }

  if (!verifica_mesa(&Mesa) || (!valida_jogada(atual, &Mao_Backup, &Mesa_Backup, &Mesa) && Baralho_Global != NULL)){
    tela_erro_jogada();
    return;
  }

  if(atual->Jogada_Inicial == 1){
    LISTA_CARTAS_PTR check = Mao_Backup;
    while(check != NULL){
        if(Busca_Carta(&(atual->cartas), check->naipe, check->numero, check->interacao) == NULL)
             break;
        
        check = check->prox;
    }
    if(check != NULL)
       atual->Jogada_Inicial = 0;
  }
  
  atual->Ja_Comprou = 0;
  Tira_Borda_Jogador(atual);
  Oculta_mao_Jogador(atual);
  
  
  Deleta_Mesa(&Mesa_Backup);
  Mesa_Backup = duplicar_mesa(&Mesa);

  Deleta_Lista(&Mao_Backup);
  Mao_Backup = duplica_Cartas(&(atual->prox->cartas));

  int winer = vencedor(&Lista_Jogadores, &Baralho_Global);
  if (winer!= -1){
    if (winer > -1)
      tela_ganhador(winer);
    if (winer == -2)
      tela_empate();
  }

  bt_habilita_compra();
  tela_proximo_jogador(atual->prox->Id + 1);
    
  return;
}

void escolha_tipo_entrada(GtkWidget *bt, gint response_id, gpointer data){
  gtk_widget_destroy(data);
  const gchar *id_bt =  gtk_widget_get_name((bt));
  if(strcmp(id_bt,"bt_sim") == 0){
    if (Carrega_Baralho(&Baralho_Global, fixed) == 0){
      tela_erro_arquivo();
      atualiza_janela();
    } else{
      tela_home(Baralho_Global, &Lista_Jogadores, &Mao_Backup);
    }
  }
  else if(strcmp(id_bt,"bt_nao") == 0){
    Init_Baralho(&Baralho_Global, fixed);
    tela_home(Baralho_Global, &Lista_Jogadores, &Mao_Backup);
  }
  else if(strcmp(id_bt,"bt_erro_file") == 0){
    g_print("NAOO ERRO FILE\n");
    Init_Baralho(&Baralho_Global, fixed);
    tela_home(Baralho_Global, &Lista_Jogadores, &Mao_Backup);
  }
  else{
    return;
  }
}