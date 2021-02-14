#include <stdio.h> 
#include <stdlib.h> 
#include <math.h>
#include <string.h>

typedef struct Node{
    int power;
    int coeff;
    struct Node *next; 
}NODE; 
typedef struct Value{
	char p1[53];
	char p2[53];
	int x;
	struct Value *next;
}VALUE;

void append(NODE** head_ref, int power, int coeff) 
{ 
	NODE* new_node = (NODE*) malloc(sizeof(NODE)); 
	NODE *last = *head_ref;
	new_node->power = power; 
	new_node->coeff = coeff; 
	new_node->next = NULL; 
	if (*head_ref == NULL) 
	{ 
		*head_ref = new_node; 
		return; 
	}
	while (last->next != NULL) last = last->next;
	last->next = new_node;
}

int* getcoeff(char arr[]) 
{
	int* out = (int*)malloc(sizeof(int)*9);
	int i=1,j = 0;	
	int num = 0,flag=0; 
	int Neg = 1;	
	while((arr[i] != '\0')&&(arr[i] != '\n'))
	{
		if(arr[i] != ' ')
		{
			if(arr[i] == '-') Neg = -1;
			else num = 10*num + (arr[i] - '0');			
			flag = 1;
		}else{
			if(flag == 1)
			{
				num = Neg*num;
				out[j] = num;
				j++;
				flag = 0;
				num = 0;				
				Neg = 1;
			}
		}
		i++;
	}
	out[j] = Neg*num;
	return out;
}
int formNodes(char arr[], NODE** p)
{
	int* coeffArr = getcoeff(arr);
	int power = arr[0] - '0';
	int coeff = coeffArr[0];
	NODE* n = (NODE*)malloc(sizeof(NODE));
	n->power = power;
	n->coeff = coeff;
	n->next = NULL;
	*p = n; 
	int i,length=power;
	NODE* temp = *p;
	for(i = 1; i <= length ; i++)
	{
		power--;
		coeff = coeffArr[i];
			NODE* temp_ = (NODE*)malloc(sizeof(NODE));
			temp_->power = power;
			temp_->coeff = coeff;
			temp_->next = NULL;
			temp->next = temp_;
			temp = temp_;
	}
	return length;
}

void appendValue(VALUE** head_ref,char p1[],char p2[],int x) 
{ 
	VALUE* new_node = (VALUE*) malloc(sizeof(VALUE)); 
	VALUE*last = *head_ref;	
	strcpy(new_node->p1, p1);
	strcpy(new_node->p2, p2);
	new_node->x = x;
	new_node->next = NULL; 
	if (*head_ref == NULL) 
	{ 
		*head_ref = new_node; 
		return; 
	}
	while (last->next != NULL) last = last->next;
	last->next = new_node;
} 
void printList(NODE *node){
	NODE *ptr = node;
	int flag = 0; //will store if something did get printed
	while(ptr!=NULL)
	{	
		if(ptr==node && ptr->coeff!=0 && ptr->next!=NULL){
			printf("%dx^%d ", ptr->coeff,ptr->power);
			flag = 1;
		}
		else if(ptr==node && ptr->coeff==0 && ptr->next==NULL){
			printf("0");
			flag = 1;
		}
		else if(ptr->coeff>0 && ptr->power>0) {
			printf("+ %dx^%d ", ptr->coeff,ptr->power); 	
			flag = 1;	
		}	
		else if(ptr->coeff<0 && ptr->power>0) {
			printf("-%dx^%d ", -1*ptr->coeff,ptr->power); 
			flag = 1;		
		}
		else if(ptr->coeff>0 && ptr->power==0){
			printf("+ %d", ptr->coeff);	
			flag = 1;
		}
		else if(ptr->coeff<0 && ptr->power==0){
			printf("-%d", -1*ptr->coeff);
			flag = 1;
		}
		ptr = ptr->next; 
	}
	if(flag==0) printf("0");
} 
void summation(NODE* head1,NODE*head2, NODE** head3,int n1,int n2){	
	NODE *ptr1 = head1;
	NODE *ptr2 = head2;
	NODE *ptr3 = *head3;
	if(n1>n2){	
		for (int i = 0; i < n1 - n2;i++){
			append(&ptr3, ptr1->power, ptr1->coeff);
			ptr1 =ptr1->next;
		}
	}
	else{
		for (int i = 0; i < n2 - n1;i++){
			append(&ptr3, ptr2->power, ptr2->coeff);
			ptr2 = ptr2->next;
		}
	}
		for (int i = 0; i<=(n1>n2?n2:n1);i++){
			append(&ptr3, ptr1->power, ptr1->coeff+ptr2->coeff);
			ptr1 = ptr1->next;
			ptr2 = ptr2->next;
		}
		*head3 = ptr3;
		printList(ptr3);
}

