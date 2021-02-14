#include <stdio.h> 
#include <stdlib.h> 
#include <math.h>
#include <string.h>

typedef struct edge{
    int u; //starting edge
    int v; //ending edge
    int weight;
} edge; 

void merge(edge *arr, int start, int mid, int end) {
    edge *temp = (edge *)malloc((end - start + 1) * sizeof(edge));

	int i = start, j = mid+1, k = 0;

	while(i <= mid && j <= end) {       
            if(arr[i].weight <= arr[j].weight) {
                temp[k] = arr[i];
                k += 1; i += 1;
            }
            else {
                temp[k] = arr[j];
                k += 1; j += 1;
            }
	}

	while(i <= mid) {
		temp[k] = arr[i];
		k += 1; i += 1;
	}

	while(j <= end) {
		temp[k] = arr[j];
		k += 1; j += 1;
	}

	for(i = start; i <= end; i += 1) 
        arr[i] = temp[i - start];
}

void mergeSort(edge *arr, int start, int end) {
	if(start < end) {
		int mid = (start + end) / 2;
		mergeSort(arr, start, mid);
		mergeSort(arr, mid+1, end);
		merge(arr, start, mid, end);
	}
}

void makeUnion(int parent[], int v1,int v2,int n){
    for (int i = 0; i < n;i++){
        if(parent[i]==v2)
            parent[i] = v1;
    }
}

int kruskalAlgo(int **M, int n)
{
    int *parent = (int *)malloc(n * sizeof(int));
    edge *edgeList=(edge*)malloc(50*sizeof(edge));  //array to store all the edges
    int edgeCount = 0; //store number of edges actually present

    for (int i = 1; i < n;i++){
        for (int j = 0; j < i;j++){
            if(M[i][j]!=0){
                edgeList[edgeCount].u = i;
                edgeList[edgeCount].v = j;
                edgeList[edgeCount].weight = M[i][j];
                edgeCount++;
            }
        }
    }
    mergeSort(edgeList, 0, edgeCount - 1);

    for (int i = 0; i < n;i++)
        parent[i] = i;
 
    edge *mstEdgeList = (edge *)malloc(edgeCount * sizeof(edge));  //store edges of mst
    int mstEdgeCount = 0;  //store number of edges in mst actually

    for (int i = 0; i < edgeCount;i++){
        int x = parent[edgeList[i].u];
        int y = parent[edgeList[i].v];

        if(x!=y){
            mstEdgeList[mstEdgeCount] = edgeList[i];
            makeUnion(parent, x, y,n);
            mstEdgeCount++;
        }
    }
    
    int totalWeight = 0;
    for (int i = 0; i < mstEdgeCount;i++){
        totalWeight += mstEdgeList[i].weight;
    }
    
    return totalWeight;
}

int main(){
    int i,j, n, **M;
    FILE *fp;
    if((fp = fopen("input.txt","r"))==NULL) printf("Error");
    //fp = fopen("input.txt","r");
    fscanf(fp, "%d\n", &n); /* assuming that n is a positive integer. */

    M= (int **) malloc(sizeof(int *)*n);
    for(i=0; i<n; i++)
        M[i] = (int*) malloc(sizeof(int)*n);
    for(i=0; i<n; i++)
        for(j=0; j<n; j++)
            fscanf(fp, "%d", &M[i][j]);

    printf("%d",kruskalAlgo(M,n));

    fclose(fp);
    return 0;
}   