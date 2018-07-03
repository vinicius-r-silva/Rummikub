# Rummikub

<h3>Grupo:</h3>
P = ?: Mateus Fernandes Doimo - 10691971
P = ?: Gabriel Santos Nicolau - 10684600
P = ?: Vinícius Ribeiro da Silva - 10828141
P = 4: Marcelo Magalhães Coelho - 10716633
P = 5: Diego da Silva Parra - 10716550
P = 6: Leonardo Prado Dias - 10684642
P = 7: Renan Peres Martins - 10716612


Este projeto visa construir o jogo Rummikub na linguagem C para a disciplina de Introdução à Ciência da Computação da Universidade de São Paulo. As regras originais do jogo foram implementadas no programa. Além disso foi utilizada a biblioteca Gtk para a criação da interface gráfica.
O repositório contém os componentes utilizados tais como bibliotecas, arquivos .c e imagens utilizadas.

<h3>COMPILAÇÃO</h3>
* Linux (Obs.: Deve-se conter o GCC instalado) : Acesse a pasta onde estão localizados os arquivos fonte pelo terminal >> execute os comandos:
$ make

Ou caso não deseje utilizar o makefile é possível compilar utilizando os comandos abaixo:
$ gcc -c -g -O0 -Wall -pthread -pipe src/main.c `pkg-config --cflags --libs gtk+-3.0` -o main.o
$ gcc -c -g -O0 -Wall -pthread -pipe src/system.c `pkg-config --cflags --libs gtk+-3.0` -o system.o
$ gcc -c -g -O0 -Wall -pthread -pipe src/eventos.c `pkg-config --cflags --libs gtk+-3.0` -o eventos.o
$ gcc -c -g -O0 -Wall -pthread -pipe src/interface.c `pkg-config --cflags --libs gtk+-3.0` -o interface.o
$ gcc -c -g -O0 -Wall -pthread -pipe src/init_game.c `pkg-config --cflags --libs gtk+-3.0` -o init_game.o
$ gcc -o template_app  main.o system.o eventos.o interface.o init_game.o -pthread `pkg-config --cflags --libs gtk+-3.0` -export-dynamic

<h3>EXECUÇÃO</h3>
* Linux: Navegue pelo terminal e acesse a pasta do arquivo compilado >> Execute o comando:
$ ./rummikub

