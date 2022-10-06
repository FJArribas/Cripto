#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gmp.h>
/* #include "gmp.h" */

int main (int argc, char *argv[])
{
    int cifra, tam, i = 1;
    char* str_a, str_b;
    FILE *entrada, *salida;
    mpz_t a, b, r0, r1, q, u0, v0, u1, v1, u2, v2, aux, r;

    /*

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
            cifra = 1;  // Cifra
        else
            cifra = 0;  // Descifra

        if (strcmp(argv[3], "-m") == 0)
            tam = atoi(argv[4]); // Tamaño del espacio del texto

        //if ((strcmp(argv[3], "-a") == 0))

    }

    */

    mpz_init (a);
    mpz_init (b);
    mpz_init (r);
    mpz_init (r0);
    mpz_init (r1);
    // mpz_init (r2);
    mpz_init (q);

    mpz_init (u0); //Esto es ui-2
    mpz_init (v0);
    mpz_init (u1); //Esto es ui-1
    mpz_init (v1);
    mpz_init (u2);
    mpz_init (v2);
    mpz_init (aux);

    mpz_set_str (a, "721", 10);
    mpz_set_str (b, "488", 10);

    // mpz_set_str (a, str_a, 10);
    // mpz_set_str (b, str_b, 10); 


    /* Control de errores*/
    if(mpz_cmp_ui (a, 0) == 1 && mpz_cmp_ui (b, 0) == 1  && mpz_cmp (a, b) == 1) // TODO Comparar que las funciones sean mpz
    {
        mpz_set_str (u0, "1", 10);
        mpz_set_str (v0, "0", 10);
        mpz_set(r0, a);
        mpz_set(r1, b);
        mpz_mod(q, r0, r1);
    

        mpz_set_str (u0, "1", 10);
        mpz_set_str (v0, "0", 10);
        mpz_set_str (u1, "0", 10);
        mpz_set_str (v1, "1", 10);

        /* Algoritmo extendido */
        while (mpz_cmp_ui (r1, 0) == 1)
        {
               
            mpz_tdiv_q(q, r0, r1);  // q = a//b (div truncada)
            
            mpz_mul(aux, q, r1);    // aux = q * r1  
            mpz_sub(r, r0, aux);    // r = r0 - aux

            mpz_mul(aux, q, u1);    // aux = q * u1
            mpz_sub(u2, u0, aux);   // u2 = u0 - aux

            mpz_mul(aux, q, v1);    // aux = q * v1
            mpz_sub(v2, v0, aux);   // v2 = v0 - aux

            mpz_set(r0, r1);        // r0 = r1
            mpz_set(r1, r);         // r1 = r

            /* Update for next iteration */
            mpz_set (u0, u1);  
            mpz_set (v0, v1);
            mpz_set (u1, u2);
            mpz_set (v1, v2);
               
        }
        
        gmp_printf("Valores de u, v y r %Zd %Zd %Zd", u0, v0, r);

        /* Euclides */
        while (mpz_cmp_ui (q, 0) == 1)
        {
            mpz_mod (q, r0, r1);     // q = r0 % r1
            mpz_set (r0, r1);       // r0 = r1
            mpz_set (r1, q);        // r1 = q

            gmp_printf("%Zd ", r1);
        }

    }
    else
        return -1;


    mpz_clear (a);
    mpz_clear (b);
    mpz_clear (q);
    mpz_clear (r0);
    mpz_clear (r1);



    return (0);
}