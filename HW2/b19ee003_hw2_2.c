#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include<ctype.h>
#include <math.h>

typedef struct Stack {   //store the infix
    int top;
    int capacity;
    char* array;
}STACK;

typedef struct Equate{   //evaluate the postfix
    int top;
    int capacity;
    float *array;
}EQUATE;

typedef struct Output{  //store the postfix(linked list)
    char op;
    int number;
    struct Output *next;
} OUTPUT;

STACK* createStack(int capacity)
{
    STACK* stack = (STACK*)malloc(sizeof(STACK));
    stack->capacity = capacity;
    stack->top = -1;
    stack->array = (char*)malloc(stack->capacity * sizeof(char));
    return stack;
}
EQUATE* createCalculateStack(int capacity)
{
    EQUATE* stack = (EQUATE*)malloc(sizeof(EQUATE));
    stack->capacity = capacity;
    stack->top = -1;
    stack->array = (float*)malloc(stack->capacity * sizeof(float));
    return stack;
}
void append(OUTPUT** head_ref, char op,int number) 
{ 
	OUTPUT* new_node = (OUTPUT*) malloc(sizeof(OUTPUT)); 
	OUTPUT *last = *head_ref;
	new_node->op = op; 
	new_node->number = number; 
	new_node->next = NULL; 
	if (*head_ref == NULL) 
	{ 
		*head_ref = new_node; 
		return; 
	}
	while (last->next != NULL) last = last->next;
	last->next = new_node;
}
int getPre(char op){ //function to get precedence of operators
    if(op=='('|| op==')')
        return 4;
    else if(op=='^' || op=='<' || op=='>') 
        return 3;
    else if(op=='/'||op=='*')
        return 2;
    else if(op=='+' || op=='-')
        return 1;
    else
        return 0;
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
int isEmpty(STACK* stack){
    return stack->top == -1;
}
char Top(STACK* stack){
    return stack->array[stack->top];
}

float TopCalc(EQUATE* stack){
    return stack->array[stack->top];
}
void pushCalc(EQUATE* stack,float value){
    if(stack->top == stack->capacity - 1){
        return;
    }
    stack->top++;
    stack->array[stack->top] = value;
}
void popCalc(EQUATE* stack){
    stack->top--;
}
void evaluate(EQUATE* calcstack,OUTPUT** head_ref){
    OUTPUT *ptr = *head_ref;
    while(ptr!=NULL){
        if(ptr->op=='0'){
            pushCalc(calcstack, ptr->number);
        }
        else{
            char oper = ptr->op;
            if(oper!='^'){
                float a = TopCalc(calcstack);
                popCalc(calcstack);
                float b=TopCalc(calcstack);
                popCalc(calcstack);
                float sum;
                if(oper=='+')
                    sum = a + b;
                else if(oper=='-')
                    sum = a - b;
                else if(oper=='*')
                    sum = a *b;
                else if (oper == '/')
                    sum = a / b;
                else if(oper=='<')
                    sum = (int)a << (int)b;
                else
                    sum = (int)a >> (int)b;
                pushCalc(calcstack, sum);
            }
            else{
                float sum;
                float a = TopCalc(calcstack);
                popCalc(calcstack);
                sum = pow(a, 2);
                pushCalc(calcstack, sum);
            }
        }
        ptr = ptr->next;
    }
    printf("%f",TopCalc(calcstack));
}

int main(){
    char arr[101];
    fgets(arr, 101, stdin); //get the input

    STACK* stack = createStack(strlen(arr));  //stack to store operators while making the postfix
    EQUATE *calcstack = createCalculateStack(101); //stack used for evaluation of postfix
    OUTPUT *head1 = NULL;
    char storenum[5];//to store more than one digit numbers
    int storenumcounter = 0;

        for (int i = 0; i < strlen(arr); i++)
        {
            if (arr[i]-'0'>=0)
            {
                while (arr[i]-'0'>=0)
                {
                    printf("%c", arr[i]);
                    storenum[storenumcounter] = arr[i];
                    storenumcounter++;
                    i++;
                }
                storenum[storenumcounter] = '\0';
                append(&head1, '0', atoi(storenum));
                storenumcounter = 0;
                for (int j = 0; j < 5;j++){
                    storenum[j] = '0';
                }
                    printf(",");
                i--;
            }
            else{
            if(arr[i]=='<'||arr[i]=='>')
                i++;
            int precedence = getPre(arr[i]);
            if(precedence==4){
                if(arr[i]=='(')
                    push(stack, '(');
                else{
                    while(Top(stack)!='(' && !isEmpty(stack)){
                        if(Top(stack)!='<'&& Top(stack)!='>'){
                            printf("%c,", (Top(stack)));
                        }        
                        else{
                            Top(stack)=='<'?printf("<<,"):printf(">>,");
                        }
                        append(&head1, Top(stack), 0);
                        pop(stack);
                    }
                    pop(stack);
                }
            }
            else if(precedence==3||precedence==2||precedence==1)
            {
                int stopprecedence = getPre(Top(stack));
                if(precedence>stopprecedence|| Top(stack)=='('){
                    push(stack, arr[i]);
                }
                else{
                    while(getPre(Top(stack))>=precedence && !isEmpty(stack)){
                        if(Top(stack)!='('){
                            if(Top(stack)!='<'&& Top(stack)!='>'){
                                printf("%c,", (Top(stack)));
                            }        
                            else{
                                Top(stack)=='<'?printf("<<,"):printf(">>,");
                            }                      
                            append(&head1, Top(stack), 0);
                            pop(stack);
                        }   
                    }
                    push(stack, arr[i]);
                }
            }
        }
    }
    
    while(!isEmpty(stack)){
        if(Top(stack)!='<'&& Top(stack)!='>'){
            printf("%c,",stack->array[stack->top] );
        }       
        else{
            Top(stack)=='<'?printf("<<,"):printf(">>,");
        } 
        append(&head1, Top(stack), 0);
        pop(stack);
    }
    printf("\n");
    evaluate(calcstack, &head1);

    return 0;
}