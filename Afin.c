#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
/* #include "gmp.h" */

int main (int argc, char *argv[])
{
    int cifra, tam
    FILE *entrada, *salida;

    if(argc < 1 || argc > 12) // TODO: Comprobar que este es el número máximo de args
        printf("\nPrograma AFÍN ejecutado. Uso del programa:"
               "afin {-C | -D} {-m |Zm|} {-a N×} {-b N+} [-i filein] [-o fileout]"
               "-C: El programa cifra"
               "-D: El programa descifra"
               "-m: Tamaño del espacio de texto cifrado"
               "-a: Coeficiente multiplicativo de la función afín"
               "-b: Término constante de la función afín"
               "-i: Fichero de entrada"
               "-o: Fichero de salida"\n);

    if(argc >= 2)
    {
        if (strcmp(argv[2], "-C") == 0)
            cifra = 1   // Cifra
        else
            cifra = 0   // Descifra

        if (strcmp(argv[3], "-m") == 0)
            tam = atoi(argv[4]) // Tamaño del espacio del texto

        if ((strcmp(argv[3], "-a") == 0))

    }

    // Ejemplo de uso GMP

    mpz_t a,b,m;
    int modo;

    mpz_init (a);
    mpz_init (b);
    mpz_init (m);

    mpz_set_str (a,"123452345234523452352352345112341234213",10);
    mpz_set_str (b,"234562344341234123421341234441234213421",10);

    mpz_add    (m,a,b);

    gmp_printf ("El resultado de la suma es %Zd\n", m);

    mpz_clear (a);
    mpz_clear (b);
    mpz_clear (m);

    return(0);
}
