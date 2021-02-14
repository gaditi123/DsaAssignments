#include <stdio.h> 
#include <stdlib.h> 
#include <math.h>
#include <string.h>

typedef struct hashTable{
    int num1;
    int num2;
}hashTable;

int hashcode1(int data,int arrLen){
    return data % arrLen;
}
int hashcode2(int data,int arrLen){
    int prime,flag;
	for (int i = arrLen - 1; i >= 1; i--)
    {
		flag = 0;
		for (int j = 2; j <= (int)sqrt(i); j++)
        {
			if (i % j == 0)
            {
				flag++;
			}
		}
		if (flag == 0)
        {
			prime= i;
            break;
        }
	}
	if(flag!=0) prime=3;
    return (prime - (data % prime));
}

void insertTable(int arr[],int data,int arrLen){
    arrLen *= 2;
    int hash1 = hashcode1(data,arrLen);
    int hash2 = hashcode2(data,arrLen);

    int index = hash1;
 
    for(int i=1;i<=arrLen;i++){ 
        if(arr[index]==-1)
            break;
        index = (hash1 + i*hash2) % arrLen;
    }
    arr[index] = data;
}

int searchPair(int arrB[],int data,int arrLen,int currentIndex){
    arrLen *= 2;
    int hash1 = hashcode1(data,arrLen);
    int hash2 = hashcode2(data,arrLen);

    int index = hash1;

    for (int i = 1; i <= arrLen;i++){    
        if(arrB[index]==data && index!=currentIndex){
            arrB[index] = -1;
            arrB[currentIndex] = -1;
            return 1;
        }
        index = (hash1 + i*hash2) % arrLen; 
    }
    return 0;
}

void makePairs(int arrB[],int k,int n){
    hashTable *store = (hashTable *)malloc(n * sizeof(hashTable));
    int check = 0;
    for (int i = 0; i < 2 * n;i++){
        int x = arrB[i];
        int y = k - arrB[i];
        int flag = 0;
        if(x!=-1){
            flag=searchPair(arrB, y, n,i);
            if(flag==1){            
                store[check].num1 = x;
                store[check].num2 = y;
                check++;
            }
        }        
    }
    if(check==0)
        printf("Not found");
    else{
        for (int i = 0; i < check;i++){
            printf("(%d,%d),", store[i].num1, store[i].num2);
        }
    }
}


int main(){
    int n;
    scanf("%d,", &n);
    int *arrA = (int *)malloc(n* sizeof(int));
    for (int i = 0; i < n;i++){
        int a;
        scanf("%d,", &arrA[i]);
    }
    
    int *arrB = (int *)malloc((2 * n) * sizeof(int));
    for(int i = 0; i < 2*n; i++){
		arrB[i]= -1;
	}
    for (int i = 0; i < n;i++){
        insertTable(arrB,arrA[i],n);
    }
    int k;
    scanf("%d", &k);
    makePairs(arrB, k, n);
    return 0;
}