void subtraction(NODE* head1,NODE* head2, NODE** head4,int n1,int n2){	
	NODE *ptr1 = head1;
	NODE *ptr2 = head2;
	NODE *ptr4 = *head4;
	if(n1>n2){	
		for (int i = 0; i < n1 - n2;i++){
			append(&ptr4, ptr1->power, ptr1->coeff);
			ptr1 =ptr1->next;
		}
	}
	else{
		for (int i = 0; i < n2 - n1;i++){
			append(&ptr4, ptr2->power,-1*ptr2->coeff);
			ptr2 = ptr2->next;
		}
	}
	for (int i = 0; i <=(n1>n2?n2:n1);i++){
		append(&ptr4, ptr1->power, ptr1->coeff-ptr2->coeff);
		ptr1 = ptr1->next;
		ptr2 = ptr2->next;
	}
	*head4 = ptr4;
	printList(ptr4);
}
void valuefind(NODE *node, int p){
	int count = 0;
	NODE *ptr = node;
	while (ptr != NULL) 
	{
		count += (ptr->coeff) * (pow(p, ptr->power));		
		ptr = ptr->next; 
	}
	printf("%d",count);
}
void freememory(NODE* node){
	NODE *n = node;
	while(n!=NULL){
		NODE *n1 = n;
		n = n->next;
		free(n1);
	}
}
int main() 
{
	int t; scanf("%d", &t);
	getchar();
	VALUE* valhead = NULL;
	for (int i = 0; i < t;i++){
		char p1[51];
		fgets(p1,51, stdin);

		char p2[51];
		fgets(p2,51, stdin);

		int x; scanf("%d", &x);
		getchar();
		appendValue(&valhead, p1, p2, x);
	}
	VALUE *valptr = valhead;
	while(valptr!=NULL){
		NODE *head1 = NULL;
		NODE *head2 = NULL;
		NODE *head3 = NULL;
		NODE *head4 = NULL;
		
		int n1 = formNodes(valptr->p1, &head1);
		int n2 = formNodes(valptr->p2, &head2);

		printf("P1(x) : ");
		printList(head1);
		printf("\nP2(x) : ");
		printList(head2);
		printf("\nP3(x) = P1(x) + P2(x) : ");
		summation(head1,head2,&head3,n1,n2);
		printf("\nP4(x) = P1(x) - P2(x) : ");
		subtraction(head1,head2,&head4,n1,n2);
		printf("\nP1(%d) : ",valptr->x);
		valuefind(head1, valptr->x);
		printf("\nP2(%d) : ",valptr->x);
		valuefind(head2, valptr->x);	
		printf("\nP3(%d) : ",valptr->x);
		valuefind(head3, valptr->x);
		printf("\nP4(%d) : ",valptr->x);
		valuefind(head4, valptr->x);
		printf("\n");
		freememory(head1);
		freememory(head2);
		freememory(head3);
		freememory(head4);
		valptr = valptr->next;
	}
		return 0;
} 