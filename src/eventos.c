#include "libs/eventos.h"

int prev_X = 0;
int prev_Y = 0;
extern GdkDevice *mouse;
extern LISTA_MESA_PTR Mesa;
extern JOGADORES_PTR Lista_Jogadores;

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


gboolean focus_out(GtkWidget *image, GdkEvent *event, gpointer user_data){
  int linha = 0, coluna = 0;
  int img_x = 0, img_y = 0;
  gtk_widget_translate_coordinates(image, gtk_widget_get_toplevel(image), 0, 0, &img_x, &img_y);
  
  Pixel_2_LinCol(&linha, &coluna, img_x, img_y);

  int pos = 0;
  LISTA_MESA_PTR Monte = NULL;
  LinCol_2_Monte(&Monte, &Mesa, &pos, linha, coluna);

  g_print("SAIU:\n");
  g_print("Img: %d, %d\n", img_x, img_y);
  g_print("lin: %d, col: %d\n", linha, coluna);
  if(Monte == NULL)
    g_print("Monte Vazio, pos: %d", pos);
  else
    g_print("Mx:  %d, My:  %d, Qtd_Carta: %d, pos; %d\n", Monte->x, Monte->y, Monte->N_Cartas, pos);

  imprime_mesa(&Mesa);

  int Naipe, Numero;
  int Nova_Lista = (pos == -1) ? 1 : 0;
  EventBox_2_Carta(image, &Naipe, &Numero);

  g_print("Naipe: %d (%c), Valor: %d (%c)\n", Naipe, Int_2_Naipe(Naipe), Numero, int_2_hexa(Numero));
  LISTA_CARTAS_PTR Mao_Jogador =  Mao_Jogador_Atual(&Lista_Jogadores);
  g_print("Mao Jogador: \n");
  Imprime_cartas(Mao_Jogador);
  g_print("fim mao jogador\n\n");

  mao_2_monte(&Mao_Jogador, &Monte, Naipe, Numero, pos, Nova_Lista);

  imprime_mesa(&Mesa);

  Organiza_Mesa(&Mesa);
  imprime_mesa(&Mesa);
  atualiza_cartas_mesa(&Mesa);


  return 1;
}
