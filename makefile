# change application name here (executable output name)
TARGET=template_app

# compiler
CC=gcc
# debug
DEBUG=-g
# optimisation
OPT=-O0
# warnings
WARN=-Wall

PTHREAD=-pthread

CCFLAGS=$(DEBUG) $(OPT) $(WARN) $(PTHREAD) -pipe

GTKLIB=`pkg-config --cflags --libs gtk+-3.0`

# linker
LD=gcc
LDFLAGS=$(PTHREAD) $(GTKLIB) -export-dynamic

OBJS=  main.o system.o eventos.o interface.o

all: $(OBJS)
	$(LD) -o $(TARGET)  $(OBJS) $(LDFLAGS)
	
main.o: src/main.c
	$(CC) -c $(CCFLAGS) src/main.c $(GTKLIB) -o main.o
	
system.o: src/system.c
	$(CC) -c $(CCFLAGS) src/system.c $(GTKLIB) -o system.o
	
eventos.o: src/eventos.c
	$(CC) -c $(CCFLAGS) src/eventos.c $(GTKLIB) -o eventos.o
	
interface.o: src/interface.c
	$(CC) -c $(CCFLAGS) src/interface.c $(GTKLIB) -o interface.o

clean:
	rm -f *.o $(TARGET)


