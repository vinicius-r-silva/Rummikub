#ifndef SYSTEM_H
#define SYSTEM_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <gtk/gtk.h>

#include "data.h"
#include "interface.h"


void Cria_Baralho(LISTA_CARTAS_PTR *Baralho, GtkWidget *Painel, int Interacao);
void Baralho_2_mao(LISTA_CARTAS_PTR *baralho, LISTA_CARTAS_PTR *mao);
void Init_Baralho(LISTA_CARTAS_PTR *Baralho, GtkWidget *Painel);

JOGADORES_PTR Jogador_Atual(JOGADORES_PTR *Lista_Jogadores);
void criar_jogadores (JOGADORES_PTR *Lista_Jogadores, int Qtd);
void excluir_jogadores (JOGADORES_PTR *Lista_Jogadores);
void cria_mao_jogadores(JOGADORES_PTR *Lista_Jogadores, LISTA_CARTAS_PTR Baralho);

char Int_2_Naipe(int Naipe);
char int_2_hexa(int Numero);

void Pixel_2_LinCol(int *lin, int *col, int x, int y);
void Grid_2_Pixel(int linha, int coluna, int *x, int *y, int Inicio_x, int Inicio_y);
void LinCol_2_Monte(LISTA_MESA_PTR *Monte, LISTA_MESA_PTR *Mesa, int *pos, int linha, int coluna);

int Cartas_Mao(int *x, int *y, GtkWidget **Img, int pos, LISTA_CARTAS_PTR atual);
void mao_2_monte(LISTA_CARTAS_PTR *mao, LISTA_MESA_PTR *mesa, int Naipe, int Numero, int Pos, bool Nova_Lista);
void EventBox_2_Carta(GtkWidget *EventBox, int *Naipe, int *Numero);

void Organiza_Mesa(LISTA_MESA_PTR *Mesa);

#endif //SYSTEM_H
