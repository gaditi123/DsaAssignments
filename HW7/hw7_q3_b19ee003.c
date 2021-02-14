#include <stdio.h> 
#include <stdlib.h> 
#include <math.h>
#include <string.h>

int findMin(int* distance,int* visited,int n){
    int minDis = INT_MAX;
    int minVertex = -1;
    for (int i = 0; i < n;i++){
        if(distance[i]<minDis && visited[i]==0){
            minDis = distance[i];
            minVertex = i;
        }
    }
    return minVertex;
}

void DijkstraAlgo(int** M,int n,int s){
    int *visited = (int *)malloc(n * sizeof(int));
    int *distance = (int *)malloc(n * sizeof(int));
 
    for (int i = 0; i < n;i++){
        distance[i] = INT_MAX;
        visited[i] = 0;
    }
    distance[s] = 0;

    for (int i = 0; i < n;i++){
        int minVertex = findMin(distance, visited,n);
        visited[minVertex] = 1;
        for (int j = 0; j < n;j++){
            if(((distance[minVertex]+M[minVertex][j])<distance[j]) && visited[j]==0 && M[minVertex][j]!=0){
                distance[j] = distance[minVertex] + M[minVertex][j];
            }
        }
    }

    for (int i = 0; i < n; i++){
        if(distance[i]!=INT_MAX) printf("%d ", distance[i]);
        else
            printf("-1 ");
    }
}

int main(){
    int i,j, n=3,s=3, **M;
    FILE *fp;
    if((fp = fopen("input.txt","r"))==NULL) printf("Error");
    //fp = fopen("input.txt","r");
    fscanf(fp, "%d %d\n", &n,&s); /* assuming that n is a positive integer. */

    M= (int **) malloc(sizeof(int *)*n);
    for(i=0; i<7; i++)
        M[i] = (int*) malloc(sizeof(int)*n);
    for(i=0; i<n; i++)
        for(j=0; j<n; j++)
            fscanf(fp, "%d", &M[i][j]);

    DijkstraAlgo(M,n,s-1);

    fclose(fp);
    return 0;
}  