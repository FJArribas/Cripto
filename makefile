#Fundamentos de la criptografia

#FLAGS = -Wall -ansi -pedantic

all: clean Afin Hill #Vigenere

Afin: Afin.o
	gcc Afin.o -o Afin -lgmp -L.

Hill: Hill.o
	gcc Hill.o -o Hill 

#Vigenere: Vigenere.o
#	gcc Vigenere.o -o Vigenere

Afin.o: Afin.c 
	gcc -c Afin.c -lgmp -L.

Hill.o: Hill.c
	gcc -c Hill.c

#Vigenere.o: Vigenere.c
#	gcc -c Vigenere.c


clean:
	rm -rf *.o Afin Hill 
	
#Vigenere