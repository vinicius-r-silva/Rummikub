#ifndef DATA_H
#define DATA_H

#define NAIPE_A 1


struct lista_cartas {
    int naipe; //se for coringa = -1
    int numero;
    struct lista_cartas *prox;
};

struct lista_mesa {
    struct lista_cartas *cartas;
    struct lista_mesa *prox;
};

typedef struct lista_cartas LISTA_CARTAS;
typedef LISTA_CARTAS *LISTA_CARTAS_PTR;

typedef struct lista_mesa LISTA_MESA;
typedef LISTA_MESA *LISTA_MESA_PTR;

#endif //DATA_H
