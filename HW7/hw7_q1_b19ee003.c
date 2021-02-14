#include <stdio.h> 
#include <stdlib.h> 
#include <math.h>
#include <string.h>

typedef struct vertex{
    int state;
    int discovery;
    int finish;
    struct vertex *pre;
} vertex;

int time=0;

void visit(int** M,vertex vertexArr[],int num,int n){
    time++;
    vertexArr[num].discovery = time;
    vertexArr[num].state = 1;
    for (int i = 0; i < n;i++){
        if(M[num][i]==1){
            if(vertexArr[i].state==0){
                vertexArr[i].pre = &vertexArr[num];
                visit(M, vertexArr, i, n);
            }
        }
    }
    vertexArr[num].state = 2;
    time++;
    vertexArr[num].finish = time;
}

int main(){
    int i,j, n, **M;
    FILE *fp;
    //if((fp = fopen("input.txt","r"))==NULL) printf("Error");
    fp = fopen("input.txt", "r");
    fscanf(fp, "%d\n", &n); /* assuming that n is a positive integer. */

    M= (int **) malloc(sizeof(int *)*n);
    for(i=0; i<n; i++)
        M[i] = (int*) malloc(sizeof(int)*n);
    for(i=0; i<n; i++)
        for(j=0; j<n; j++)
            fscanf(fp, "%d", &M[i][j]);

    vertex *vertexArr = (vertex *)malloc(n * sizeof(vertex));
    for (int i = 0; i < n;i++){
        vertexArr[i].state = 0;
        vertexArr[i].discovery = 0;
        vertexArr[i].finish = 0;
        vertexArr[i].pre = NULL;
    }

    for (int i = 0; i < n;i++){
        if(vertexArr[i].state==0){
            visit(M, vertexArr,i,n);
        }
    }
    
    for (int i = 0; i < n;i++){
        printf("%d %d %d\n", i + 1, vertexArr[i].discovery, vertexArr[i].finish);
    }
    for (int i = 0; i < n;i++){
        for (int j = 0; j < n;j++){
            if(M[i][j]==0)
                printf("0");
            else{
                if(vertexArr[j].pre==&vertexArr[i])
                    printf("T");
                else if(vertexArr[i].discovery>vertexArr[j].discovery && vertexArr[i].finish>vertexArr[j].finish)
                    printf("C");
                else if(vertexArr[i].discovery<vertexArr[j].discovery && vertexArr[i].finish>vertexArr[j].finish)
                    printf("F");
                else
                    printf("B");
            }
            if(j!=n-1)printf(" ");
        }
        printf("\n");
    }
    
    fclose(fp);
    return 0;
}