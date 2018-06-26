#ifndef SYSTEM_H
#define SYSTEM_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

#include "data.h"

void Organiza_Mesa(LISTA_MESA_PTR *Mesa);
int verifica_mesa(LISTA_MESA_PTR *lista_mesa);
void Baralho_2_mao(LISTA_CARTAS_PTR *baralho, LISTA_CARTAS_PTR *mao);
void mao_2_monte(LISTA_CARTAS_PTR *mao, LISTA_MESA_PTR *mesa, int Naipe, int Numero, int Pos, bool Nova_Lista);

void Deleta_Lista(LISTA_CARTAS_PTR *Lista);
void Cria_Carta(LISTA_CARTAS_PTR *Baralho, int Naipe, int Numero);
LISTA_CARTAS_PTR Busca_Carta(LISTA_CARTAS_PTR *Baralho, int Naipe, int Numero);
void TrocaCarta(LISTA_CARTAS_PTR *Baralho, int Naipe_1, int Naipe_2, int Num_1, int Num_2);
void Cria_Baralho(LISTA_CARTAS_PTR *Baralho);
void Carrega_Baralho(LISTA_CARTAS_PTR *Baralho);
void Organiza_Mesa(LISTA_MESA_PTR *Mesa);
void Inverte_Lista(LISTA_CARTAS_PTR *Lista);

int Naipe_2_int(char Naipe);
char Int_2_Naipe(int Naipe);
char int_2_hexa(int Numero);
int Hexa_2_int(char Numero);

void Imprime_Mesa(LISTA_MESA_PTR *Mesa);
void Imprime(LISTA_CARTAS_PTR Baralho);
void Imprime_Ordenado(LISTA_CARTAS_PTR Baralho);

#endif //SYSTEM_H