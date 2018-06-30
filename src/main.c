#include <gtk/gtk.h>
#include <string.h>  /* for css */

#include "libs/data.h"
#include "libs/system.h"
#include "libs/eventos.h"

//TODO: testar se as cartas na distribuicao da mao ultrapassam a limitacao da area da mao
//TODO: Destruir as cartas quando excluido as cartas dos jogadores, da mesa, destruir as img dos jogadores... Necessario?
struct bt_jog{
  GtkWidget *n_2;
  GtkWidget *n_3;
  GtkWidget *n_4;
  GtkWidget *n_5;
  GtkWidget *obj_home;
  int bt_ativo;
};

typedef struct bt_jog LISTA_BT_JOG;
typedef LISTA_BT_JOG *LISTA_BT_JOG_PTR;

GdkDevice *mouse;

GtkWidget *window;
GtkWidget *fixed;

GtkWidget *bt_compra_carta;
GtkWidget *bt_finaliza_jog;

GtkWidget *image;
GtkWidget *img_mesa;
GtkWidget *img_user1;
GtkWidget *img_user2;
GtkWidget *img_user3;
GtkWidget *img_user4;
GtkWidget *img_user5;

GtkWidget *img_user1_foco;
GtkWidget *img_user2_foco;
GtkWidget *img_user3_foco;
GtkWidget *img_user4_foco;
GtkWidget *img_user5_foco;

GtkWidget *img_mao;

JOGADORES_PTR Lista_Jogadores;
static LISTA_CARTAS_PTR Baralho;

/*---- CSS ------------------*/
GtkCssProvider *provider;
GdkDisplay *display;
GdkScreen *screen;
/*---------------------------*/
void fecha_tela(GtkDialog *dialog, gint response_id, gpointer callback_params){
  gtk_widget_destroy((callback_params));
  return;
}
void Imprime(LISTA_CARTAS_PTR Lista_Carta){
    while(Lista_Carta != NULL){
        g_print("%d | %d\n", Lista_Carta->numero, Lista_Carta->naipe);
        Lista_Carta = Lista_Carta->prox;
    }
    g_print("\n\n\n");
}
void cria_mao_jogadores(JOGADORES_PTR *Lista_Jogadores){
  JOGADORES_PTR atual = *Lista_Jogadores;
  int cont;
  int prev_id = 0;

  for(cont = 0; cont < 14; cont++){
    Baralho_2_mao(&Baralho, &(atual->cartas));
  }
  atual = atual->prox;

  while(prev_id < atual->Id){
    for(cont = 0; cont < 14; cont++){
      Baralho_2_mao(&Baralho, &(atual->cartas));
    }
    prev_id = atual->Id;
    atual = atual->prox;
  }
}
void atualiza_carta(GtkWidget *img, int x, int y){
  gtk_fixed_move (GTK_FIXED(fixed), img, x, y);
}
void Imprime_mao_jogador(LISTA_CARTAS_PTR *Mao){
  LISTA_CARTAS_PTR atual = *Mao;
  
  GtkWidget *Img;
  int linha = 0, coluna = 0;
  int Pos_x = 0, Pos_y = 0;


  while(atual != NULL){
    Img = atual->img;
    Grid_2_Pixel(linha, coluna, &Pos_x, &Pos_y, INICIO_X_MAO, INICIO_Y_MAO);

    atualiza_carta(Img, Pos_x, Pos_y);
    gtk_widget_set_child_visible(Img, 1);
    g_print("%d - N: %s, x: %d, y: %d, N: %c, V: %c\n", coluna, gtk_widget_get_name(Img), Pos_x, Pos_y, Int_2_Naipe(atual->naipe), int_2_hexa(atual->numero));

    atual = atual->prox;

    coluna++;
    if(coluna > N_MAX_COLUNAS){
      coluna = 0;
      linha++;
    }
  }
}

