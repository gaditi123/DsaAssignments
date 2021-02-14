#include <stdio.h> 
#include <stdlib.h> 
#include <math.h>
#include <string.h>

//I have attempted bonus questions

typedef struct Node{
    int data;
    int height;
    int balance;
    struct Node *left, *right;
} NODE;

NODE* newNode(int data)
{
    NODE *temp=(NODE*) malloc(sizeof(NODE)); ;
    temp->data = data;
    temp->left = NULL;
    temp->right = NULL;
    temp->balance = 0;
    temp->height = 1;
    return temp;
}
int treeHeight(NODE* node){
    if(node==NULL)
        return 0;
    return node->height;
}
int maxi(int a, int b) 
{ 
    return (a > b)? a : b; 
} 
NODE* rightRotate(NODE* node){
    struct Node *x = node->left; 
	struct Node *temp = x->right; 
	x->right = node; 
	node->left = temp; 

	node->height = 1 + maxi(treeHeight(node->left), treeHeight(node->right));
	x->height = 1 + maxi(treeHeight(x->left), treeHeight(x->right));

    x->balance= x== NULL ? 0 : (treeHeight(x->right) - treeHeight(x->left));
    node->balance= node== NULL ? 0 : (treeHeight(node->right) - treeHeight(node->left));

	return x; 
}

NODE* leftRotate(NODE* node){
    struct Node *x = node->right; 
	struct Node *temp = x->left; 
	x->left = node; 
	node->right = temp; 

	node->height = 1 + maxi(treeHeight(node->left), treeHeight(node->right));
	x->height = 1 + maxi(treeHeight(x->left), treeHeight(x->right));

    node->balance= node== NULL ? 0 : (treeHeight(node->right) - treeHeight(node->left));
    x->balance= x== NULL ? 0 : (treeHeight(x->right) - treeHeight(x->left));
	return x; 
}

NODE* insert(NODE* node, int data){
	if (node == NULL) 
		return(newNode(data)); 

	if (data < node->data) 
   {
		node->left = insert(node->left, data); 
   }
	else if (data > node->data) 
   {
		node->right = insert(node->right, data); 
   }

	node->height = 1 + maxi(treeHeight(node->left), treeHeight(node->right));
 
	int balanceFac = node == NULL ? 0 : (treeHeight(node->right) - treeHeight(node->left));

	if (balanceFac > 1 && data > node->right->data) 
   {
		return leftRotate(node);
   }

	if (balanceFac < -1 && data < node->left->data) 
   {
		return rightRotate(node);                 
   }

	if (balanceFac > 1 && data <= node->right->data) 
	{ 
		node->right = rightRotate(node->right); 
		return leftRotate(node); 
	} 

	if (balanceFac < -1 && data >= node->left->data) 
	{ 
		node->left = leftRotate(node->left); 
		return rightRotate(node); 
	} 
    node->balance= node== NULL ? 0 : (treeHeight(node->right) - treeHeight(node->left));
	return node; 
}

void inorder(NODE* root)
{
    if (root == NULL) 
        return; 
    inorder(root->left); 
    printf("(%d,%d,%d),", root->data,root->height-1,root->balance); 
    inorder(root->right);            
}

int balanceFactorFunction(NODE *node)  
{  
    if (node == NULL)  
        return 0;  
    return treeHeight(node->right) - treeHeight(node->left);  
}  

