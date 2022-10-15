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
            // c = cifrar (a, b, msg, str_a)
            
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
            // TODO Lo mismo basicamente
        }
        else
        {
            printf("\nError en los parámetros\n");
        }
    }

        if (strcmp(argv[3], "-m") == 0)
            tam = atoi(argv[4]); // Tamaño del espacio del texto

        //if ((strcmp(argv[3], "-a") == 0))

    }