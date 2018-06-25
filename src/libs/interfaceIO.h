#ifndef INTERFACE_IO

#define INTERFACE_IO

#include <stdbool.h>
#include <stdio.h>

//Le um inteiro do Stdin
//certifica que ser� lido somente numeros do stdin, nao sofre do 'bug' de ter lixo no buffer
//Retorna false quando nao foi poss�vel ler nenhum n�mero do buffer, e retorna true quando leu
//Certifica que deixa o buffer limpo quando termina de ler
int ReadInt(int *numero);

//Le um float do Stdin
//certifica que ser� lido somente numeros do stdin, nao sofre do 'bug' de ter lixo no buffer
//Retorna false quando nao foi poss�vel ler nenhum n�mero do buffer, e retorna true quando leu
//Certifica que deixa o buffer limpo quando termina de ler
int ReadDouble(double *numero);


int EntradaLimitadaInt(int min, int max);

double EntradaLimitadaDouble(double min, double max);

#endif //INTERFACE_IO