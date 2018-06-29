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
#define TAM_Y_ESPACO 15

#define INICIO_X_MAO 122
#define INICIO_Y_MAO 425

#define SCREEN_SIZE_X 1000
#define SCREEN_SIZE_Y 563


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
    struct lista_cartas *cartas;
    struct jogadores *prox;
};

typedef struct lista_cartas LISTA_CARTAS;
typedef LISTA_CARTAS *LISTA_CARTAS_PTR;

typedef struct lista_mesa LISTA_MESA;
typedef LISTA_MESA *LISTA_MESA_PTR;

typedef struct jogadores JOGADORES;
typedef JOGADORES *JOGADORES_PTR;

#endif //DATA_H
