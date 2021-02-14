#include <stdio.h> 
#include <stdlib.h> 
#include <math.h>
#include <string.h>

void makeMaxHeap(int arr[],int n,int i){
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    if(left<n && arr[left]>arr[i]){
        largest = left;
    }
    if(right<n && arr[right]>arr[i] && arr[right]>arr[left]){        
        largest = right;
    }
    if(largest!=i){
        int temp = arr[largest];
        arr[largest] = arr[i];
        arr[i] = temp;
        makeMaxHeap(arr, n, largest);
    }
       
}
void makeMinHeap(int arr[],int n,int i){
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    if(left<n && arr[left]<arr[i]){
        smallest=left;
    }
    if(right<n && arr[right]<arr[i]&& arr[right]<arr[left]){    
        smallest = right;
    }
    if(smallest!=i){
        int temp = arr[smallest];
        arr[smallest] = arr[i];
        arr[i] = temp;
        makeMinHeap(arr, n,smallest);
    }
}

void sendHeap(int arr[],int n, char type){
    int lastInternal = (n / 2) - 1;
    for (int i = lastInternal; i >= 0;i--){
        type=='X'?makeMaxHeap(arr, n, i):makeMinHeap(arr,n,i);
    }
    for (int i = 0; i < n;i++){
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main(){
    int whilecounter = 1;
    int* arrMax = (int *)malloc(100 * sizeof(int));
    int* arrMin = (int *)malloc(100 * sizeof(int));
    int nMax;
    int nMin;
    while(whilecounter){
        printf("Enter numbers 1-6 for functions and 7 to exit: ");
        int operation; 
        scanf("%d ",&operation);
        switch (operation)
        {
        case 1:
            {
                char type;
                scanf("%c", &type);
                if(type=='X'){                   
                    scanf("%d", &nMax);                    
                    for (int i = 0; i < nMax;i++){
                        scanf("%d", &arrMax[i]);
                    }
                    sendHeap(arrMax, nMax, 'X');
                }
                else{                   
                    scanf("%d", &nMin);                    
                    for (int i = 0; i < nMin;i++){
                        scanf("%d", &arrMin[i]);
                    }
                    sendHeap(arrMin, nMin, 'N');
                }
            }
            break;

            case 2:
            {
                char type;
                scanf("%c", &type);
                if(type=='X'){
                    scanf("%d", &arrMax[nMax]);
                    nMax++;
                    sendHeap(arrMax, nMax, 'X');
                }
                else{
                   scanf("%d", &arrMin[nMin]);
                    nMin++; 
                    sendHeap(arrMin, nMin, 'N');
                }
            }
            break;
            case 3:
            {
                char type;
                scanf("%c", &type);
                int del; scanf("%d", &del);
                if(type=='X'){                    
                    for (int i = 0; i < nMax;i++){
                        if(arrMax[i]==del){
                            arrMax[i] = arrMax[nMax - 1];
                            nMax--;
                            break;
                        }
                    }
                    sendHeap(arrMax, nMax, 'X');
                }
                else{
                    for (int i = 0; i < nMin;i++){
                        if(arrMin[i]==del){
                            arrMin[i] = arrMin[nMin - 1];
                            nMin--;
                            break;
                        }
                    }
                    sendHeap(arrMin, nMin, 'N');
                }
            }
            break;
            case 4:
            {
                char type;
                scanf("%c", &type);
                if(type=='X'){                   
                    arrMax[0] = arrMax[nMax - 1];
                    nMax--;
                    sendHeap(arrMax, nMax, 'X');  
                }        
                else{                  
                    arrMin[0] = arrMin[nMin - 1];
                    nMin--;
                    sendHeap(arrMin, nMin, 'N');
                }                
            }
            break;

            case 5:
            {
                char type;
                scanf("%c", &type);
                if(type=='X'){
                    for (int i = nMax - 1; i > 0;i--){
                        int temp = arrMax[i];
                        arrMax[i] = arrMax[0];
                        arrMax[0] = temp;
                        makeMaxHeap(arrMax, i, 0);
                    }
                    for (int i = 0; i < nMax;i++){
                        printf("%d ", arrMax[i]);
                    }
                    printf("\n");
                }
                else{
                    for (int i = nMin - 1; i > 0;i--){
                        int temp = arrMin[i];
                        arrMin[i] = arrMin[0];
                        arrMin[0] = temp;
                        makeMinHeap(arrMin, i, 0);
                    }
                    for (int i = nMin-1; i >= 0;i--){
                        printf("%d ", arrMin[i]);
                    }
                    printf("\n");
                }           
            }
            break;           
            case 7:
            {
                return 0;
                break;
            }
            default:
                break;
        }     
    }
    return 0;
}