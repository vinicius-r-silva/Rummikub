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


void Cria_Baralho(LISTA_CARTAS_PTR *Baralho, GtkWidget *Painel, char Interacao);
void Baralho_2_mao(LISTA_CARTAS_PTR *baralho, LISTA_CARTAS_PTR *mao);
void Init_Baralho(LISTA_CARTAS_PTR *Baralho, GtkWidget *Painel);

JOGADORES_PTR Jogador_Atual(JOGADORES_PTR Lista_Jogadores);
void criar_jogadores (JOGADORES_PTR *Lista_Jogadores, int Qtd);
void excluir_jogadores (JOGADORES_PTR *Lista_Jogadores);
void cria_mao_jogadores(JOGADORES_PTR *Lista_Jogadores, LISTA_CARTAS_PTR *Baralho, LISTA_CARTAS_PTR *Backup_mao);


char Int_2_Naipe(int Naipe);
char int_2_hexa(int Numero);
LISTA_CARTAS_PTR Busca_Carta(LISTA_CARTAS_PTR *Baralho, int Naipe, int Numero, char interacao);
LISTA_CARTAS_PTR Busca_Carta_Mesa(LISTA_MESA_PTR *Mesas, LISTA_MESA_PTR *Monte, int Naipe, int Numero, char interacao);
 
void Pixel_2_LinCol(int *lin, int *col, int x, int y, int Inicio_x, int Inicio_y, int Tam_x, int Tam_y);
void Grid_2_Pixel(int linha, int coluna, int *x, int *y, int Inicio_x, int Inicio_y);
void LinCol_2_Monte(LISTA_MESA_PTR *Monte, LISTA_MESA_PTR *Mesa, int *pos, int linha, int coluna);

int Cartas_Mao(int *x, int *y, GtkWidget **Img, int pos, LISTA_CARTAS_PTR atual);
void mao_2_monte(LISTA_CARTAS_PTR *mao, LISTA_MESA_PTR *mesa, int Naipe, int Numero, int Pos, bool Nova_Lista);
void EventBox_2_Carta(GtkWidget *EventBox, int *Naipe, int *Numero, char *interacao);

void Organiza_Mesa(LISTA_MESA_PTR *Mesa);void Deleta_Lista(LISTA_CARTAS_PTR *Lista);

void Deleta_Mesa(LISTA_MESA_PTR *Mesa);
//1: SIM; 0: NAO; -1: ERRO
int fim_do_jogo(LISTA_CARTAS_PTR *baralho_compras, JOGADORES_PTR *lista_jogadores);

//retorna o id, se for -1 se o jogo ainda nao acabou, erro
int vencedor(JOGADORES_PTR *lista_jogadores, LISTA_CARTAS_PTR *lista_baralho);

int valida_jogada(JOGADORES_PTR Jogador, LISTA_CARTAS_PTR *Backup_Mao, LISTA_MESA_PTR *mesa_backup, LISTA_MESA_PTR *mesa_nova);

LISTA_MESA_PTR duplicar_mesa (LISTA_MESA_PTR *lista_mesa);

//verifica a validade da mesa (1-valido/0-invalido/-1 erro)
int verifica_mesa(LISTA_MESA_PTR *lista_mesa);

LISTA_CARTAS_PTR duplica_Cartas (LISTA_CARTAS_PTR *Origem);

void Inverte_Lista(LISTA_CARTAS_PTR *Lista);

void Carrega_Baralho(LISTA_CARTAS_PTR *Baralho, GtkWidget *Painel);
void Imprime_Baralho(LISTA_CARTAS_PTR Lista_Carta);

#endif //SYSTEM_H
