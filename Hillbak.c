#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_matrix(int **matrix, int size){

    int i, j;

    for(i=0;i<size;i++){
        for(j=0;j<size;j++){
            printf(" %d ", matrix[i][j]);
        }
        printf("\n");
    }
}


void print_matrixd(double **matrix, int size){

    int i, j;

    for(i=0;i<size;i++){
        for(j=0;j<size;j++){
            printf(" %lf ", matrix[i][j]);
        }
        printf("\n");
    }
}


void matrix_multiply(int **matrix, int size, double num, double **inv){

    int i, j;

    for(i=0;i<size;i++){
        for(j=0;j<size;j++){
            inv[i][j] = matrix[i][j] * num;
            //printf("\nValor modificado de pos [%d][%d] = %lf", i, j, inv[i][j]);
        }
    }
}


/* Funcion que obtiene cofactores  el valor de los cofactores */
void cofactor(int** array, int size, int row, int col, int **cof){

    int met[size][size];
    int i, j, k = 0, l = 0;

    // Obtenemos con loops cofactors y los devuelve
    for (i = 0;i < size;i++){
        for (j = 0;j < size;j++){
            if (i != row && j != col){
                // l++;

                cof[k][l] = array[i][j];

                l+=1;
                if(l == size -1){ // Si llegas fin columnas reseteas y empiezas nueva row
                    k++;
                    l=0;
                }
            }
        }
    }

    //printf("\nThis is the cofactor created\n");
    //print_matrix(cof, size);
}


int determinant(int **matrix, int size){

    int det = 0, cof, i, j, m, aux, aux2;
    
    if(size == 1){
        det = matrix[0][0];
        return det;
    }
    else if (size == 2){
        det = matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
        return det;
    }
    else {

        /* Storing memory for the cofactor */
        m = size-1;
        int **cof = malloc(m * sizeof(int *));
        for(i = 0; i < m; i++)
            cof[i] = malloc(m * sizeof(int));

        printf("Paso por else\n");

        /* Starting loop with the cofactors */
        j = 0;
        for(i = 0; i < size; i++){
            cofactor(matrix, size, j, i, cof); // 0 = row, i = column
            
            printf("\nCofactor que obtenemos:\n");
            print_matrix(cof, m);

            aux = determinant(cof, m);
            if(i%2==1){
                aux *= -1;
            }

            det += matrix[j][i] * aux;
            
            //printf("Determinante = %d\n", det);
        }

        /* Freeing values of cofactor*/
        for(i = 0; i < m; i++)
            free((void *)cof[i]);
        free((void *)cof);

        return det;
    }

    return det;
}


void adjoint(int **matrix, int size, int **adj){

    int m, i, j, cof, aux;

    if(size == 1){
        adj[0][0] = matrix[0][0];
        return;
    }
    else if (size == 2){

        /* Los valores que se mantienen positivos */
        adj[0][0] = matrix[1][1];
        adj[1][1] = matrix[0][0];

        /* Los valores que cambian de signo */
        adj[0][1] = -matrix[1][0];
        adj[1][0] = -matrix[0][1];

        return;
    }
    else {

        /* Storing memory for the cofactor */
        m = size-1;
        int **cof = malloc(m * sizeof(int *));
        for(i = 0; i < m; i++)
            cof[i] = malloc(m * sizeof(int));

        printf("Paso por else\n");

        /* Starting loop with the cofactors */
        for(i = 0; i < size; i++){

            for(j = 0; j < size; j++){

                /* Obtenemos todos los cofactores de la matriz */
                cofactor(matrix, size, j, i, cof); // j=row i=col
                
                printf("\nCofactor que obtenemos:\n");
                print_matrix(cof, m);

                /* Obtenemos determinante de los cofactores */
                aux = determinant(cof, m);

                /* Cambiamos signo en suma de indices impar */
                if((i+j)%2==1){
                    aux *= -1;
                }

                /* Insertamos valores en matriz adjunta */
                adj[j][i] = aux;
            }
        }

        /* Freeing values of cofactor*/
        for(i = 0; i < m; i++)
            free((void *)cof[i]);
        free((void *)cof);

        return;
    }
}

void cifrar()
{
    
}

void descifrar()
{
    
}

int main (int argc, char *argv[])
{
    int tam, i, j;
    int n;

    unsigned long int h = 100;
    char *x, *c, *d;
    FILE *entrada, *salida, *k;

    if(argc <= 8 || argc > 12)
    {
        printf("\nPrograma HILL ejecutado. Uso del programa:\n"
               "afin {-C | -D} {-m |Zm|} {-n Nk} {-k fileK} [-i filein] [-o fileout]\n"
               "-C: El programa cifra\n"
               "-D: El programa descifra\n"
               "-m: Cardinalidad\n"
               "-n: Dimensión\n"
               "-k: Fichero con matriz\n"
               "-i: Fichero de entrada\n"
               "-o: Fichero de salida\n");
    }
    else
    {
        // Leemos matriz
        n = atoi(argv[5]);

        k = fopen (argv[7], "r");
        if (k == NULL)
        {
            printf ("Error al abrir el fichero de matriz\n");
            return -1;
        }

        int **matrix = malloc(n * sizeof(int *));
        for (i = 0; i < n; i++)
		    matrix[i] = malloc (n * sizeof(int));

        for (i = 0; i < n; i++)
        {
            for (j = 0; j < n; j++)
            {
                if (!fscanf(k, "%d", &matrix[i][j]))
                    break;
                printf("%d", matrix[i][j]); // DEBUG
            }
        }
        fclose(k);

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
                x = malloc ((tam + 1) * sizeof (char));
                fread (x, 1, tam, entrada);
                fclose (entrada);
            }
            else    // Entrada por teclado
            {
                printf ("\nIntroducir entrada: ");
                scanf ("%m[^\n]%*c", &x);
                tam = strlen (x);
            }

            // c = cifrar (a, b, m, x, tam);
            
            // Scanf -> Fichero
            if ((argc < 11 ) && ((strcmp(argv[8], "-o") == 0 || strcmp(argv[8], "-O") == 0)))
            {
                salida = fopen (argv[9], "w");
                fputs (c, salida);
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
                fputs (c, salida);
                fclose (salida);
            }
            printf("\n");
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
                x = malloc ((tam + 1) * sizeof (char));
                fread (x, 1, tam, entrada);
                fclose (entrada);
            }
            else    // Entrada por teclado
            {
                printf ("\nIntroducir entrada: ");
                scanf ("%m[^\n]%*c", &x);
                tam = strlen (x);
            }


            // d = descifrar (a, b, m, y, x, tam);

            // Scanf -> Fichero
            if ((argc < 11 ) && ((strcmp(argv[8], "-o") == 0 || strcmp(argv[8], "-O") == 0)))
            {
                salida = fopen (argv[9], "w");
                fputs (d, salida);
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
                fputs (d, salida);
                fclose (salida);
            }
            printf("\n");

        }
        else
        {
            printf("\nError en los parámetros\n");
        }

    free(c);
    free(d);
    free(x);
    }

    return 0;
}
