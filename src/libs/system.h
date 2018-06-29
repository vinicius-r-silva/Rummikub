#ifndef SYSTEM_H
#define SYSTEM_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <gtk/gtk.h>

#include "data.h"
#include "eventos.h"


void Cria_Baralho(LISTA_CARTAS_PTR *Baralho, GtkWidget *Painel);
void Baralho_2_mao(LISTA_CARTAS_PTR *baralho, LISTA_CARTAS_PTR *mao);
int Cartas_Mao(int *x, int *y, GtkWidget **Img, int pos, LISTA_CARTAS_PTR atual);
char Int_2_Naipe(int Naipe);
char int_2_hexa(int Numero);

#endif //SYSTEM_H
