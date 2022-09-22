#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gmp.h>
/* #include "gmp.h" */

int main (int argc, char *argv[])
{
    int cifra, tam;
    char* str_a, str_b;
    FILE *entrada, *salida;
    mpz_t a, b, d, r0, r1, r2, q;

    if(argc <= 1 || argc > 12) // TODO: Comprobar que este es el número máximo de args
        printf("\nPrograma AFÍN ejecutado. Uso del programa:"
               "afin {-C | -D} {-m |Zm|} {-a N×} {-b N+} [-i filein] [-o fileout]"
               "-C: El programa cifra"
               "-D: El programa descifra"
               "-m: Tamaño del espacio de texto cifrado"
               "-a: Coeficiente multiplicativo de la función afín"
               "-b: Término constante de la función afín"
               "-i: Fichero de entrada\n"
               "-o: Fichero de salida\n");

    if(argc >= 2)
    {
        if (strcmp(argv[2], "-C") == 0)
            cifra = 1;   // Cifra
        else
            cifra = 0;  // Descifra

        if (strcmp(argv[3], "-m") == 0)
            tam = atoi(argv[4]); // Tamaño del espacio del texto

        //if ((strcmp(argv[3], "-a") == 0))

    }

    mpz_init(a);
    mpz_init(b);
    mpz_init(d);
    mpz_init(r0);
    mpz_init(r1);
    mpz_init(r2);
    mpz_init(q);



    mpz_set_str(a, str_a, 10), 
    mpz_set_str(b, str_b, 10), 

        /* Control de errores*/

    if(a == 0 || b == 0  ||)
    while (r != 0){

    }

    return(0);
}
