#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gmp.h>

#define MAX_LEN 1024

char *cifrar (mpz_t a, mpz_t b, mpz_t m, char *p, int len)
{
	int i, j;
	char *cifrado, *numerico, *ascii;
	mpz_t x, y, aux;

	mpz_init(aux);
	mpz_init(x);
	mpz_init(y);

	mpz_set_str(aux, "65", 10); // convertir a ascii

	cifrado = malloc(MAX_LEN * sizeof(char));
	ascii = malloc(MAX_LEN * sizeof(char));
	numerico = malloc(MAX_LEN * sizeof(char));

	for(i = 0; i < len; i++)
	{
		// toupper() para convertir de mayus a minus
		// Si no es una letra, no lo permutamos
		if (toupper(p[i]) < 65 || toupper(p[i]) > 90)
			cifrado[i] = p[i];
		else // letra -> permutamos
		{
			j = toupper(p[i]) - 65; // Asignamos un número a cada letra (A-Z = 0-25)
			sprintf (numerico, "%d", j);
			mpz_set_str (x, numerico, 10);

			// y = (a * x) + (b mod m)
			mpz_mul (y, a, x);		// y = a * x
			mpz_add (y, y, b);		// y = (a * x) + b
			mpz_fdiv_r (y, y, m);	// y = (((a * x) + b) mod m)

			mpz_add (y, y, aux);	// Asignamos la letra a cada numero (0-25 = A-Z)
			
			mpz_get_str (ascii, 10, y);
		
			cifrado[i] = atoi(ascii);

		}					
	}

	cifrado[i] = '\0'; // Fin de cadena

	free(ascii);
	free(numerico);

	mpz_clear(x);
	mpz_clear(y);
	mpz_clear(aux);

	return cifrado;
}



char * descifrar (mpz_t a, mpz_t b, mpz_t m, mpz_t inverso, char *q, int len)
{
	int i, j;
	char *descifrado, *numerico, *ascii;
	mpz_t x, y, aux, cero;

	mpz_init(x);
	mpz_init(y);
	mpz_init(aux);
	mpz_init(cero);

	mpz_set_str(aux, "65", 10);
	mpz_set_str(cero, "0", 10);

	descifrado = malloc (MAX_LEN * sizeof(char));
	ascii = malloc (MAX_LEN * sizeof(char));
	numerico = malloc (MAX_LEN * sizeof(char));

	for(i = 0; i < len; i++)
	{
		// toupper() para convertir de mayus a minus
		// Si no es una letra, no lo permutamos
		if (toupper(q[i]) < 65 || toupper(q[i]) > 90)
			descifrado[i] = q[i]; 
		else // letra -> permutamos
		{
			j = toupper(q[i]) - 65; // Asignamos un número a cada letra (A-Z = 0-25)
			sprintf(numerico, "%d", j);
			mpz_set_str(y, numerico, 10);

			// x = (y - b) * (a^-1 mod m), inverso = a^-1
			mpz_sub (y, y, b);			// y = y - b
			mpz_mul (y, y, inverso);	// y = (y - b) * (a^-1)
			mpz_fdiv_r (x, y, m);		// x = ((y - b) * (a^-1)) mod m)

			// si x < 0, sumamos m hasta hacerlo positivo
			if (mpz_cmp (x, cero) < 0)
				mpz_add (x, x, m);

			mpz_add (x, x, aux);	// Asignamos la letra a cada numero (0-25 = A-Z)

			mpz_get_str (ascii, 10, x);
			descifrado[i] = atoi(ascii);

		}					
	}

	descifrado[i] = '\0'; // Fin de cadena

	free(ascii);
	free(numerico);


	mpz_clear(x);
	mpz_clear(y);
	mpz_clear(aux);
	mpz_clear(cero);

	return descifrado;
}


void euclides (mpz_t a, mpz_t b, mpz_t q)
{
    mpz_t r0, r1;

    mpz_init(r0);
    mpz_init(r1);

    mpz_set(r0, a);
    mpz_set(r1, b);

    /* Control de errores */
    if(mpz_cmp_ui (r0, 0) != 1 || mpz_cmp_ui (r1, 0) != 1  || mpz_cmp (r0, r1) != 1){
        mpz_set_str(q, "-1", 10);
        return;
    }

    mpz_mod(q, r0, r1);

    /* Euclides algorithm */
    while (mpz_cmp_ui (q, 0) == 1)
    {
        mpz_mod (q, r0, r1);     // q = r0 % r1
        mpz_set (r0, r1);       // r0 = r1
        mpz_set (r1, q);        // r1 = q

        //gmp_printf("%Zd ", r1);
    }

    /* We store the solution of the algorithm */
    mpz_set(q, r0);

    mpz_clear(r0);
    mpz_clear(r1);
}


void euclides_extended (mpz_t a, mpz_t b, mpz_t u0, mpz_t v0)
{
    mpz_t u1, v1, u2, v2, aux, r, r0, r1, q;

    /* Initializing values */
    mpz_init (u1);
    mpz_init (v1);
    mpz_init (u2);
    mpz_init (v2);
    mpz_init (aux);
    mpz_init (r);
    mpz_init (r0);
    mpz_init (r1);
    mpz_init (q);

    mpz_set_str (u0, "1", 10);
    mpz_set_str (v0, "0", 10);
    mpz_set_str (u1, "0", 10);
    mpz_set_str (v1, "1", 10);

    mpz_set(r0, a);
    mpz_set(r1, b);

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

        mpz_set (u0, u1);  
        mpz_set (v0, v1);
        mpz_set (u1, u2);
        mpz_set (v1, v2);
               
    }
        
    //gmp_printf("Valores de u, v y r %Zd %Zd %Zd", u0, v0, r);

    /* Freeing values */
    mpz_clear (u1);
    mpz_clear (u2);
    mpz_clear (v1);
    mpz_clear (v2);
    mpz_clear (aux);
    mpz_clear (r);
    mpz_clear (r0);
    mpz_clear (r1);
    mpz_clear (q);
}


