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

// TO DO AÑADIR EL MAIN DE AFIN PARA QUE FUNCIONE

