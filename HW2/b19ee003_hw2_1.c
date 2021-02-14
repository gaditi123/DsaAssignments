#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>

typedef struct Stack {
    int top;
    unsigned capacity;
    char* array;
}STACK;
typedef struct Output{
    char operation;
    char num;
    struct Output *next;
} OUTPUT;
void append(OUTPUT** head_ref, char operation, int number) 
{ 
	OUTPUT* new_node = (OUTPUT*) malloc(sizeof(OUTPUT)); 
	OUTPUT *last = *head_ref;
	new_node->operation = operation; 
	new_node->num = number; 
	new_node->next = NULL; 
	if (*head_ref == NULL) 
	{ 
		*head_ref = new_node; 
		return; 
	}
	while (last->next != NULL) last = last->next;
	last->next = new_node;
} 
void printOutput(OUTPUT** head_ref){
    OUTPUT *ptr = *head_ref;
    while(ptr!=NULL){
        if(ptr->operation=='p'){
            printf("push(%d),", ptr->num);
        }
        else{
            printf("pop(),");
        }
        ptr = ptr->next;
    }
}
STACK* createStack(unsigned capacity)
{
    STACK* stack = (STACK*)malloc(sizeof(STACK));
    stack->capacity = capacity;
    stack->top = -1;
    stack->array = (char*)malloc(stack->capacity * sizeof(char));
    return stack;
}
int isFull(STACK* stack){
    return stack->top == stack->capacity - 1;
}
void push(STACK* stack,char value){
    if(isFull(stack)){
        return;
    }
    stack->top++;
    stack->array[stack->top] = value;
}
void pop(STACK* stack){
    stack->top--;
}
int isTop(STACK* stack){
    return stack->array[stack->top];
}
int isEmpty(STACK* stack){
    return stack->top == -1;
}
int main(){
    int n;
    scanf("%d\n", &n);
    STACK* stack = createStack(n);
    int* arr = (int *)malloc((n) * sizeof(int));
    int j = 0;
    int i;
    for (i = 0; i < n-1;i++){
        scanf("%d\n", &arr[i]);
    }
    scanf("%d", &arr[i]);
    int counter = 0;
    OUTPUT *head1 = NULL;
    for (int i = 1; i <= n;i++){
        push(stack, i);
        append(&head1, 'p', i); //p will denote that its a push operation
        while((isTop(stack))==arr[counter]){
            pop(stack);
            append(&head1, 'o', i); //o will denote that its a pop operation
            counter++; 
        }
    }
    if(!isEmpty(stack)){
        printf("Not valid sequence");
    }
    else{
        printOutput(&head1);
    }
    return 0;
}