void Imprime_Jodagores(JOGADORES_PTR Lista_Jogadores){
  if (Lista_Jogadores == NULL)
    return;

  while(Lista_Jogadores->Id < Lista_Jogadores->prox->Id){
    printf("%d\n", Lista_Jogadores->Id);
    Lista_Jogadores = Lista_Jogadores->prox;
  }
  printf("%d\n\n\n", Lista_Jogadores->Id);
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

}
void comeca_jogo(GtkWidget *bt, gint response_id, LISTA_BT_JOG_PTR data){
  g_print("\n\n%d\n\n",data->bt_ativo);
  if(data->bt_ativo > 1){
    gtk_widget_destroy((data->obj_home));

    criar_jogadores(&Lista_Jogadores,data->bt_ativo);
    printf("\n\nJogadores:\n");

    Imprime_Jodagores(Lista_Jogadores);

    cria_mao_jogadores(&Lista_Jogadores);

    Imprime(Lista_Jogadores->cartas);
    Imprime_mao_jogador(&(Lista_Jogadores->cartas));
    tela_bem_vindo();
    atualiza_janela();
  }
  else{
    g_print("Nao selecionou n jogadores");
  }
  return;
}
void ativa_n_jog(GtkWidget *bt, gint response_id, LISTA_BT_JOG_PTR data){
  const gchar *id_bt =  gtk_widget_get_name((bt));
  //g_print("%s\n", id_bt);

  GtkStyleContext *context2 = gtk_widget_get_style_context(data->n_2);
  gtk_style_context_remove_class(context2,"bt_n_jog_2_foco");
  GtkStyleContext *context3 = gtk_widget_get_style_context(data->n_3);
  gtk_style_context_remove_class(context3,"bt_n_jog_3_foco");
  GtkStyleContext *context4 = gtk_widget_get_style_context(data->n_4);
  gtk_style_context_remove_class(context4,"bt_n_jog_4_foco");
  GtkStyleContext *context5 = gtk_widget_get_style_context(data->n_5);
  gtk_style_context_remove_class(context5,"bt_n_jog_5_foco");


  GtkStyleContext *context = gtk_widget_get_style_context(bt);
  if(strcmp(id_bt,"bt_n_jog_2") == 0){
    gtk_style_context_add_class(context,"bt_n_jog_2_foco");
    data->bt_ativo = 2;
  }
  else if(strcmp(id_bt,"bt_n_jog_3") == 0){
    gtk_style_context_add_class(context,"bt_n_jog_3_foco");
    data->bt_ativo = 3;
  }
  else if(strcmp(id_bt,"bt_n_jog_4") == 0){
    gtk_style_context_add_class(context,"bt_n_jog_4_foco");
    data->bt_ativo = 4;
  }
  else if(strcmp(id_bt,"bt_n_jog_5") == 0){
    gtk_style_context_add_class(context,"bt_n_jog_5_foco");
    data->bt_ativo = 5;
  }
  else{
    return;
  }
  return;
}
void tela_home(){
  GtkWidget *home = gtk_fixed_new();
  gtk_fixed_put(GTK_FIXED(fixed), home, 0, 0);

  GtkWidget *event_box = gtk_event_box_new();
  gtk_fixed_put(GTK_FIXED(home), event_box,0, 0);
  gtk_widget_set_size_request(event_box, SCREEN_SIZE_X, SCREEN_SIZE_Y);
  gtk_widget_set_name(event_box,"tela_home");

  GtkWidget *n_jogador2 = gtk_button_new_with_label("");
  gtk_fixed_put(GTK_FIXED(home), n_jogador2,340,300);
  gtk_widget_set_size_request(n_jogador2, 70, 67);
  gtk_widget_set_name(n_jogador2,"bt_n_jog_2");
  GtkStyleContext *context_bt1 = gtk_widget_get_style_context(n_jogador2);
  gtk_style_context_add_class(context_bt1,"bt_n_jog_2");

  GtkWidget *n_jogador3 = gtk_button_new_with_label("");
  gtk_fixed_put(GTK_FIXED(home), n_jogador3,442,300);
  gtk_widget_set_size_request(n_jogador3, 70, 67);
  gtk_widget_set_name(n_jogador3,"bt_n_jog_3");
   GtkStyleContext *context_bt2 = gtk_widget_get_style_context(n_jogador3);
  gtk_style_context_add_class(context_bt2,"bt_n_jog_3");

  GtkWidget *n_jogador4 = gtk_button_new_with_label("");
  gtk_fixed_put(GTK_FIXED(home), n_jogador4,544,300);
  gtk_widget_set_size_request(n_jogador4, 70, 67);
  gtk_widget_set_name(n_jogador4,"bt_n_jog_4");
   GtkStyleContext *context_bt3 = gtk_widget_get_style_context(n_jogador4);
  gtk_style_context_add_class(context_bt3,"bt_n_jog_4");

  GtkWidget *n_jogador5 = gtk_button_new_with_label("");
  gtk_fixed_put(GTK_FIXED(home), n_jogador5,646,300);
  gtk_widget_set_size_request(n_jogador5, 70, 67);
  gtk_widget_set_name(n_jogador5,"bt_n_jog_5");
   GtkStyleContext *context_bt4 = gtk_widget_get_style_context(n_jogador5);
  gtk_style_context_add_class(context_bt4,"bt_n_jog_5");

  GtkWidget *bt_inicial = gtk_button_new_with_label("");
  gtk_fixed_put(GTK_FIXED(home), bt_inicial,400, 415);
  gtk_widget_set_size_request(bt_inicial, 260, 66);
  gtk_widget_set_name(bt_inicial,"bt_iniciar");

  LISTA_BT_JOG_PTR bts_n_jog = (LISTA_BT_JOG_PTR)malloc(sizeof(LISTA_BT_JOG));
  memset(bts_n_jog,0,sizeof(LISTA_BT_JOG));
  bts_n_jog->n_2 = n_jogador2;
  bts_n_jog->n_3 = n_jogador3;
  bts_n_jog->n_4 = n_jogador4;
  bts_n_jog->n_5 = n_jogador5;

  bts_n_jog->obj_home = home;
  bts_n_jog->bt_ativo = 0;

  //
  g_signal_connect(G_OBJECT(n_jogador2),"button_press_event",G_CALLBACK(ativa_n_jog),bts_n_jog); 
  g_signal_connect(G_OBJECT(n_jogador3),"button_press_event",G_CALLBACK(ativa_n_jog),bts_n_jog); 
  g_signal_connect(G_OBJECT(n_jogador4),"button_press_event",G_CALLBACK(ativa_n_jog),bts_n_jog); 
  g_signal_connect(G_OBJECT(n_jogador5),"button_press_event",G_CALLBACK(ativa_n_jog),bts_n_jog);

  g_signal_connect(G_OBJECT(bt_inicial),"button_press_event",G_CALLBACK(comeca_jogo),bts_n_jog);

}