NODE* deleteNode(NODE* root,int del){
   if (root == NULL)  
        return root;  

    if ( del < root->data )  
        root->left = deleteNode(root->left, del);    

    else if( del > root->data )  
        root->right = deleteNode(root->right, del);  

    else
    {  
        if( (root->left == NULL) || (root->right == NULL) )  
        {  
            NODE *temp = root->left ?  root->left :  root->right;    
            if (temp == NULL)  
            {  
                temp = root;  
                root = NULL;  
            }  
            else
            {
                temp->height = root->height;
                *root = *temp;
            } 
        }  
        else
        {  
            NODE* temp = root->right;  
            while (temp->left != NULL)  
                temp = temp->left;             
            root->data = temp->data;  
            root->right = deleteNode(root->right, temp->data);  
        }  
    }  
    
    if (root == NULL)  return root;  

    root->height = 1 + maxi(treeHeight(root->left),treeHeight(root->right));

    int balance = root== NULL ? 0 : (treeHeight(root->right) - treeHeight(root->left));

    if (balance > 1 && balanceFactorFunction(root->left) >= 0)  
    return leftRotate(root);         

    if (balance > 1 && balanceFactorFunction(root->left) < 0)  
    {  
        root->right = rightRotate(root->right);  
        return leftRotate(root);  
    }  

    if (balance < -1 &&  balanceFactorFunction(root->right) <= 0)  
         return rightRotate(root);  
  
    if (balance < -1 && balanceFactorFunction(root->right) > 0)  
    {  
        root->left = leftRotate(root->left);  
        return rightRotate(root); 
    }  
    root->balance= root== NULL ? 0 : (treeHeight(root->right) - treeHeight(root->left));    
    return root;  
}
int diameter(NODE* root){
    if (root == NULL)
        return 0;
    int lht = treeHeight(root->left);
    int rht = treeHeight(root->right);

    int ldia = diameter(root->left);
    int rdia = diameter(root->right); 
    return maxi(lht + rht +1, maxi(ldia, rdia));
}
void leftnodes(NODE* root){
    if(root== NULL)
        return;
    if(root->left){
        printf("%d,", root->data);
        leftnodes(root->left);
    }
    else if(root->right){
        printf("%d,", root->data);
        leftnodes(root->right);
    }
}
void leafnodes(NODE* root){
    if(root== NULL)
        return;
    if(root->left==NULL && root->right==NULL){
        printf("%d,", root->data);
    }
    leafnodes(root->left);
    leafnodes(root->right);
}
void rightnodes(NODE* root){
    if(root== NULL)
        return;
    if(root->right){
        rightnodes(root->right);
        printf("%d,", root->data);
    }
    else if(root->left){
        rightnodes(root->left);
        printf("%d,", root->data);
    }
}
int ifNodeExists(NODE* node, int key)
{
    if (node == NULL)
        return 0;
 
    if (node->data == key)
        return 1;

    int state1 = ifNodeExists(node->left, key);
     if(state1) return 1; 

    int state2 = ifNodeExists(node->right, key);
 
    return state2;
}
int ancestorNode(NODE* root, int a, int b) 
{ 
    if (root == NULL) return -1; 

    if (root->data > a && root->data >b) 
        return ancestorNode(root->left, a, b); 

    if (root->data < a && root->data < b) 
        return ancestorNode(root->right, a, b); 
    
    return root->data; 
} 

void route(NODE* root,int a,int b,int founda,int foundb){  
    if(root==NULL){
        printf("-1(no path exists)\n");
        return;
    }
    if (root->data > a && founda == 0){
            route(root->left, a, b, 0, 0);
    }
    if(root->data<a && founda==0){
        route(root->right, a,b, 0,0);
    }
    if(root->data==a && founda==0){
        route(root, a, b, 1,0);
    }
    if(root->data>b && founda==1){
        printf("%d,", root->data);
        route(root->left, a, b, 1,0);
    }
    if(root->data<b && founda==1){
        printf("%d,", root->data);
        route(root->right, a,b, 1,0);
    }
    if(root->data==b){
        printf("%d\n", root->data);
        return;
    }    
}
int main(){
    int whilecounter = 1;
    NODE *root = NULL;
    int n;
    while(whilecounter){
        printf("Enter numbers 1-7 for functions and 8 to exit: ");
        int operation;
        scanf("%d", &operation);
        switch (operation)
        {
        case 1:
        {            
            scanf("%d",&n);
            for (int i = 0; i < n;i++){
                int a;
                scanf("%d", &a);
                root = insert(root, a);
            }
        }
        break;
        case 2:
        {
            int a; 
            scanf("%d", &a);
            insert(root, a);
        }
        break;
        case 3:
        {
            int a; scanf("%d",&a);
            if(ifNodeExists(root,a)==1)
                root=deleteNode(root,a);
            else
                printf("Not present in the tree");
        }
        break;
        case 4:
        {
            inorder(root);
            printf("\n");
        }
        break;    
        case 5:{
            printf("Diameter/width:%d\n", diameter(root));
            printf("Perimeter: %d,",root->data);
            leftnodes(root->left);
            leafnodes(root);
            rightnodes(root->right);
            printf("\n");
        }
        break;
        case 6:
        {
            int a, b;
            scanf("%d %d", &a, &b);
            if(ifNodeExists(root,a)==1 && ifNodeExists(root,b)==1)
            printf("Lowest Common Ancestor of %d and %d : %d\n", a, b,ancestorNode(root, a, b));
            else
            printf("Lowest Common Ancestor does not exist");
        }
        break;
        case 7:
        {
            int a, b;
            scanf("%d %d", &a, &b);
            if(ifNodeExists(root,a)==1 && ifNodeExists(root,b)==1){
            printf("The path from %d to %d : ", a, b);
            route(root, a, b,0,0);
            }
            else{
                printf("-1\n");
            }
        }
        break;
        case 8:
            return 0;
            break;
        default:
            break;
        }
    }
    return 0;
}