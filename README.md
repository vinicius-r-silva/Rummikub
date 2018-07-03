# Rummikub.c

Este projeto visa construir o jogo Rummikub na linguagem C para a disciplina de Introdução à Ciência da Computação da Universidade de São Paulo. As regras originais do jogo foram implementadas no programa. Além disso foi utilizada a biblioteca Gtk para a criação da interface gráfica.<br>
<b>Os usuários de Ubuntu 16 ou outras distribuições poderão enfrentar problemas na execução desse projeto, por causa da versão do GTK.</b><br>
O repositório contém os componentes utilizados tais como bibliotecas, arquivos .c e imagens utilizadas.
<hr>

<h3>Grupo:</h3>
P = 0: Vinícius Ribeiro da Silva - 10828141<br>
P = 1: Gabriel Santos Nicolau - 10684600<br>
P = 2: Mateus Fernandes Doimo - 10691971<br>
P = 3: Marcelo Magalhães Coelho - 10716633<br>
P = 4: Diego da Silva Parra - 10716550<br>
P = 5: Leonardo Prado Dias - 10684642<br>
P = 6: Renan Peres Martins - 10716612<br>

<h3>COMPILAÇÃO</h3>
Ubuntu 18 (Obs.: Deve-se conter o GCC instalado) : Acesse a pasta onde estão localizados os arquivos fonte pelo terminal >> execute os comandos.

<h4>Sistema operacional:</h4>
Ubuntu com versão <b>18</b><br>

<h4>Instalação do GCC (caso não venha pré instalado no Ubuntu):</h4>
$ sudo apt-get install gcc<br>

<h4>Instalação do GTK:</h4>
$ sudo apt-get install libgtk-3-dev<br>
<b>Verificar se a versão instalada do GTK é igual ou superior a 3.2</b><br>
<h4>Compilar programa:</h4>
$ make<br>

Ou caso não deseje utilizar o makefile é possível compilar utilizando os comandos abaixo:<br>
$ gcc -c -g -O0 -Wall -pthread -pipe src/main.c `pkg-config --cflags --libs gtk+-3.0` -o main.o<br>
$ gcc -c -g -O0 -Wall -pthread -pipe src/system.c `pkg-config --cflags --libs gtk+-3.0` -o system.o<br>
$ gcc -c -g -O0 -Wall -pthread -pipe src/eventos.c `pkg-config --cflags --libs gtk+-3.0` -o eventos.o<br>
$ gcc -c -g -O0 -Wall -pthread -pipe src/interface.c `pkg-config --cflags --libs gtk+-3.0` -o interface.o<br>
$ gcc -c -g -O0 -Wall -pthread -pipe src/init_game.c `pkg-config --cflags --libs gtk+-3.0` -o init_game.o<br>
$ gcc -o template_app  main.o system.o eventos.o interface.o init_game.o -pthread `pkg-config --cflags --libs gtk+-3.0` -export-dynamic<br>

<h3>EXECUÇÃO</h3>
Linux (Ubuntu 18): Navegue pelo terminal e acesse a pasta do arquivo compilado >> Execute o comando:
$ ./rummikub

