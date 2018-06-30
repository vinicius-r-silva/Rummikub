#ifndef DATA_H
#define DATA_H

#include <gtk/gtk.h>

#define NAIPE_1 '!' 
#define NAIPE_2 '@'
#define NAIPE_3 '#'
#define NAIPE_4 '$'
#define CORINGA '*'

#define LOCAL_FILE_BARALHO "rummikub/baralho.txt"

#define N_MAX_COLUNAS 28

#define TAM_X_CARTA 28
#define TAM_Y_CARTA 50

#define TAM_X_ESPACO 3
#define TAM_Y_ESPACO 14

#define INICIO_X_MAO 129
#define INICIO_Y_MAO 425

#define SCREEN_SIZE_X 1060
#define SCREEN_SIZE_Y 563

#define FIM_Y_MESA    385
#define INICIO_Y_MESA 30

#define FIM_X_MESA    1020
#define INICIO_X_MESA 129

#define INICIO_X_JOGADORES 20
#define INICIO_Y_JOGADORES 15
#define ESPACO_Y_JOGADORES 80

struct lista_cartas {
    int naipe; //se for coringa = -1
    int numero;
    GtkWidget *img;
    struct lista_cartas *prox;
};

struct lista_mesa {
    int x;
    int y;
    int N_Cartas;
    struct lista_cartas *cartas;
    struct lista_mesa *prox;
};

struct jogadores {
    int Id;
    char Sua_Vez;
    GtkWidget *img;
    char Jogada_Inicial;
    struct lista_cartas *cartas;
    struct jogadores *prox;
};

struct bt_jog{
  GtkWidget *n_2;
  GtkWidget *n_3;
  GtkWidget *n_4;
  GtkWidget *n_5;
  GtkWidget *obj_home;
  int bt_ativo;
  struct lista_cartas *Baralho;
};

typedef struct bt_jog LISTA_BT_JOG;
typedef LISTA_BT_JOG *LISTA_BT_JOG_PTR;

typedef struct lista_cartas LISTA_CARTAS;
typedef LISTA_CARTAS *LISTA_CARTAS_PTR;

typedef struct lista_mesa LISTA_MESA;
typedef LISTA_MESA *LISTA_MESA_PTR;

typedef struct jogadores JOGADORES;
typedef JOGADORES *JOGADORES_PTR;

#endif //DATA_H
