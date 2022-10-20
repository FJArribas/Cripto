#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void cifradoVigenere(char *string, char *key){

    char alf[27] = {"a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k",
    "l", "m", "n", "ñ", "o", "p", "q", "r", "s", "t", "u", "v",
    "w", "x", "y", "z"};

    char val = string[0];
    int i, size_k, size_s, kidx;

    size_k = strlen(key);
    size_s = strlen(string);

    printf("String1 %s String2 %s", string, key);


    /* Control errores */
    if (string == NULL)
        return;

    /* Vigenere algorithm */
    /*i = 0;
    while (val != '\0'){
        kidx = i % size;
        string[i] = string[i] + key[kidx];
        i++;
    }*/
}

int main (int argc, char *argv[]) {
    
    char *s = "el otro dia fui al parque";
    char *key = "criptografia";
    char a = 'a', b = 'b';

    //printf("String1 %s String2 %s", s, key);

    cifradoVigenere(s, key);

    printf("Mensaje cifrado %s", s);

    printf("Probando a sumar letras %c y %c = %c", a, b, a+b);
    
}