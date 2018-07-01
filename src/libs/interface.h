#ifndef INTERFACE_H
#define INTERFACE_H

#include <gtk/gtk.h>
#include "data.h"
#include "system.h"
#include "eventos.h"

void atualiza_janela();
void move_imagem(GtkWidget *image,int descola_X, int descola_Y);
GtkWidget* Insere_Carta_Interface(int Naipe, int Valor, GtkWidget *Painel, char Interacao);
void Insere_Img_Jogador(JOGADORES_PTR Jogador);
void Coloca_Borda_Jogador(JOGADORES_PTR Jogador);
void Tira_Borda_Jogador(JOGADORES_PTR Jogador);
void Imprime_mao_jogador(LISTA_CARTAS_PTR *Mao, int linha, int coluna, int Pixel_X_Inicial, int Pixel_Y_Inicial);
void atualiza_cartas_mesa(LISTA_MESA_PTR *Lista_Mesas);

void fecha_tela(GtkDialog *dialog, gint response_id, gpointer callback_params);

//Cria tela de bem vindo para os usuarios
void tela_bem_vindo();

//Cria tela de erro na mesa
void tela_erro_jogada();

//Cria tela ganhador do jogo
void tela_ganhador(int jogador);

//Desabilita botão de comprar carta
void bt_desabilita_compra(GtkWidget *widget, gpointer data);

//Altera botão nova jogada para iniciar outro jogador
void troca_bt_jogador();

void Oculta_mao_Jogador(JOGADORES_PTR Jogador);

void tela_tipo_entrada();

void tela_erro_arquivo();

void escolha_tipo_entrada(GtkWidget *bt, gint response_id, gpointer data);

void tela_proximo_jogador(int jogador);

void proximo_jogador(GtkWidget *bt, gint response_id, gpointer data);
#endif //INTERFACE_H