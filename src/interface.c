#include "libs/interface.h"

extern GtkWidget *fixed;
extern GtkWidget *window;
extern GtkWidget *bt_compra_carta;
extern GtkWidget *bt_finaliza_jog;

void atualiza_janela(){
  gtk_widget_show_all(window);
}
void proximo_jogador(GtkWidget *bt, gint response_id, gpointer data){
  // gtk_overlay_reorder_overlay((fixed), data,0);
  // gtk_overlay_reorder_overlay (GtkOverlay *overlay,GtkWidget *child,gint position);
}
void tela_proximo_jogador(int jogador){
  GtkWidget *tela_proximo = gtk_fixed_new();
  gtk_fixed_put(GTK_FIXED(fixed), tela_proximo, 0, 0);

  GtkWidget *event_box = gtk_event_box_new();
  gtk_fixed_put(GTK_FIXED(tela_proximo), event_box,0, 0);
  gtk_widget_set_size_request(event_box, SCREEN_SIZE_X, SCREEN_SIZE_Y);
  gtk_widget_set_name(event_box,"tela_proximo");

  char resultado[30]; memset(resultado, 0, sizeof(char)*27);
  sprintf(resultado,"img_jogador_%d",jogador);

  GtkWidget *img_jogador = gtk_event_box_new();
  gtk_fixed_put(GTK_FIXED(tela_proximo), img_jogador,370,175);
  gtk_widget_set_size_request(img_jogador, 320, 80);
  gtk_widget_set_name(img_jogador,resultado);

  GtkWidget *bt_continuar = gtk_button_new_with_label("");
  gtk_fixed_put(GTK_FIXED(tela_proximo), bt_continuar,370, 305);
  gtk_widget_set_size_request(bt_continuar, 320, 67);
  gtk_widget_set_name(bt_continuar,"bt_continuar");

  //Evento fecha janela
  g_signal_connect(G_OBJECT(bt_continuar),"button_press_event",G_CALLBACK(proximo_jogador), tela_proximo); 
  atualiza_janela();
}
void tela_erro_arquivo(){
  GtkWidget *tela_erro_file = gtk_fixed_new();
  gtk_fixed_put(GTK_FIXED(fixed), tela_erro_file, 0, 0);

  GtkWidget *event_box = gtk_event_box_new();
  gtk_fixed_put(GTK_FIXED(tela_erro_file), event_box,0, 0);
  gtk_widget_set_size_request(event_box, SCREEN_SIZE_X, SCREEN_SIZE_Y);
  gtk_widget_set_name(event_box,"tela_erro_file_entrada");

  GtkWidget *bt_erro_file = gtk_button_new_with_label("");
  gtk_fixed_put(GTK_FIXED(tela_erro_file), bt_erro_file,415, 380);
  gtk_widget_set_size_request(bt_erro_file, 230, 67);
  gtk_widget_set_name(bt_erro_file,"bt_erro_file");

  g_signal_connect(G_OBJECT(bt_erro_file),"button_press_event",G_CALLBACK(escolha_tipo_entrada), tela_erro_file); 
  atualiza_janela();
}
void escolha_tipo_entrada(GtkWidget *bt, gint response_id, gpointer data){
  gtk_widget_destroy(data);
  const gchar *id_bt =  gtk_widget_get_name((bt));
  if(strcmp(id_bt,"bt_sim") == 0){
    g_print("SIMM\n");
    tela_erro_arquivo();
  }
  else if(strcmp(id_bt,"bt_nao") == 0){
    g_print("NAOO\n");
  }
  else if(strcmp(id_bt,"bt_erro_file") == 0){
    g_print("NAOO ERRO FILE\n");
  }
  else{
    return;
  }
}
void tela_tipo_entrada(){
  GtkWidget *tela_tipo = gtk_fixed_new();
  gtk_fixed_put(GTK_FIXED(fixed), tela_tipo, 0, 0);

  GtkWidget *event_box = gtk_event_box_new();
  gtk_fixed_put(GTK_FIXED(tela_tipo), event_box,0, 0);
  gtk_widget_set_size_request(event_box, SCREEN_SIZE_X, SCREEN_SIZE_Y);
  gtk_widget_set_name(event_box,"tela_tipo_entrada");

  GtkWidget *bt_sim = gtk_button_new_with_label("");
  gtk_fixed_put(GTK_FIXED(tela_tipo), bt_sim,252, 320);
  gtk_widget_set_size_request(bt_sim, 258, 75);
  gtk_widget_set_name(bt_sim,"bt_sim");

  GtkWidget *bt_nao = gtk_button_new_with_label("");
  gtk_fixed_put(GTK_FIXED(tela_tipo), bt_nao,550, 320);
  gtk_widget_set_size_request(bt_nao, 258, 75);
  gtk_widget_set_name(bt_nao,"bt_nao");

  //Evento fecha janela
  g_signal_connect(G_OBJECT(bt_sim),"button_press_event",G_CALLBACK(escolha_tipo_entrada), tela_tipo); 
  g_signal_connect(G_OBJECT(bt_nao),"button_press_event",G_CALLBACK(escolha_tipo_entrada), tela_tipo); 
  atualiza_janela();
}

