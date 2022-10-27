#Fundamentos de la criptografia

#FLAGS = -Wall -ansi -pedantic

all: clean Afin AfinExtendido Hill

Afin: Afin.o
	gcc Afin.o -o Afin -lgmp -L.

AfinExtendido: AfinExtendido.o
	gcc AfinExtendido.o -o AfinExtendido -lgmp -L.

Hill: Hill.o
	gcc Hill.o -o Hill 

Afin.o: Afin.c 
	gcc -c Afin.c -lgmp -L.

AfinExtendido.o: AfinExtendido.c 
	gcc -c AfinExtendido.c -lgmp -L.

Hill.o: Hill.c
	gcc -c Hill.c

clean:
	rm -rf *.o Afin Hill Vigenere