int main (int argc, char *argv[])
{
    int tam, i = 1;
    unsigned long int h = 100;
    char *str_a, *str_b;
    FILE *entrada, *salida;
    mpz_t a, b, q, u, v, x, y, m;

    /* Declaration of variables */
    mpz_init (a);
    mpz_init (b);
    mpz_init (q);
    mpz_init (x); // TODO quitar frees e init de euclides, meterlo en main
    mpz_init (y);
    mpz_init (u);
    mpz_init (v);
    mpz_init (m);

	mpz_set_str(m, "26", 10); // Inglés, 27 es


    mpz_set_str (a, "721", 10);
    mpz_set_str (b, "488", 10);

    if(argc <= 8 || argc > 12)
    {
        printf("\nPrograma AFÍN ejecutado. Uso del programa:\n"
               "afin {-C | -D} {-m |Zm|} {-a N×} {-b N+} [-i filein] [-o fileout]\n"
               "-C: El programa cifra\n"
               "-D: El programa descifra\n"
               "-m: Tamaño del espacio de texto cifrado\n"
               "-a: Coeficiente multiplicativo de la función afín\n"
               "-b: Término constante de la función afín\n"
               "-i: Fichero de entrada\n"
               "-o: Fichero de salida\n");
    }
    else
    {
        if (strcmp(argv[1], "-C") == 0 || strcmp(argv[1], "-c") == 0) // Cifra
        {
            if ((argc > 8) && ((strcmp(argv[8], "-i") == 0 || strcmp(argv[8], "-I") == 0))) // Entrada por fichero
            {
                entrada = fopen (argv[9], "r");
                if (entrada == NULL)
                {
                    printf ("Error al abrir el fichero de entrada\n");
                    return -1;
                }
                
                fseek (entrada, 0, SEEK_END);
                tam = ftell (entrada);
                rewind (entrada);
                str_a = malloc ((tam + 1) * sizeof (char));
                fread (str_a, 1, tam, entrada);
                fclose (entrada);
            }
            else    // Entrada por teclado
            {
                printf ("\nIntroducir entrada: ");
                scanf ("%m[^\n]%*c", &str_a);
                tam = strlen (str_a);
            }
            
            // TODO: CIFRAR
            c = cifrar (a, b, 26, str_a, tam)
            
            // Scanf -> Fichero
            if ((argc < 11 ) && ((strcmp(argv[8], "-o") == 0 || strcmp(argv[8], "-O") == 0)))
            {
                salida = fopen (argv[9], "w");
                // TODO fputs (c, salida);
                fclose (salida);
            }
            // Fichero -> Printf
            else if ((argc < 11 ) && ((strcmp(argv[8], "-o") != 0 && strcmp(argv[8], "-O") != 0)))
            {
                printf ("Mensaje cifrado: %s", c);
            }
            // Scanf -> Printf
            else if (argc == 8)
            {
                printf ("Mensaje cifrado: %s", c);
            }
            // Fichero -> Fichero
            else
            {
                salida = fopen (argv[11], "w");
                // TODO fputs (c, salida);
                fclose (salida);
            }
            printf("\n");
            // free (c);
            free (str_a);
        }
        else if (strcmp(argv[1], "-D") == 0 || strcmp(argv[1], "-d") == 0) // Descifra
        {
            if ((argc > 8) && ((strcmp(argv[8], "-i") == 0 || strcmp(argv[8], "-I") == 0))) // Entrada por fichero
			{
				entrada = fopen (argv[9], "r");
				if (entrada == NULL)
				{
					printf("Error al abrir el fichero de entrada\n");
					return -1;					
				}

                fseek (entrada, 0, SEEK_END);
                tam = ftell (entrada);
                rewind (entrada);
                str_a = malloc ((tam + 1) * sizeof (char));
                fread (str_a, 1, tam, entrada);
                fclose (entrada);
			}
			else    // Entrada por teclado
			{
				printf ("\nIntroducir entrada: ");
                scanf ("%m[^\n]%*c", &str_a);
                tam = strlen (str_a);
			}

			/*Obtenemos el inverso multiplicativo*/
			// TODO inverso (a, msg, y)
			d = descifrar (a, b, msg, y, str_a, tam)
            // Scanf -> Fichero
            if ((argc < 11 ) && ((strcmp(argv[8], "-o") == 0 || strcmp(argv[8], "-O") == 0)))
            {
                salida = fopen (argv[9], "w");
                // TODO fputs (d, salida);
                fclose (salida);
            }
            // Fichero -> Printf
            else if ((argc < 11 ) && ((strcmp(argv[8], "-o") != 0 && strcmp(argv[8], "-O") != 0)))
            {
                printf ("Mensaje descifrado: %s", d);
            }
            // Scanf -> Printf
            else if (argc == 8)
            {
                printf ("Mensaje descifrado: %s", d);
            }
            // Fichero -> Fichero
            else
            {
                salida = fopen (argv[11], "w");
                // TODO fputs (d, salida);
                fclose (salida);
            }
            printf("\n");
            // free (c);
            free (str_a);

        }
        else
        {
            printf("\nError en los parámetros\n");
        }
    }

        //if (strcmp(argv[3], "-m") == 0)
            //tam = atoi(argv[4]); // Tamaño del espacio del texto

        //if ((strcmp(argv[3], "-a") == 0))

	// TODO: clear and free
	return 0;

} 
