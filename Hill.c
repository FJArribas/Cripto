#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
void getCofactor(vector<vector<int> > &a, vector<vector<int> > &temp, int p, int q, int n){ 
    int i=0,j=0; 
    for(int row=0;row<n;row++){ 
        for(int col=0;col<n;col++){ 
            if(row!=p&&col!=q){ 
                temp[i][j++] = a[row][col]; 
                if (j==n-1){ 
                    j=0; 
                    i++; 
                } 
            } 
        } 
    } 
}
int determinant(vector<vector<int> > &a, int n, int N){ 
    int D = 0;
    if(n==1) 
        return a[0][0]; 
    vector<vector<int> > temp(N, vector<int>(N));
    int sign = 1;
    for(int f=0;f<n;f++){ 
        getCofactor(a, temp, 0, f, n); 
        D += sign * a[0][f] * determinant(temp, n - 1, N); 
        sign = -sign; 
    }
    return D; 
} 
void adjoint(vector<vector<int> > &a,vector<vector<int> > &adj,int N){ 
    if(N == 1){ 
        adj[0][0] = 1; 
        return; 
    } 
    int sign = 1;
    vector<vector<int> > temp(N, vector<int>(N));
    for(int i=0;i<N;i++){ 
        for(int j=0;j<N;j++){ 
            getCofactor(a, temp, i, j, N); 
            sign = ((i+j)%2==0)? 1: -1; 
            adj[j][i]= (sign)*(determinant(temp, N-1 , N)); 
        } 
    } 
}
*/

void print_matrix(int **matrix, int size){

    int i, j;

    for(i=0;i<size;i++){
        for(j=0;j<size;j++){
            printf("%d", matrix[i][j]);
        }
        printf("\n");
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

int main(){

    int det = 0, i, j, n = 1, m, h;

    // Determinante debe dar = 18
    int matrix1[3][3] = {
        {1, 3, 5},
        {2, 0, 4},
        {4, 2, 7}
    };


    /************* MATRIX OF SIZE = 1 *************/
    int **array1 = malloc(n * sizeof(int *));
	for(i = 0; i < n; i++)
		array1[i] = malloc(n * sizeof(int));

    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            array1[i][j] = i+j;
        }
        printf("\n");
    }

    /* Printing values of matrix 1 */
    printf("This is matrix of 1 size\n");
    print_matrix(array1, n);

    det = determinant(array1, n);

    printf("\nThis is the determinant received of size 1 %d", det);

    /* Freeing values of matrix 1 */
    for(i = 0; i < n; i++)
		free((void *)array1[i]);
	free((void *)array1);



    /************* MATRIX OF SIZE = 2 *************/

    n = 2;
    /* We create a matrix of 2 */
    int **array2 = malloc(n * sizeof(int *));
	for(i = 0; i < n; i++)
		array2[i] = malloc(n * sizeof(int));

    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            array2[i][j] = i+j;
        }
        printf("\n");
    }

    /* Printing values of matrix 2 */
    printf("This is matrix of 2 size\n");
    print_matrix(array2, n);

    det = determinant(array2, n);

    printf("\nThis is the determinant received of size 2 %d", det);

    /* Freeing values of matrix 2 */
    for(i = 0; i < n; i++)
		free((void *)array2[i]);
	free((void *)array2);



    /************* MATRIX OF SIZE = 3 *************/

    n = 3;
    /* We create a matrix of 3 */
    int **array3 = malloc(n * sizeof(int *));
	for(i = 0; i < n; i++)
		array3[i] = malloc(n * sizeof(int));

    int k = 2;
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            array3[i][j] = k*i+j+1;
        }
        printf("\n");
    }

    /* Printing values of matrix 3 */
    printf("This is matrix of 3 size\n");
    print_matrix(array3, n);

    det = determinant(array3, n);

    printf("\nThis is the determinant received of size 3 %d", det);

    /* Freeing values of matrix 3 */
    for(i = 0; i < n; i++)
		free((void *)array3[i]);
	free((void *)array3);


    /************* MATRIX OF SIZE = 4 *************/
    int array5[16] = {1, 2, 3, 4, 3, 3, 5, 6, 5, 3, 7, 8, 7, 3, 9, 1};

    /*
    1 2 3 4
    2 3 4 3
    3 4 3 3 
    4 3 3 5   det = 29
    */

    n = 4;
    /* We create a matrix of 4 */
    int **array4 = malloc(n * sizeof(int *));
	for(i = 0; i < n; i++)
		array4[i] = malloc(n * sizeof(int));

    k = 2;
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            array4[i][j] = array5[i+j];
        }
        printf("\n");
    }

    /* Printing values of matrix 4 */
    printf("This is matrix of 4 size\n");
    print_matrix(array4, n);

    det = determinant(array4, n);

    printf("\nThis is the determinant received of size 4 %d", det);

    /* Freeing values of matrix 4 */
    for(i = 0; i < n; i++)
		free((void *)array4[i]);
	free((void *)array4);

    return(0);
}