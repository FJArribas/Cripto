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
            // c = cifrar (a, b, msg, str_a, len)
            
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
			// TODO d = descifrar (a, b, msg, y, str_a, len)
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



char * descifrar (mpz_t a, mpz_t b, mpz_t m, mpz_t inverso, char *q, len)
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