void move_imagem(GtkWidget *image,int descola_X, int descola_Y){
  int img_X, img_Y;
  gtk_widget_translate_coordinates(image, gtk_widget_get_toplevel(image), 0, 0, &img_X, &img_Y);

  img_X += descola_X;
  img_Y += descola_Y;

  if (img_X < INICIO_X_MESA){
    img_X = INICIO_X_MESA;
  }
  else if(img_X > SCREEN_SIZE_X-TAM_X_CARTA){
    img_X = SCREEN_SIZE_X-TAM_X_CARTA;
  }

  if (img_Y < 1){
    img_Y = 1;
  }
  else if(img_Y > SCREEN_SIZE_Y-TAM_Y_CARTA){
    img_Y = SCREEN_SIZE_Y-TAM_Y_CARTA;
  }
  gtk_fixed_move (GTK_FIXED(fixed),image,img_X,img_Y);
}

GtkWidget* Insere_Carta_Interface(int Naipe, int Valor, GtkWidget *Painel, char Interacao){
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


void Insere_Img_Jogador(JOGADORES_PTR Jogador){
  char Caminho[40]; memset(Caminho, 0, sizeof(char)*40);

  if(Jogador->Sua_Vez)
    sprintf(Caminho,"src/image/user%d_foco.png",Jogador->Id+1);
  else
    sprintf(Caminho,"src/image/user%d.png",Jogador->Id+1);

  Jogador->img = gtk_image_new_from_file(Caminho); 
  gtk_fixed_put(GTK_FIXED(fixed), Jogador->img ,INICIO_X_JOGADORES, INICIO_Y_JOGADORES + ESPACO_Y_JOGADORES*Jogador->Id);
  atualiza_janela();
}


void Coloca_Borda_Jogador(JOGADORES_PTR Jogador){
  Jogador->Sua_Vez = 1;
  char Caminho[40]; memset(Caminho, 0, sizeof(char)*40);
  sprintf(Caminho,"src/image/user%d_foco.png",Jogador->Id+1);

  gtk_image_set_from_file(GTK_IMAGE(Jogador->img), Caminho);
}

void Tira_Borda_Jogador(JOGADORES_PTR Jogador){
  Jogador->Sua_Vez = 0;
  char Caminho[40]; memset(Caminho, 0, sizeof(char)*40);
  sprintf(Caminho,"src/image/user%d.png",Jogador->Id+1);

  gtk_image_set_from_file(GTK_IMAGE(Jogador->img), Caminho);
}

void atualiza_carta(GtkWidget *img, int x, int y){
  gtk_fixed_move (GTK_FIXED(fixed), img, x, y);
}


void Imprime_mao_jogador(LISTA_CARTAS_PTR *Mao, int linha, int coluna, int Pixel_X_Inicial, int Pixel_Y_Inicial){
	LISTA_CARTAS_PTR atual = *Mao;
  
  GtkWidget *Img;
  int Pos_x = 0, Pos_y = 0;


  while(atual != NULL){
    Img = atual->img;
    Grid_2_Pixel(linha, coluna, &Pos_x, &Pos_y, Pixel_X_Inicial, Pixel_Y_Inicial);

    atualiza_carta(Img, Pos_x, Pos_y);
    gtk_widget_set_child_visible(Img, 1);

    atual = atual->prox;

    coluna++;
    if(coluna > N_MAX_COLUNAS){
      coluna = 0;
      linha++;
    }
  }
}

void atualiza_cartas_mesa(LISTA_MESA_PTR *Lista_Mesas){
  LISTA_MESA_PTR atual = *Lista_Mesas;

  while(atual != NULL){
    Imprime_mao_jogador(&(atual->cartas), atual->y, atual->x, INICIO_X_MESA, INICIO_Y_MESA);
    atual = atual->prox;
  }
}

void fecha_tela(GtkDialog *dialog, gint response_id, gpointer callback_params){
  gtk_widget_destroy((callback_params));
  return;
}

//Cria tela de bem vindo para os usuarios
void tela_bem_vindo(){
  GtkWidget *tela_inicial = gtk_fixed_new();
  gtk_fixed_put(GTK_FIXED(fixed), tela_inicial, 0, 0);

  GtkWidget *event_box = gtk_event_box_new();
  gtk_fixed_put(GTK_FIXED(tela_inicial), event_box,0, 0);
  gtk_widget_set_size_request(event_box, SCREEN_SIZE_X, SCREEN_SIZE_Y);
  gtk_widget_set_name(event_box,"tela_bem_vindo");


  GtkWidget *bt_pronto = gtk_button_new_with_label("");
  gtk_fixed_put(GTK_FIXED(tela_inicial), bt_pronto,401, 315);
  gtk_widget_set_size_request(bt_pronto, 258, 65);
  gtk_widget_set_name(bt_pronto,"bt_pronto");

  //Evento fecha janela
  g_signal_connect(G_OBJECT(bt_pronto),"button_press_event",G_CALLBACK(fecha_tela), tela_inicial); 
}

//Cria tela de erro na mesa
void tela_erro_jogada(){
  GtkWidget *tela_erro_jogada = gtk_fixed_new();
  gtk_fixed_put(GTK_FIXED(fixed), tela_erro_jogada, 0, 0);

  GtkWidget *event_box = gtk_event_box_new();
  gtk_fixed_put(GTK_FIXED(tela_erro_jogada), event_box,0, 0);
  gtk_widget_set_size_request(event_box, SCREEN_SIZE_X, SCREEN_SIZE_Y);
  gtk_widget_set_name(event_box,"tela_erro_jogada");

  GtkWidget *bt_pronto = gtk_button_new_with_label("");
  gtk_fixed_put(GTK_FIXED(tela_erro_jogada), bt_pronto,447, 355);
  gtk_widget_set_size_request(bt_pronto, 166, 46);
  gtk_widget_set_name(bt_pronto,"bt_ok");

  //Evento fecha janela
  g_signal_connect(G_OBJECT(bt_pronto),"button_press_event",G_CALLBACK(fecha_tela), tela_erro_jogada); 
  atualiza_janela();
}


//Cria tela ganhador do jogo
void tela_ganhador(int jogador){
  GtkWidget *tela_ganha = gtk_fixed_new();
  gtk_fixed_put(GTK_FIXED(fixed), tela_ganha, 0, 0);

  GtkWidget *event_box = gtk_event_box_new();
  gtk_fixed_put(GTK_FIXED(tela_ganha), event_box,0, 0);
  gtk_widget_set_size_request(event_box, SCREEN_SIZE_X, SCREEN_SIZE_Y);
  gtk_widget_set_name(event_box,"tela_ganha");

  char resultado[30]; memset(resultado, 0, sizeof(char)*27);
  sprintf(resultado,"img_jogador_%d",jogador);

  GtkWidget *img_jogador = gtk_event_box_new();
  gtk_fixed_put(GTK_FIXED(tela_ganha), img_jogador,370,210);
  gtk_widget_set_size_request(img_jogador, 320, 80);
  gtk_widget_set_name(img_jogador,resultado);

  GtkWidget *bt_final = gtk_button_new_with_label("");
  gtk_fixed_put(GTK_FIXED(tela_ganha), bt_final,447, 355);
  gtk_widget_set_size_request(bt_final, 166, 46);
  gtk_widget_set_name(bt_final,"bt_final");

  //Evento fecha janela
  g_signal_connect(G_OBJECT(bt_final),"button_press_event",G_CALLBACK(fecha_tela),tela_ganha); 
  atualiza_janela();
}

void tela_empate(){
  GtkWidget *tela_empate = gtk_fixed_new();
  gtk_fixed_put(GTK_FIXED(fixed), tela_empate, 0, 0);

  GtkWidget *event_box = gtk_event_box_new();
  gtk_fixed_put(GTK_FIXED(tela_empate), event_box,0, 0);
  gtk_widget_set_size_request(event_box, SCREEN_SIZE_X, SCREEN_SIZE_Y);
  gtk_widget_set_name(event_box,"tela_empate");

  //JOGADORES QUE EMPATARAM SERÃO CRIADOS AQUI
  
  GtkWidget *bt_final = gtk_button_new_with_label("");
  gtk_fixed_put(GTK_FIXED(tela_empate), bt_final,447, 355);
  gtk_widget_set_size_request(bt_final, 166, 46);
  gtk_widget_set_name(bt_final,"bt_final");

  //Evento fecha janela
  g_signal_connect(G_OBJECT(bt_final),"button_press_event",G_CALLBACK(fecha_tela),tela_empate); 
  atualiza_janela();
}

//Desabilita botão de comprar carta
void bt_desabilita_compra(){
  GtkStyleContext *context;
  context = gtk_widget_get_style_context(bt_compra_carta);
  gtk_style_context_add_class(context,"bt_compra_carta_db");
  g_signal_connect(G_OBJECT(bt_compra_carta),"button_press_event",G_CALLBACK(NULL), NULL); 

}

//Habilita compra de cartas
void bt_habilita_compra(){
  GtkStyleContext *context;
  context = gtk_widget_get_style_context(bt_compra_carta);
  gtk_style_context_remove_class(context,"bt_compra_carta_db");
  g_signal_connect(G_OBJECT(bt_compra_carta),"button_press_event",G_CALLBACK(comprar_cartas_user), NULL); 
}

//Altera botão nova jogada para iniciar outro jogador
// void troca_bt_jogador(){
//   GtkStyleContext *context;
//   context = gtk_widget_get_style_context(bt_finaliza_jog);
//   gtk_style_context_add_class(context,"bt_novo_jogador");
// }

void Oculta_mao_Jogador(JOGADORES_PTR Jogador){
  LISTA_CARTAS_PTR atual = Jogador->cartas;
  while(atual != NULL){
    gtk_widget_set_child_visible(atual->img, 0);
    atual = atual->prox;
  }
}

