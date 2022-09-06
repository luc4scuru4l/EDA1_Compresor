all: io funciones btree huff

io: io.c io.h
	gcc -c io.c

funciones: funciones.c funciones.h
	gcc -c funciones.c

btree: btree.c btree.h
	gcc -c btree.c

huff: funciones.o btree.o io.o main.c
	gcc -Wall -g -o huff main.c funciones.o btree.o io.o

clean: 
	rm *.o