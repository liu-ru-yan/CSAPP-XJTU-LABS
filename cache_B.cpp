/* 
 * trans.c - Matrix transpose B = A^T
 *
 * Each transpose function must have a prototype of the form:
 * void trans(int M, int N, int A[N][M], int B[M][N]);
 *
 * A transpose function is evaluated by counting the number of misses
 * on a 1KB direct mapped cache with a block size of 32 bytes.
 */ 
#include <stdio.h>
#include "cachelab.h"

int is_transpose(int M, int N, int A[N][M], int B[M][N]);

/* 
 * transpose_submit - This is the solution transpose function that you
 *     will be graded on for Part B of the assignment. Do not change
 *     the description string "Transpose submission", as the driver
 *     searches for that string to identify the transpose function to
 *     be graded. 
 */
char transpose_submit_desc[] = "Transpose submission";
void transpose_submit(int M, int N, int A[N][M], int B[M][N])
{/*
    int x=M/8,y=N/8;
    for(int i=0;i<x;i=i+8){
        for(int j=0;j<y;j=j+8){
            int t1=
        }
    }
    */
    
    if(M==32){
        /*
        for(int i=0;i<N;i=i+8){
            for(int j=0;j<N;j=j+8){
                for(int k=i;k<8+i;k++){
                    for(int q=j;q<8+j;q++){
                        B[q][k]=A[k][q];
                    }
                }
            }
        }
        */
        
        for(int i=0;i<M;i=i+8){
            for(int j=0;j<N;j=j+8){
                for(int k=0;k<8;k++){
                    int t1,t2,t3,t4,t5,t6,t7,t8;
                    t1=A[i+k][j];
                    t2=A[i+k][j+1];
                    t3=A[i+k][j+2];
                    t4=A[i+k][j+3];
                    t5=A[i+k][j+4];
                    t6=A[i+k][j+5];
                    t7=A[i+k][j+6];
                    t8=A[i+k][j+7];

                    B[j][i+k]=t1;
                    B[j+1][i+k]=t2;
                    B[j+2][i+k]=t3;
                    B[j+3][i+k]=t4;
                    B[j+4][i+k]=t5;
                    B[j+5][i+k]=t6;
                    B[j+6][i+k]=t7;
                    B[j+7][i+k]=t8;
                }
            }
        }
        return;
        
        

    }
    
    if(M==64){
        
        for(int i=0;i<M;i=i+4){
            for(int j=0;j<N;j=j+4){
                for(int k=0;k<4;k++){
                    int t1,t2,t3,t4;
                    t1=A[i+k][j];
                    t2=A[i+k][j+1];
                    t3=A[i+k][j+2];
                    t4=A[i+k][j+3];


                    B[j][i+k]=t1;
                    B[j+1][i+k]=t2;
                    B[j+2][i+k]=t3;
                    B[j+3][i+k]=t4;


                }
            }
        }
        return;
    }
    
    
    /*
    if(M==64){
        for(int i=0;i<M;i=i+2){
            for(int j=0;j<N;j=j+2){
                for(int k=0;k<2;k++){
                    int t1,t2;
                    t1=A[i+k][j];
                    t2=A[i+k][j+1];



                    B[j][i+k]=t1;
                    B[j+1][i+k]=t2;



                }
            }
        }



        return;

    }
    */
    /*
        for(int i=0;i<M;i=i+8){
            for(int j=0;j<N;j=j+8){
                for(int x=0;x<i+8;x=x+4){
                    for(int y=0;y<i+8;y=y+4){
                        for(int z=0;z<x+4;z++){
                            for(int q=0;q<y+4;q++){
                                B[q][z]=A[z][q];
                            }
                        }
                    }
                }  
            }
        }
        */
    /*
    int strides=7;
        for(int i=0;i<64;i=i+strides){
            for(int j=0;j<64;j=j+strides){
                for(int k=i;k<64&&k<i+strides;k++){
                    for(int x=j;x<64&&x<j+strides;x++){
                        B[x][k]=A[k][x];
                    }
                    
                }
            }
        }
        */
        
    /*
    for(int i=0;i<M;i=i+8){
            for(int j=0;j<N;j=j+8){
                for(int x=0;x<i+8;x=x+4){
                    for(int y=0;y<4;y++){
                        int t1,t2,t3,t4;
                        t1=A[i+y][x];
                        t2=A[i+y][x+1];
                        t3=A[i+y][x+2];
                        t4=A[i+y][x+3];

                        B[x][i+y]=t1;
                        B[x+1][i+y]=t2;
                        B[x+2][i+y]=t3;
                        B[x+3][i+y]=t4;
                    }
                    
                }
            }
        }

    */
    
    
   


    
    if(M==61){
        /*
        for(int i=0;i<60;i=i+4){
            if(i==60){
                break;
            }
            for(int j=0;j<60;j=j+4){
                for(int k=0;k<4;k++){
                    int t1,t2,t3,t4;
                    t1=A[i+k][j];
                    t2=A[i+k][j+1];
                    t3=A[i+k][j+2];
                    t4=A[i+k][j+3];


                    B[j][i+k]=t1;
                    B[j+1][i+k]=t2;
                    B[j+2][i+k]=t3;
                    B[j+3][i+k]=t4;
                }
            }
        }
        int t1=A[60][60];
        int t2=A[61][60];
        int t3=A[62][60];
        int t4=A[63][60];
        int t5=A[64][60];
        int t6=A[65][60];
        int t7=A[66][60];
        B[60][60]=t1;
        B[60][61]=t2;
        B[60][62]=t3;
        B[60][63]=t4;
        B[60][64]=t5;
        B[60][65]=t6;
        B[60][66]=t7;
        
    }
    */
    
        int strides=16;
        for(int i=0;i<67;i=i+strides){
            for(int j=0;j<61;j=j+strides){
                for(int k=i;(k<67)&&(k<i+strides);k++){
                    for(int x=j;(x<61)&&x<(j+strides);x++){
                        B[x][k]=A[k][x];
                    }
                    
                }
            }
        }
    }
    return;
    

}

/* 
 * You can define additional transpose functions below. We've defined
 * a simple one below to help you get started. 
 */ 

/* 
 * trans - A simple baseline transpose function, not optimized for the cache.
 */
char trans_desc[] = "Simple row-wise scan transpose";
void trans(int M, int N, int A[N][M], int B[M][N])
{
    int i, j, tmp;

    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++) {
            tmp = A[i][j];
            B[j][i] = tmp;
        }
    }    

}

/*
 * registerFunctions - This function registers your transpose
 *     functions with the driver.  At runtime, the driver will
 *     evaluate each of the registered functions and summarize their
 *     performance. This is a handy way to experiment with different
 *     transpose strategies.
 */
void registerFunctions()
{
    /* Register your solution function */
    registerTransFunction(transpose_submit, transpose_submit_desc); 

    /* Register any additional transpose functions */
    registerTransFunction(trans, trans_desc); 

}

/* 
 * is_transpose - This helper function checks if B is the transpose of
 *     A. You can check the correctness of your transpose by calling
 *     it before returning from the transpose function.
 */
int is_transpose(int M, int N, int A[N][M], int B[M][N])
{
    int i, j;

    for (i = 0; i < N; i++) {
        for (j = 0; j < M; ++j) {
            if (A[i][j] != B[j][i]) {
                return 0;
            }
        }
    }
    return 1;
}