#include <stdio.h> 
#include <stdlib.h> 
#include <math.h>
#include <string.h>

typedef struct hashTable{
    int flag;
    int data;
}hashTable;
int n, m;
int hashcode1(int data,int arrLen){
    return data % arrLen;
}

void insertTable(hashTable* arr,int data,int arrLen){
    int hash1 = hashcode1(data,arrLen);

    int index = hash1;
 
    for(int i=1;i<=arrLen;i++){ 
        if(arr[index].data==-1)
            break;
        index = (hash1 + i) % arrLen;
    }
    arr[index].data = data;
    arr[index].flag = 1;
}

int searchTable(hashTable* arr,int data,int arrLen){
    int hash1 = hashcode1(data,arrLen);

    int index = hash1;

    for (int i = 1; i <= arrLen;i++){    
        if(arr[index].data==data)
            return 1;
        index = (hash1 + i) % arrLen; 
    }
    return 0;
}

int symmetricDiff(hashTable* arrA,hashTable* arrB,int arrC[],int n,int m){
    int counter = 0;
    for(int i=0;i<n;i++){ 
        if(arrA[i].data!=-1 && searchTable(arrB,arrA[i].data,m)==0){
            arrC[counter] = arrA[i].data;
            counter++;
        }
    }
    for(int i=0;i<m;i++){ 
        if(arrB[i].data!=-1 && searchTable(arrA,arrB[i].data,n)==0){
            arrC[counter] = arrB[i].data;
            counter++;
        }
    }
    return counter;
}

int intersection(hashTable* arrA,hashTable* arrB,int arrD[],int n,int m){
    int counter = 0;
    for(int i=0;i<n;i++){ 
        if(arrA[i].data!=-1 && searchTable(arrB,arrA[i].data,m)==1){
            arrD[counter] = arrA[i].data;
            counter++;
        }
    }
    return counter;
}

int main(){
    scanf("%d,", &n);
    hashTable *arrA=(hashTable*)malloc((n)*sizeof(hashTable)); //makes a hashtable
 	for(int i = 0; i < n; i++){
		arrA[i].data = -1;
		arrA[i].flag = 0;
	}
    for (int i = 0; i < n;i++){
        int a;
        scanf("%d,", &a);
        insertTable(arrA,a,n);
    }
    scanf("%d,", &m);
    hashTable *arrB=(hashTable*)malloc((m)*sizeof(hashTable)); //makes a hashtable
    for(int i = 0; i < m; i++){
		arrB[i].data = -1;
		arrB[i].flag = 0;
	}
    for (int i = 0; i < m;i++){
        int a;
        scanf("%d,", &a);
        insertTable(arrB,a,m);
    }
    int *arrC = (int *)malloc((n + m) * sizeof(int));
    int *arrD = (int *)malloc((n + m) * sizeof(int));
    int counterC = symmetricDiff(arrA, arrB, arrC, n, m);
    int counterD=intersection(arrA, arrB,arrD,n,m);
    printf("\n\n\nC: ");
    for (int i = 0; i < counterC; i++){
        printf("%d,", arrC[i]);
    }
    printf("\n\n\n");
    printf("D: ");
    for (int i = 0; i < counterD; i++){
        printf("%d,", arrD[i]);
    }
    return 0;
}