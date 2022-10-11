#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void cifradoVigenere(char *string, char *key){

    char val = string[0];
    int i, size, kidx;

    size = strlen(key);

    printf("String1 %s String2 %s", string, key);


    /* Control errores */
    if (string == NULL)
        return;

    /* Vigenere algorithm */
    i = 0;
    while (val != '\0'){
        kidx = i % size;
        string[i] = string[i] + key[kidx];
        i++;
    }    
}

int main (int argc, char *argv[]) {
    
    char *s = "el otro dia fui al parque";
    char *key = "criptografia";

    //printf("String1 %s String2 %s", s, key);

    //cifradoVigenere(s, key);

    printf("Mensaje cifrado %s", s);
    
}