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

typedef struct calculate{   //evaluate the postfix
    int top;
    int capacity;
    float *array;
}CALCULATE;

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
CALCULATE* createCalculateStack(int capacity)
{
    CALCULATE* stack = (CALCULATE*)malloc(sizeof(CALCULATE));
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
char Top(STACK* stack){
    return stack->array[stack->top];
}
int isEmpty(STACK* stack){
    return stack->top == -1;
}
float TopCalc(CALCULATE* stack){
    return stack->array[stack->top];
}
void pushCalc(CALCULATE* stack,float value){
    if(stack->top == stack->capacity - 1){
        return;
    }
    stack->top++;
    stack->array[stack->top] = value;
}
void popCalc(CALCULATE* stack){
    stack->top--;
}
void evaluate(CALCULATE* calcstack,OUTPUT** head_ref){
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
                sum=(oper=='+')?(a+b):((oper=='-')?(b-a):((oper=='*')?(a*b):((oper=='/')?(b/a):((oper=='<')?((int)b<<(int)a):((int)b>>(int)a)))));
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
    printf("%.3f",TopCalc(calcstack));
}

int main(){
    char arr[101];
    fgets(arr, 101, stdin); //get the input
    OUTPUT *head1 = NULL;

    char storenum[4];//to store more than one digit numbers
    int storenumcounter = 0;
    STACK* stack = createStack(strlen(arr));  //stack to store operators while making the postfix
    CALCULATE *calcstack = createCalculateStack(101); //stack used for evaluation of postfix
    int flag = 0; //to check if valid expression or not

    for (int i = 0; i < strlen(arr);i++){ //to check if its a valid expression with equal opeing and closing brackets
        if(arr[i]=='(')
            flag++;
        else if(arr[i]==')')
            flag--;
    }
    if(getPre(arr[0])!=4 && getPre(arr[0])!=0) //check if the expression doesn't start with an operator
        flag = 1;
    if(flag==0){
        for (int i = 0; i < strlen(arr); i++)
        {
            if (isdigit(arr[i]))
            {
                while (isdigit(arr[i]))
                {
                    printf("%c", arr[i]);
                    storenum[storenumcounter] = arr[i];
                    storenumcounter++;
                    i++;
                }
                storenum[storenumcounter] = '\0';
                append(&head1, '0', atoi(storenum));
                storenumcounter = 0;
                for (int j = 0; j < 4;j++){
                    storenum[j] = '0';
                }
                    printf(",");
                i--;
            }
            else{
            if(arr[i]=='<'||arr[i]=='>')
                i++;
            int level = getPre(arr[i]);
            if(level==4){
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
            else if(level==3||level==2||level==1)
            {
                int stoplevel = getPre(Top(stack));
                if(level>stoplevel|| Top(stack)=='('){
                    push(stack, arr[i]);
                }
                else{
                    while(getPre(Top(stack))>=level && !isEmpty(stack)){
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
                        else break;
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
    }
    else{
        printf("not a valid expression");
    }
    return 0;
}
