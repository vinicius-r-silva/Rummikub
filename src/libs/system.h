#ifndef SYSTEM_H
#define SYSTEM_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

#include "data.h"

void Cria_Baralho(LISTA_CARTAS_PTR *Baralho);
void Baralho_2_mao(LISTA_CARTAS_PTR *baralho, LISTA_CARTAS_PTR *mao);
int Cartas_Mao(int *x, int *y, int *Naipe, int *Valor, int pos, LISTA_CARTAS_PTR atual);
char Int_2_Naipe(int Naipe);
char int_2_hexa(int Numero);

#endif //SYSTEM_H
