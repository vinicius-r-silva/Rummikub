#include <gtk/gtk.h>
#include <string.h>  /* for css */

#include "libs/data.h"
#include "libs/system.h"
#include "libs/eventos.h"
#include "libs/init_game.h"

//TODO: testar se as cartas na distribuicao da mao ultrapassam a limitacao da area da mao
//TODO: Destruir as cartas quando excluido as cartas dos jogadores, da mesa, destruir as img dos jogadores... Necessario?

GdkDevice *mouse;
GtkWidget *window;
GtkWidget *fixed;

GtkWidget *bt_compra_carta;
GtkWidget *bt_finaliza_jog;

LISTAS_PTR Listas;

/*LISTA_MESA_PTR Mesa;
LISTA_MESA_PTR Mesa_Backup;
LISTA_CARTAS_PTR Mao_Backup;
JOGADORES_PTR Lista_Jogadores;
LISTA_CARTAS_PTR Baralho_Global;*/

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

  cria_jogo_imagens(); //carrega imagens do jogo Ex: Mesa, img dos jogadores, fundo da mão do jogador
  carrega_estilo_jogo(); //carrega dados para criar o estilo do jogo
  ///////////////////////////////////////////////////////////////////////////////
  
  Listas = (LISTAS_PTR)malloc(sizeof(Listas));

  Listas->Mesa = NULL;
  Listas->Baralho = NULL;
  Listas->Mesa_Backup = NULL;
  Listas->Mao_Backup = NULL;
  Listas->Lista_Jogadores = NULL;

  //Init_Baralho(&Baralho, fixed);
  Carrega_Baralho(&(Listas->Baralho), fixed);

  cria_botoes_jogo(&bt_compra_carta, &bt_finaliza_jog); //carrega botões no jogo
  tela_home(Listas->Baralho, &(Listas->Lista_Jogadores), &(Listas->Mao_Backup));
  constroi_janela_jogo(window); //carrega funções do GTK para criar a janela

  g_object_unref(icon);
  gtk_main(); //cria janela 

  excluir_jogadores(&(Listas->Lista_Jogadores));
  //Deleta Jodares
  //Deletea Mesa
  return 0;
}