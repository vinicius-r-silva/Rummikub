#include <gtk/gtk.h>
#include <string.h>  /* for css */

#include "libs/data.h"
#include "libs/system.h"
#include "libs/eventos.h"

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

void init_mouse(){
  GdkSeat * seat;
  GdkDisplay *display;
  display = gdk_display_get_default();
  seat = gdk_display_get_default_seat (display);
  //device_manager = gdk_display_get_device_manager (display);
  mouse = gdk_seat_get_pointer (seat);
}

//////////MOUSE//////////////////////////////////MOUSE////////////////////////

void css_add(){
    provider = gtk_css_provider_new ();
    display = gdk_display_get_default ();
    screen = gdk_display_get_default_screen (display);
    gtk_style_context_add_provider_for_screen (screen, GTK_STYLE_PROVIDER (provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
    const gchar* home = "glade/style.css";
    GError *error = 0;
    gtk_css_provider_load_from_file(provider, g_file_new_for_path(home), &error);
    g_object_unref (provider);
}

void constroi(){
    g_signal_connect(G_OBJECT(window), "destroy", 
    G_CALLBACK(gtk_main_quit), NULL);
    gtk_widget_show_all(window);
}

void bt_desabilita_compra(){
  GtkStyleContext *context;
  context = gtk_widget_get_style_context(bt_compra_carta);
  gtk_style_context_add_class(context,"bt_compra_carta_db");
}

void troca_bt_jogador(){
 
}

static LISTA_CARTAS_PTR Baralho;
static JOGADORES_PTR Jogadores;


void atualiza_carta(GtkWidget *img, int x, int y){
  gtk_fixed_move (GTK_FIXED(fixed), img, x, y);
}

void Imprime_mao_jogador(LISTA_CARTAS_PTR *Lista_Mao){
	LISTA_CARTAS_PTR atual = *Lista_Mao;
  int cont = 0;
  int x = 0, y = 0;
  GtkWidget *Img;
  while(Cartas_Mao(&x, &y, &Img, cont, atual)){
    cont++;
    atualiza_carta(Img, x, y);
    //g_print("N: %d, V: %d, x: %d, y: %d\n", Naipe, Valor, x, y);
    //gerar_mao(Naipe, Valor, x, y);
  }
}



void Imprime(LISTA_CARTAS_PTR Lista_Carta){
    while(Lista_Carta != NULL){
        g_print("%d | %d\n", Lista_Carta->numero, Lista_Carta->naipe);
        Lista_Carta = Lista_Carta->prox;
    }
    g_print("\n\n\n");
}

int main(int argc, char *argv[]) {
  gtk_init(&argc, &argv);
  init_mouse();

  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title(GTK_WINDOW(window), "Rummikub");
  gtk_window_set_default_size(GTK_WINDOW(window), 1000, 563);
  gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
  gtk_window_set_resizable(GTK_WINDOW(window), FALSE);


  fixed = gtk_fixed_new();
  gtk_container_add(GTK_CONTAINER(window), fixed);

  ///////////////////////////////////////////////////////////////////////////////

  bt_compra_carta = gtk_button_new_with_label("");
  gtk_fixed_put(GTK_FIXED(fixed), bt_compra_carta, 20,420);
  gtk_widget_set_size_request(bt_compra_carta, 88, 60);
  gtk_widget_set_name(bt_compra_carta,"bt_compra_carta");

  GtkStyleContext *context_bt1 = gtk_widget_get_style_context(bt_compra_carta);
  gtk_style_context_add_class(context_bt1,"bt_compra_carta");

  bt_finaliza_jog = gtk_button_new_with_label("");
  gtk_fixed_put(GTK_FIXED(fixed), bt_finaliza_jog, 20,485);
  gtk_widget_set_size_request(bt_finaliza_jog, 88, 65);
  gtk_widget_set_name(bt_finaliza_jog,"bt_finaliza_jog");

  GtkStyleContext *context_bt2 = gtk_widget_get_style_context(bt_finaliza_jog);
  gtk_style_context_add_class(context_bt2,"bt_finaliza_jog");

  ////////////////////////////////////////////////////////////////////////////

  //g_signal_connect (G_OBJECT(bt_compra_carta),"button_press_event",G_CALLBACK(bt_desabilita_compra), NULL);


  img_mesa = gtk_image_new_from_file("src/image/mesa.png"); 
  gtk_fixed_put(GTK_FIXED(fixed), img_mesa,120, 15);

  img_mao = gtk_image_new_from_file("src/image/mao.png"); 
  gtk_fixed_put(GTK_FIXED(fixed), img_mao,120, 420);

  img_user1 = gtk_image_new_from_file("src/image/user1_foco.png"); 
  gtk_fixed_put(GTK_FIXED(fixed), img_user1,20, 15);

  img_user2 = gtk_image_new_from_file("src/image/user2.png"); 
  gtk_fixed_put(GTK_FIXED(fixed), img_user2, 20, 95);

  img_user3 = gtk_image_new_from_file("src/image/user3.png"); 
  gtk_fixed_put(GTK_FIXED(fixed), img_user3, 20, 175);

  img_user4 = gtk_image_new_from_file("src/image/user4.png"); 
  gtk_fixed_put(GTK_FIXED(fixed), img_user4, 20, 255);

  img_user5 = gtk_image_new_from_file("src/image/user5.png"); 
  gtk_fixed_put(GTK_FIXED(fixed), img_user5, 20, 335);

  css_add();


  printf("1\n");

  Baralho = NULL;
  Jogadores = NULL;
  Cria_Baralho(&Baralho, fixed);	
  printf("2\n");

  Jogadores = (JOGADORES_PTR)malloc(sizeof(JOGADORES));
  Jogadores->Id = 0;
  Jogadores->prox = NULL;
  Jogadores->cartas = NULL;
  //Imprime(Baralho);

  printf("3\n");

  int cont = 0;
  for(cont = 0; cont < 14; cont++){
    Baralho_2_mao(&Baralho, &(Jogadores->cartas));
  }

  Imprime(Jogadores->cartas);
  Imprime_mao_jogador(&(Jogadores->cartas));

  constroi();
  gtk_main();

  //bt_img();
  return 0;
}