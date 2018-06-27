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
void Imprime_mao_jogador(LISTA_CARTAS_PTR *mao);

#endif //SYSTEM_H