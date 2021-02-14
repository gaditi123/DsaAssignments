#include <stdio.h> 
#include <stdlib.h> 
#include <math.h>
#include <string.h>

typedef struct Node{
    int value;
    struct Node *next;
} NODE;

void append(NODE** head_ref, int value) 
{ 
	NODE* new_node = (NODE*) malloc(sizeof(NODE)); 
	NODE *last = *head_ref;
	new_node->value = value; 
	new_node->next = NULL; 
	if (*head_ref == NULL) 
	{ 
		*head_ref = new_node; 
		return; 
	}
	while (last->next != NULL) last = last->next;
	last->next = new_node;
}

void reverseList(NODE** headptr){
    NODE* curr = *headptr;
    NODE* prev = NULL;    
    NODE* next = NULL;
    while (curr != NULL){
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    *headptr = prev;
}

void print(NODE** headptr){
    NODE *ptr = *headptr;
    while(ptr!=NULL){
        printf("%d ",ptr->value);
        ptr = ptr->next;
    }
}

int main(){
    NODE *head1 = NULL;
    int k;
    int n;
    scanf("%d\n", &n);
    for (int i = 0; i < n;i++){
        scanf("%d", &k);
        append(&head1, k);
    }
    reverseList(&head1);
    print(&head1);
    return 0;
}