#include<stdio.h>
#include<stdlib.h>

int result[10000][10000] = {0};
int matrix[10000][10000] = {0};

void mul_matrix(char *);

void mul_matrix(char *filename){
    int N;
    FILE *fp = freopen(filename, "r", stdin);
    scanf("%d", &N);

    for(int i = 0; i < N; i++){
        for(int j = 0 ; j < N; j++){
            scanf("%d", &matrix[i][j]);
        }
    }

    for(int i = 0 ; i < N ; i++){
        for(int j = 0 ; j < N ; j++){
            for(int k = 0 ; k < N ; k++){
                result[i][j] += matrix[i][k] * matrix[k][j];
            }
        }
    }
}