//Cria o icone na janela
GdkPixbuf *create_pixbuf(const gchar * filename) {
  GdkPixbuf *pixbuf;
  GError *error = NULL;
  pixbuf = gdk_pixbuf_new_from_file(filename, &error);
  if (!pixbuf) {  fprintf(stderr, "%s\n", error->message);g_error_free(error);}
  return pixbuf;
}



void init_mouse(){
  GdkSeat * seat;
  GdkDisplay *display;
  display = gdk_display_get_default();
  seat = gdk_display_get_default_seat (display);
  //device_manager = gdk_display_get_device_manager (display);
  mouse = gdk_seat_get_pointer (seat);
}

//////////MOUSE//////////////////////////////////MOUSE////////////////////////

void carrega_estilo_jogo(){
    provider = gtk_css_provider_new ();
    display = gdk_display_get_default ();
    screen = gdk_display_get_default_screen (display);
    gtk_style_context_add_provider_for_screen (screen, GTK_STYLE_PROVIDER (provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
    const gchar* home = "glade/style.css";
    GError *error = 0;
    gtk_css_provider_load_from_file(provider, g_file_new_for_path(home), &error);
    g_object_unref (provider);
}

//Constroi janela - funções do GTK
void constroi_janela_jogo(){
    g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);
    gtk_widget_show_all(window);
}

//Desabilita botão de comprar carta
void bt_desabilita_compra(GtkWidget *widget, gpointer data){
  GtkStyleContext *context;
  context = gtk_widget_get_style_context(bt_compra_carta);
  gtk_style_context_add_class(context,"bt_compra_carta_db");
}

//Altera botão nova jogada para iniciar outro jogador
void troca_bt_jogador(){
  GtkStyleContext *context;
  context = gtk_widget_get_style_context(bt_finaliza_jog);
  gtk_style_context_add_class(context,"bt_novo_jogador");
}


void Oculta_mao_Jogador(JOGADORES_PTR Jogador){
  LISTA_CARTAS_PTR atual = Jogador->cartas;
  while(atual != NULL){
    gtk_widget_set_child_visible(atual->img, 0);
    atual = atual->prox;
  }
}



void comprar_cartas_user(GtkWidget *widget, gpointer data){
  g_print("-> Apertou comprar cartas\n");
  return;
}

void finaliza_jogada_user(GtkWidget *widget, gpointer data){
  JOGADORES_PTR atual = Lista_Jogadores;
  int cont = 0;
  for (cont = 0; cont < 10 && !atual->Sua_Vez; cont++)
    atual = atual->prox;
  
  if(cont == 10)
    return;
  
  Tira_Borda_Jogador(atual);
  Oculta_mao_Jogador(atual);
  Coloca_Borda_Jogador(atual->prox);
  Imprime_mao_jogador(&(atual->prox->cartas));
  return;
}



//Adiciona botões no jogo e seus eventos
void cria_botoes_jogo(){
  //Cria botão de COMPRA CARTAS
  bt_compra_carta = gtk_button_new_with_label("");
  gtk_fixed_put(GTK_FIXED(fixed), bt_compra_carta, 20,420);
  gtk_widget_set_size_request(bt_compra_carta, 88, 60);
  gtk_widget_set_name(bt_compra_carta,"bt_compra_carta");
  
  //Adiciona a class para o botão COMPRA CARTAS
  GtkStyleContext *context_bt1 = gtk_widget_get_style_context(bt_compra_carta);
  gtk_style_context_add_class(context_bt1,"bt_compra_carta");
    
  //Evento que realiza COMPRA CARTAS para o usuario
  g_signal_connect(G_OBJECT(bt_compra_carta),"button_press_event",G_CALLBACK(comprar_cartas_user), NULL); 

  //Cria botão de FINALIZAR JOGADA
  bt_finaliza_jog = gtk_button_new_with_label("");
  gtk_fixed_put(GTK_FIXED(fixed), bt_finaliza_jog, 20,485);
  gtk_widget_set_size_request(bt_finaliza_jog, 88, 65);
  gtk_widget_set_name(bt_finaliza_jog,"bt_finaliza_jog");
  
  GtkStyleContext *context_bt2 = gtk_widget_get_style_context(bt_finaliza_jog);
  gtk_style_context_add_class(context_bt2,"bt_finaliza_jog");
  
  //Evento que realiza FINALIZAR JOGADA para o usuario
  g_signal_connect(G_OBJECT(bt_finaliza_jog),"button_press_event",G_CALLBACK(finaliza_jogada_user), NULL); 
}

//Função para criar imagens do jogo
void cria_jogo_imagens(){
  img_mesa = gtk_image_new_from_file("src/image/mesa.png"); 
  gtk_fixed_put(GTK_FIXED(fixed), img_mesa,120, 15);

  img_mao = gtk_image_new_from_file("src/image/mao.png"); 
  gtk_fixed_put(GTK_FIXED(fixed), img_mao,120, 420);
}


int main(int argc, char *argv[]) {
  gtk_init(&argc, &argv);//pega endereços dos parametros
  init_mouse();

  //cria janela do jogo
  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title(GTK_WINDOW(window), "Rummikub");
  gtk_window_set_default_size(GTK_WINDOW(window), SCREEN_SIZE_X, SCREEN_SIZE_Y);
  gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
  gtk_window_set_resizable(GTK_WINDOW(window), FALSE);

  GdkPixbuf *icon = create_pixbuf("src/image/icon.png");  
  gtk_window_set_icon(GTK_WINDOW(window), icon);

  //Cria CONTAINER no windows, onde serão criados os objetos
  fixed = gtk_fixed_new();
  gtk_container_add(GTK_CONTAINER(window), fixed);

  cria_botoes_jogo(); //carrega botões no jogo
  cria_jogo_imagens(); //carrega imagens do jogo Ex: Mesa, img dos jogadores, fundo da mão do jogador
  carrega_estilo_jogo(); //carrega dados para criar o estilo do jogo
  ///////////////////////////////////////////////////////////////////////////////
  

  Baralho = NULL;
  Init_Baralho(&Baralho, fixed);

  Lista_Jogadores = NULL;

  tela_home();
  constroi_janela_jogo(); //carrega funções do GTK para criar a janela
  

  g_object_unref(icon);
  gtk_main(); //cria janela 

  excluir_jogadores(&Lista_Jogadores);
  //Deleta Jodares
  //Deletea Mesa
  return 0;
}