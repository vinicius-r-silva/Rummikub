#ifndef DATA_H
#define DATA_H

#define NAIPE_1 '!' 
#define NAIPE_2 '@'
#define NAIPE_3 '#'
#define NAIPE_4 '$'
#define CORINGA '*'

#define LOCAL_FILE_BARALHO "rummikub/baralho.txt"

#define N_MAX_COLUNAS 12


struct lista_cartas {
    int naipe; //se for coringa = -1
    int numero;
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
