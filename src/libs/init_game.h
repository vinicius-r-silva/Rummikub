#ifndef INIT_GAME_H
#define INIT_GAME_H

#include <gtk/gtk.h>
#include "data.h"
#include "interface.h"
#include "eventos.h"

void carrega_estilo_jogo();

//Cria o icone na janela
GdkPixbuf *create_pixbuf(const gchar * filename);

void init_mouse();

void tela_home(LISTA_CARTAS_PTR Baralho, JOGADORES_PTR *Lista_Jogadores);

void comeca_jogo(GtkWidget *bt, gint response_id, LISTA_BT_JOG_PTR data);

void ativa_n_jog(GtkWidget *bt, gint response_id, LISTA_BT_JOG_PTR data);

//Constroi janela - funções do GTK
void constroi_janela_jogo(GtkWidget *window);

//Adiciona botões no jogo e seus eventos
void cria_botoes_jogo(GtkWidget *bt_compra_carta, GtkWidget *bt_finaliza_jog);

//Função para criar imagens do jogo
void cria_jogo_imagens();

#endif //INIT_GAME_H