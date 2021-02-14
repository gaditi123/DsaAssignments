#include <stdio.h> 
#include <stdlib.h> 
#include <math.h>
#include <string.h>

typedef struct proff{
    int order;
    int time;
    int deadline;
}proff;

void merge(proff *arr, int start, int mid, int end,int check) {
    proff *temp = (proff *)malloc((end - start + 1) * sizeof(proff));

	int i = start, j = mid+1, k = 0;

	while(i <= mid && j <= end) {
        if(check==0){
            if(arr[i].deadline <= arr[j].deadline) {
                temp[k] = arr[i];
                k += 1; i += 1;
            }
            else {
                temp[k] = arr[j];
                k += 1; j += 1;
            }
        }
        else{
            if(arr[i].time <= arr[j].time) {
                temp[k] = arr[i];
                k += 1; i += 1;
            }
            else {
                temp[k] = arr[j];
                k += 1; j += 1;
            }
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

void mergeSort(proff *arr, int start, int end,int check) {
	if(start < end) {
		int mid = (start + end) / 2;
		mergeSort(arr, start, mid,check);
		mergeSort(arr, mid+1, end,check);
		merge(arr, start, mid, end,check);
	}
}

int getCount(proff arr[],int start,int deadline,int n){
    int i = start+1,count=1;

    while(1){
        if(arr[i].deadline==deadline && i<n)
            count++;
        i++;
        if(i>=n) break;
    }
    return count;
}

void sortTimings(proff arr[],int n){
    int deadline = arr[0].deadline;
    int start = 0,i,min_idx;
    int count = getCount(arr, start,deadline, n);
    while(start<n){
        mergeSort(arr, start, start + count - 1,1);  //1 is to denote sort for time
        start += count;
        count = getCount(arr, start,arr[start].deadline, n);
        deadline = arr[start].deadline;
    }
}

int maxNum(int a, int b){
    if(a>b) return a;
    return b;
}

int getAnnoyance(proff arr[],int n){
    int timer = 0, annoyance = 0;
    for (int i = 0; i < n;i++){
        timer += arr[i].time;
        annoyance += maxNum(timer - arr[i].deadline, 0);
    }
    return annoyance;
}

int main(){
    int n;
    scanf("%d\n", &n);
    proff *arr=(proff*)malloc(n*sizeof(proff)); 
    for(int i = 0; i < n; i++){
        scanf("%d %d", &arr[i].time, &arr[i].deadline);
        arr[i].order = i + 1;
    }
    mergeSort(arr, 0, n-1,0); //0 is to denote sort for deadline
    sortTimings(arr, n);
    printf("Order:");
    for (int i = 0; i < n;i++)
        printf("%d,", arr[i].order);
    
    printf("\nAnnoyance: %d",getAnnoyance(arr,n));

    return 0;
}