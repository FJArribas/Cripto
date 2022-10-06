#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/* #include "gmp.h" */

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

/* Funcion que obtiene cofactores  el valor de los cofactores */
int** cofactor(int** array, int size, int row, int col){

    int matrix_ret[][];
    int i, j, k, l;

    // Obtenemos con loops cofactors y los devuelve
    for (i = 0;i < size;i++){
        for (j = 0;j < size;j++){
            if (i != row && j != col){
                // l++;
                matrix_ret[k][l] = array[i][j]
                l++;
                if(l == size -1) // Si llegas fin columnas reseteas y empiezas nueva row
                    k++;
                    l=0;
            }
        }
    }

    return matrix_ret;
}

int determinant(int** matrix, int size){

    if(size == 1){
        return matrix[0][0];
    }
    else if (size == 2){
        return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0]
    }
    else {
        for(i = 0; i < size; i++){
            cof = cofactor(matrix, size, 0, i) // 0 = row, i = column
            det += determinant(cof)
        }
    }

    return det;
}   