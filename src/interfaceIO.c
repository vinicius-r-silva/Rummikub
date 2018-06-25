#include "libs\interfaceIO.h"

#define TOLERANCIA 0.0001

//Le um inteiro do Stdin
//certifica que ser� lido somente numeros do stdin, nao sofre do 'bug' de ter lixo no buffer
//Retorna false quando nao foi poss�vel ler nenhum n�mero do buffer, e retorna true quando leu
//Certifica que deixa o buffer limpo quando termina de ler
int ReadInt(int *numero){
	bool negativo = false;

	//Limpa o buffer inicial at� encontrar um numero ou ate o buffer acabar
	char c = getchar();
	if (c == '\n' || c == '\0')
		c = getchar();

	while (c != '\n' && c != '\0' && (c < '0' || c > '9')){
		//Se o usuario digitou o sinal de menos, salva para no final multiplar por -1
		if (c == '-')
			negativo = true;

		c = getchar();
	}

	//Se o buffer de entrada acabou, entao nao tem nenhum numero para ler
	if (c == '\n' || c == '\0')
		return 0;

	//Caso o usuario digitou algum digito, le os digitos ate acabar
	*numero = c - '0';
	c = getchar();
	while (c != '\n' && c != '\0' && c >= '0' && c <= '9'){
		*numero = (*numero) * 10 + c - '0';
		c = getchar();
	}

	//Certifica que o buffer continua limpo depois da leitura
	while (c != '\n' && c != '\0')
		c = getchar();

	//Se o usuario digitou um '-' antes de digitar o numero, deixa o numero negativo
	if (negativo)
		*numero *= -1;

	//retorna sucesso
	return 1;
}

//Le um float do Stdin
//certifica que ser� lido somente numeros do stdin, nao sofre do 'bug' de ter lixo no buffer
//Retorna false quando nao foi poss�vel ler nenhum n�mero do buffer, e retorna true quando leu
//Certifica que deixa o buffer limpo quando termina de ler
int ReadDouble(double *numero){
	int i;
	bool negativo = false;

	//Limpa o buffer inicial at� encontrar um numero ou ate o buffer acabar
	char c = getchar();
	if (c == '\n' || c == '\0')
		c = getchar();

	while (c != '\n' && c != '\0' && (c < '0' || c > '9'))	{
		if (c == '-')
			negativo = true;

		c = getchar();
	}

	//Se o buffer de entrada acabou, entao nao tem nenhum numero para ler
	if (c == '\n' || c == '\0')
		return 0;

	//Caso o usuario digitou algum digito, le os digitos ate acabar
	*numero = (double)(c - '0');
	c = getchar();
	while (c != '\n' && c != '\0' && c >= '0' && c <= '9'){
		*numero = (*numero) * 10 + c - '0';
		c = getchar();
	}

	//Caso o usuario digitou um '.' ou uma ',', le os proximos digitos ate acabar
	if (c == '.' || c == ','){
		i = 10;
		c = getchar();
		while (c != '\n' && c != '\0' && c >= '0' && c <= '9')
		{
			*numero = (*numero) + ((double)(c - '0') / i);
			c = getchar();
			i *= 10;
		}
	}

	//Certifica que o buffer continua limpo depois da leitura
	while (c != '\n' && c != '\0')
		c = getchar();

	//Se o usuario digitou um '-' antes de digitar o numero, deixa o numero negativo
	if (negativo)
		*numero *= -1;

	//retorna sucesso
	return 1;
}


int EntradaLimitadaInt(int min, int max){
	int c;
	while (true && !false){
		while(!ReadInt(&c))
			printf("Entrada invalida. Digite novamente: ");
			
		if(c < min || c > max)
			printf("Valor invalido. Digite algo entre %d e %d. \nDigite novamente: ", min, max);
		else
			break;
	}

	return c;
}

double EntradaLimitadaDouble(double min, double max){
	double c;
	while (true && !false){
		while(!ReadDouble(&c))
			printf("Entrada invalida. Digite novamente: ");

		if(c < (min+TOLERANCIA) || c > (max-TOLERANCIA))
			printf("Valor invalido. Digite algo entre %.2lf e %.2lf. \nDigite novamente: ", min, max);
		else
			break;
	}

	return c;
}