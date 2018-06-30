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

#endif //INTERFACE_H