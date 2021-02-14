#include <stdio.h> 
#include <stdlib.h> 
#include <math.h>
#include <string.h>

int maxNum(int a ,int b){
    if(a>b) return a;
    return b;
}
int minNum(int a,int b){
    if(a<b)return a;
    return b;
}

int score(int arr[],int n) 
{ 
	int** table=(int**)malloc(n*sizeof(int*));
    for (int i=0; i<n; i++) table[i] = (int *)malloc(n * sizeof(int));

	int** coinSelect=(int**)malloc(n*sizeof(int*));
    for (int i=0; i<n; i++) coinSelect[i] = (int *)malloc(n * sizeof(int));
	
	int turn = (n % 2 == 0) ? 0 : 1; //0 1st person, 1 2nd person

	for (int i = 0; i < n; i++) {   //initialise the diagonals as base condition
		table[i][i] = turn ? arr[i] : 0; 
		coinSelect[i][i] = 1; 
	} 
	turn = !turn;
    int flag = 1; 
  
    while (flag < n) {   
        for (int i = 0; i + flag < n; i++) { 
            int scoreOne = table[i + 1][i + flag]; 
            int scoreTwo = table[i][i + flag - 1]; 

            if (turn) { 
                table[i][i + flag] = maxNum(arr[i] + scoreOne,arr[i + flag] + scoreTwo); 
  
                if (arr[i] + scoreOne > arr[i + flag] + scoreTwo) 
                    coinSelect[i][i + flag] = 1; 
  
                else coinSelect[i][i + flag] = 0; 
            } 
            else { 
                table[i][i + flag] = minNum(scoreOne, scoreTwo); 
  
                if (scoreOne < scoreTwo) coinSelect[i][i + flag] = 1; 
  
                else coinSelect[i][i + flag] = 0; 
            } 
        } 
        turn = !turn;   
        flag++; 
    } 

	int left = 0, right = n - 1,counter=0;
	printf("Sequence: ");
	while (left <= right) { 
		if (coinSelect[left][right]) { 
			if(counter%2==0) printf("%d,",arr[left]);
			left++; 
		} 
		else { 
			if(counter%2==0) printf("%d,",arr[right]);
			right--; 
		}
		counter++;
	} 
	return table[0][n-1]; 
} 

int main() 
{
	int n; 	scanf("%d ", &n);
	int *arr = (int *)malloc(n * sizeof(int));
	for (int i = 0; i < n;i++)
		scanf("%d", &arr[i]);

	printf("\nTotal Coins: %d", score(arr,n));

	return 0;
} 