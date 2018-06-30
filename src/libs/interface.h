#ifndef INTERFACE_H
#define INTERFACE_H

#include <gtk/gtk.h>
#include "data.h"
#include "system.h"
#include "eventos.h"

void move_imagem(GtkWidget *image,int descola_X, int descola_Y);
GtkWidget* Insere_Carta_Interface(int Naipe, int Valor, GtkWidget *Painel, char Interacao);
void Insere_Img_Jogador(JOGADORES_PTR Jogador);
void Coloca_Borda_Jogador(JOGADORES_PTR Jogador);
void Tira_Borda_Jogador(JOGADORES_PTR Jogador);
void Imprime_mao_jogador(LISTA_CARTAS_PTR *Mao, int linha, int coluna, int Pixel_X_Inicial, int Pixel_Y_Inicial);
void atualiza_cartas_mesa(LISTA_MESA_PTR *Lista_Mesas);

#endif //INTERFACE_H