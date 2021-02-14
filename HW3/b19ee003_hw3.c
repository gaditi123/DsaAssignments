#include <stdio.h> 
#include <stdlib.h> 
#include <math.h>
#include <string.h>

typedef struct Node {
    int data;
    struct Node *left, *right;
}Node;
typedef struct Stack{
    int top;
    int capacity;
    Node** array;
} Stack;
typedef struct Queue{
    int front, rear,size;
    int capacity; 
    Node** array;
} Queue;
Stack* createStack(int capacity)
{
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    stack->capacity = capacity;
    stack->top = -1;
    stack->array = (Node**)malloc(stack->capacity * sizeof(Node));
    return stack;
}
Queue* createQueue(int capacity) 
{
    Queue *queue = (Queue *)malloc(sizeof(Queue));
    queue->capacity = capacity;
    queue->front = 0;
    queue->rear = capacity - 1;
    queue->size = 0;
    queue->array =(Node**)malloc(queue->capacity * sizeof(Node));
    return queue; 
}
void enqueue(Queue* queue, Node* node) 
{ 
    if (queue->size == queue->capacity) 
        return; 
    queue->rear = (queue->rear + 1)% queue->capacity; 
    queue->size = queue->size + 1; 
    queue->array[queue->rear] = node; 
} 

void dequeue(Queue* queue) 
{ 
    if (queue->size==0)
        return;
    queue->front = (queue->front + 1)% queue->capacity; 
    queue->size = queue->size - 1; 
} 
Node* newNode(int data)
{
    Node *temp=(Node*) malloc(sizeof(Node)); ;
    temp->data = data;
    temp->left = NULL;
    temp->right = NULL; 
    return temp;
}
Node* insert(Node* root, int data)  //to make the tree
{
    Node* newnode = newNode(data);
    Node* x = root;
    Node* y = NULL;
 
    while (x != NULL) {
        y = x;
        if (data < x->data)
            x = x->left;
        else
            x = x->right;
    }
    if (y == NULL)
        y = newnode;

    else if (data < y->data)
        y->left = newnode;

    else
        y->right = newnode;

    return y;
}

void push(Stack* stack,Node* node){
    if(stack->top == stack->capacity - 1){
        return;
    }
    stack->top++;
    stack->array[stack->top] = node;
}
void pop(Stack* stack){
    stack->top--;
}
Node* top(Stack* stack){
    return stack->array[stack->top];
}
void Inorder(Stack* stack,Node* root)
{
        Node *x = root;
        if (root == NULL)
            printf("Tree is empty");
        else {
            int flag = 1;
            while(flag){
                if(x!=NULL){
                    push(stack,x);
                    x = x->left;
                }
                else{
                    if(stack->top!=-1){ //stack not empty
                        x=top(stack);
                        pop(stack);
                        printf("%d ", x->data);                    
                        x = x->right;
                    }
                    else
                        flag = 0;
                }
            }
        }              
}

void Preorder(Stack *stack, Node *root){
    if(root!=NULL){
        Node *x = root;
        push(stack, x);
        while(stack->top!=-1){
            x=top(stack);
            pop(stack);
            printf("%d ", x->data);
            if(x->right!=NULL) push(stack, x->right);
            if(x->left!=NULL) push(stack, x->left);
        }
    }
    else
        printf("Tree is empty");
}

void Postorder(Stack* stack, Node* root){
    if(root!=NULL){
        Stack *stacktemp = createStack(stack->capacity);
        Node *x = root;
        push(stack, x);
        while(stack->top!=-1){
            x=top(stack);
            pop(stack);
            push(stacktemp, x);
            if(x->left!=NULL)
                push(stack, x->left);     
            if(x->right!=NULL)
                push(stack, x->right);   
        }
        while(stacktemp->top!=-1){
            printf("%d ", top(stacktemp)->data);
            pop(stacktemp);
        }
    }
    else
        printf("Tree is empty");
}

void height(Node* root, Queue* queue){
    if(root==NULL)
        printf("Tree is empty");
    else{
        enqueue(queue, root);
        int height = 0;
        int flag = 0; //to check if its not a leaf
        int nodes = 1;  //to store total number of nodes
        int leaf = 0;  //tp store total number of leaves
        while(1){
            int childcount = queue->size;
            if(childcount==0){
                printf("Height:%d\n", --height);
                printf("Internal Nodes:%d\n",nodes-leaf);
                printf("Leaves:%d\n", leaf);
                return;
            }
            else{
                height++;
                while(childcount>0){
                    Node *x = queue->array[queue->front];
                    dequeue(queue);
                    if(x->left!=NULL){
                        flag = 1;
                        nodes++;
                        enqueue(queue, x->left);
                    }
                    if(x->right!= NULL){
                        enqueue(queue, x->right);
                        flag = 1;
                        nodes++;
                    }
                    if(flag==0) leaf++;
                    flag = 0;
                    childcount--;
                }
            }
        }
    }
}

Node* deleteNode(Node* root,int del){
    Node *x = root;
    Node *parent = NULL;
    while(x->data!=del){
        parent = x;
        if(x->data>del)
            x = x->left;
        else
            x = x->right;
    }

    if(x->left==NULL || x->right==NULL){  //has only one child
    if(x!=root){
        if(x->left==NULL){
            if(parent->left==x)
                parent->left = x->right;
            else
                parent->right = x->right;
        }
        else{
            if(parent->left==x)
                parent->left = x->left;
            else
                parent->right = x->left;
        }
    }
    else{
        root=(x->left)? x->left: x->right;
    }
    }
    else if(x->left!=NULL && x->right!=NULL){  //has 2 children
        Node *temp = x->left; //will store the inorder predecessor
        while(temp->right!=NULL){
            temp = temp->right;
        }
        int data = temp->data;
        deleteNode(root, temp->data);
        //free(temp);
        x->data = data;
    }
    else if(x->left==NULL && x->right==NULL){  //leaf node
        if(x!=root){
            if(parent->left==x)
                parent->left == NULL;
            else
                parent->right == NULL;
        }
        else
            root = NULL;
    }
    return root;
}

int main(){
    int flag = 1;
    Node* root = NULL;
    int n;
    Stack* stack = createStack(n);
    Queue* queue = createQueue(2*n);
    while(flag){
        int operation;
        printf("Enter a number from 1-6 or 7 to exit: ");
        scanf("%d", &operation);
        switch (operation)
        {
        case 1:
        {            
            scanf("%d ", &n);
            int* arr = (int *)malloc(n * sizeof(int));            
            for (int i = 0; i < n;i++){
                int a; scanf("%d", &a);
                if(i==0) root = insert(root, a);
                else insert(root, a);
            }
            break;
        }
        case 2:{
            int del;
            printf("Enter node to delete: ");
            scanf("%d", &del);
            root=deleteNode(root, del);
            //Preorder(stack, root);
            printf("Deleted succesfully\n");
            break;
        }
        case 3:
        {
            height(root,queue);
            break;
        }  
        case 4:
        {
            printf("Inorder traversal: ");
            Inorder(stack,root);
            printf("\n");
            break;
        }
        case 5:
        {    
            printf("Preorder traversal: ");        
            Preorder(stack,root);
            printf("\n");
            break;
        }
        case 6:
        {            
            printf("Postorder traversal: ");
            Postorder(stack,root);
            printf("\n");
            break;
        }
        case 7:  //exit the program
        {
            return 0;
            break;
        }
        default: break;
        }
    }  
    return 0;
}