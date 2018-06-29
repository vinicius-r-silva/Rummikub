#include <gtk/gtk.h>
#include <string.h>  /* for css */

#include "libs/data.h"
#include "libs/system.h"
#include "libs/eventos.h"

//TODO: testar se as cartas na distribuicao da mao ultrapassam a limitacao da area da mao
//TODO: Destruir as cartas quando excluido as cartas dos jogadores, da mesa, destruir as img dos jogadores... Necessario?

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

/*---- CSS ------------------*/
GtkCssProvider *provider;
GdkDisplay *display;
GdkScreen *screen;
/*---------------------------*/

//Cria o icone na janela
GdkPixbuf *create_pixbuf(const gchar * filename) {
  GdkPixbuf *pixbuf;
  GError *error = NULL;
  pixbuf = gdk_pixbuf_new_from_file(filename, &error);
  if (!pixbuf) {  fprintf(stderr, "%s\n", error->message);g_error_free(error);}
  return pixbuf;
}

JOGADORES_PTR Lista_Jogadores;

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

static LISTA_CARTAS_PTR Baralho;
static JOGADORES_PTR Jogadores;


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



void Imprime(LISTA_CARTAS_PTR Lista_Carta){
    while(Lista_Carta != NULL){
        g_print("%d | %d\n", Lista_Carta->numero, Lista_Carta->naipe);
        Lista_Carta = Lista_Carta->prox;
    }
    g_print("\n\n\n");
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
  Coloca_Borda_Jogador(atual->prox);
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




  printf("1\n");

  Baralho = NULL;
  Jogadores = NULL;
  Init_Baralho(&Baralho, fixed);	
  printf("2\n");

  Jogadores = (JOGADORES_PTR)malloc(sizeof(JOGADORES));
  Jogadores->Id = 0;
  Jogadores->prox = NULL;
  Jogadores->cartas = NULL;
  //Imprime(Baralho);

  printf("3\n\n");

  int cont = 0;
  for(cont = 0; cont < 58; cont++){
    Baralho_2_mao(&Baralho, &(Jogadores->cartas));
  }

  Imprime(Jogadores->cartas);
  Imprime_mao_jogador(&(Jogadores->cartas));

  Lista_Jogadores = NULL;
  criar_jogadores(&Lista_Jogadores, 3);
  printf("\n\nJogadores:\n");
  Imprime_Jodagores(Lista_Jogadores);


  constroi_janela_jogo(); //carrega funções do GTK para criar a janela
  g_object_unref(icon);
  gtk_main(); //cria janela 

  excluir_jogadores(&Lista_Jogadores);

  //Deleta Jodares
  //Deletea Mesa
  return 0;
}