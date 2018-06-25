#ifndef SYSTEM_H
#define SYSTEM_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

#include "data.h"

void Deleta_Lista(LISTA_CARTAS_PTR *Lista);
void Cria_Carta(LISTA_CARTAS_PTR *Baralho, int Naipe, int Numero);
LISTA_CARTAS_PTR Busca_Carta(LISTA_CARTAS_PTR *Baralho, int Naipe, int Numero);
void TrocaCarta(LISTA_CARTAS_PTR *Baralho, int Naipe_1, int Naipe_2, int Num_1, int Num_2);
void Cria_Baralho(LISTA_CARTAS_PTR *Baralho);
void Imprime(LISTA_CARTAS_PTR Baralho);
void Imprime_Ordenado(LISTA_CARTAS_PTR Baralho);

#endif //SYSTEM_H