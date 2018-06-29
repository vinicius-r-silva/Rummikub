#include <gtk/gtk.h>
#include <string.h>  /* for css */

#include "libs/data.h"
#include "libs/system.h"

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
int prev_X = 0;
int prev_Y = 0;
GdkDevice *mouse;

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

//////////MOUSE////////////////////////
void clique_mouse(GtkWidget *event_box,GdkEventButton *event,gpointer data){
  gint x,y;
  gdk_device_get_position (mouse, NULL, &x, &y);
  prev_X = x;
  prev_Y = y;

}
void move_imagem(GtkWidget *image,int descola_X, int descola_Y){
  int img_X, img_Y;
  gtk_widget_translate_coordinates(image, gtk_widget_get_toplevel(image), 0, 0, &img_X, &img_Y);

  img_X += descola_X;
  img_Y += descola_Y;

  if (img_X < 1){
    img_X = 1;
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
static gboolean mouse_moved(GtkWidget *widget,GdkEventMotion *event, gpointer user_data) {
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
void init_mouse(){
  GdkSeat * seat;
  GdkDisplay *display;
  display = gdk_display_get_default();
  seat = gdk_display_get_default_seat (display);
  //device_manager = gdk_display_get_device_manager (display);
  mouse = gdk_seat_get_pointer (seat);
}
//////////MOUSE////////////////////////

void carrega_estilo_jogo(){
    provider = gtk_css_provider_new ();
    display = gdk_display_get_default ();
    screen = gdk_display_get_default_screen (display);
    gtk_style_context_add_provider_for_screen (screen, GTK_STYLE_PROVIDER (provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
    const gchar* home = "glade/style.css";
    GError *error = 0;
    gtk_css_provider_load_from_file(provider, g_file_new_for_path(home), &error);
    g_object_unref(provider);
}

//Constroi janela - funções do GTK
void constroi_janela_jogo(){
  g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);
  gtk_widget_show_all(window);
}

//Desabilita botão de comprar carta
void bt_desabilita_compra(){
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

gboolean focus_out(GtkWidget *widget, GdkEvent  *event,gpointer   user_data){
  g_print("SAIU");
  return 1;
}

void gerar_mao(int Naipe, int val, int x, int y){
  GtkWidget *img_carta;
  GtkWidget *event_box;

  char V = int_2_hexa(val);
  char N = Int_2_Naipe(Naipe);

  char resultado[27]; memset(resultado, 0, sizeof(char)*27);
  sprintf(resultado,"src/image/cartas/%c%c.png",V,N);
  g_print("N: %2d, V: %2d, x: %2d, y: %2d, Res: %s\n", Naipe, val, x, y, resultado);


  char Nome[3];
  sprintf(Nome,"%c%c",V,N);
  Nome[2] = '\0';

  event_box = gtk_event_box_new();
  gtk_fixed_put(GTK_FIXED(fixed), event_box,x, y);

  img_carta = gtk_image_new_from_file(resultado);
  gtk_widget_set_name(img_carta, Nome);
  //gtk_fixed_put(GTK_FIXED(fixed), img_carta,x, y);
  gtk_container_add(GTK_CONTAINER(event_box), img_carta);

  g_signal_connect (G_OBJECT(event_box),"button_press_event",G_CALLBACK(clique_mouse), NULL);
  g_signal_connect (G_OBJECT(event_box),"motion_notify_event",G_CALLBACK(mouse_moved), NULL);
  g_signal_connect (G_OBJECT(event_box), "button-release-event",G_CALLBACK(focus_out), NULL);

}

void Imprime_mao_jogador(LISTA_CARTAS_PTR *Lista_Mao){
	LISTA_CARTAS_PTR atual = *Lista_Mao;
    int cont = 0;
    int x = 0, y = 0;
    int Naipe = 0, Valor = 0;
    while(Cartas_Mao(&x, &y, &Naipe, &Valor, cont, atual)){
    	cont++;
    	//g_print("N: %d, V: %d, x: %d, y: %d\n", Naipe, Valor, x, y);
    	gerar_mao(Naipe, Valor, x, y);
    }
}

void Imprime(LISTA_CARTAS_PTR Lista_Carta){
    while(Lista_Carta != NULL){
        g_print("%d | %d\n", Lista_Carta->numero, Lista_Carta->naipe);
        Lista_Carta = Lista_Carta->prox;
    }
    g_print("\n\n\n");
}
//
void comprar_cartas_user(){
  g_print("-> Apertou comprar cartas\n");
  return;
}
//
void finaliza_jogada_user(){
  g_print("-> Apertou finalizar jogada\n");
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

  img_user1 = gtk_image_new_from_file("src/image/user1_foco.png"); //primeiro jogados começa com foco. (Borda azul)
  gtk_fixed_put(GTK_FIXED(fixed), img_user1,20, 15);

  img_user2 = gtk_image_new_from_file("src/image/user2.png"); 
  gtk_fixed_put(GTK_FIXED(fixed), img_user2, 20, 95);

  img_user3 = gtk_image_new_from_file("src/image/user3.png"); 
  gtk_fixed_put(GTK_FIXED(fixed), img_user3, 20, 175);

  img_user4 = gtk_image_new_from_file("src/image/user4.png"); 
  gtk_fixed_put(GTK_FIXED(fixed), img_user4, 20, 255);

  img_user5 = gtk_image_new_from_file("src/image/user5.png"); 
  gtk_fixed_put(GTK_FIXED(fixed), img_user5, 20, 335);
}

int main(int argc, char *argv[]) {
  gtk_init(&argc, &argv); //pega endereços dos parametros
  init_mouse();
  
  //cria janela do windows
  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title(GTK_WINDOW(window), "Rummikub.c");
  gtk_window_set_default_size(GTK_WINDOW(window), 1000, 563);
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

  Baralho = NULL;
  Jogadores = NULL;
  Cria_Baralho(&Baralho);	

  Jogadores = (JOGADORES_PTR)malloc(sizeof(JOGADORES));
  Jogadores->Id = 0;
  Jogadores->prox = NULL;
  Jogadores->cartas = NULL;
  Imprime(Baralho);

  int cont = 0;
  for(cont = 0; cont < 14; cont++){
    Baralho_2_mao(&Baralho, &(Jogadores->cartas));
  }

  Imprime(Jogadores->cartas);
  Imprime_mao_jogador(&(Jogadores->cartas));

  constroi_janela_jogo(); //carrega funções do GTK para criar a janela
  g_object_unref(icon);
  gtk_main(); //cria janela 

  return 0;
}