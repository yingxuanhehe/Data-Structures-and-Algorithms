#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 200 //The number digit limitation

typedef struct _btnode{
	int item;
	struct _btnode *left;
	struct _btnode *right;
} BTNode;   // You should not change the definition of BTNode

typedef struct _node{
     BTNode* item;
     struct _node *next;
}StackNode;

typedef struct _stack{
   int size;
   StackNode *head;
}Stack;

void deleteTree(BTNode **root);

void createExpTree(BTNode** root,char* prefix);
void printTree(BTNode *node);
void printTreePostfix(BTNode *node);
double computeTree(BTNode *node);

void push(Stack *sPtr,  BTNode* item);
int pop(Stack *sPtr);
BTNode *peek(Stack s);
int isEmptyStack(Stack s);

BTNode *createBTNode(int item);

int main()
{
    char prefix[SIZE];
    BTNode* root=NULL;

    printf("Enter an prefix expression:\n");
    gets(prefix);

    createExpTree(&root, prefix);

    printf("The Infix Expression:\n");
    printTree(root);
    printf("\n");
    printf("The Postfix (Reverse Polish) Expression:\n");
    printTreePostfix(root);
    printf("\n");
    printf("Answer ");
    printf("%.2f\n", computeTree(root));
    deleteTree(&root);
    return 0;
}

BTNode *createBTNode(int item){
    BTNode *newNode = malloc(sizeof(BTNode));
    newNode->item = item;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

void createExpTree(BTNode** root,char* prefix)
{
    Stack s;
    s.head=NULL;
    s.size=0;
    int size=0, num=0, place=1;
    char digit;
    BTNode *newNode;

    while(prefix[size]!='\0') size++;

    while(size)
    {
        switch (prefix[size-1])
        {
        case '+': case '-': case '*': case '/':
            newNode = createBTNode(prefix[size-1]);
            newNode->left = peek(s); pop(&s);
            newNode->right = peek(s); pop(&s);
            push(&s, newNode);
            size--;
            break;

        case ' ':
            size--;
            break;

        default:
            while(prefix[size-1]>='0' && prefix[size-1]<='9'){    //while is digit
                digit = prefix[size-1];
                num = num + ((digit-'0') * place);
                place *= 10;
                size--;
            }
            newNode = createBTNode(num);
            push(&s,newNode);
            place=1; num=0;
            break;
        }
    }
    *root = peek(s);

    /*for(i = 0; prefix[i]!='\0' && !isEmptyStack(s); i++)
    {
        c = prefix[i];

        if(c == ' ')
            continue;

        while(prefix[i]!=' ' && prefix[i]!= '\0')
        {
            stuff[j++] = prefix[i++];
        }
        //i++;     //ignoring the space and go to next token //can uncomment, it works too

        stuff[j] = '\0';
        j=0;
        //printf("%s.", stuff);

        if(isOpt(stuff[j])==1)
        {
            root = peek(s); pop(&s);

            (*root) = malloc(sizeof(BTNode));
            (*root)->item = stuff[j];
            (*root)->left = NULL;
            (*root)->right = NULL;

            push(&s, &(*root)->right);
            push(&s, &(*root)->left);

        }

        else
        {
            root = peek(s); pop(&s);
            (*root) = malloc(sizeof(BTNode));
            (*root)->item = atoi(stuff);
            (*root)->left = NULL;
            (*root)->right = NULL;

        }
    }*/
}

void printTree(BTNode *node){
    //Write your code here
    if(node==NULL)
        return;

    printTree(node->left);

    if(node->left == NULL && node->right == NULL)
        printf("%d ", node->item);
    else
        printf("%c ", node->item);

    printTree(node->right);
    return;
}


void printTreePostfix(BTNode *node){
   //Write your code here
    if(node==NULL)
        return;

    printTreePostfix(node->left);
    printTreePostfix(node->right);

    if(node->left == NULL && node->right == NULL)
        printf("%d ", node->item);
    else
        printf("%c ", node->item);
    return;

}

double computeTree(BTNode *node){
    //Write your code here

    //if leaf node, must be operand, return operand
    if(node->left == NULL && node->right == NULL)
        return node->item;

    switch(node->item)
    {
        case('+'):
            return computeTree(node->left) + computeTree(node->right);
            break;

        case('-'):
            return computeTree(node->left) - computeTree(node->right);
            break;

        case('*'):
            return computeTree(node->left) * computeTree(node->right);
            break;

        case('/'):
            return computeTree(node->left) / computeTree(node->right);
            break;
    }
}

void push(Stack *sPtr, BTNode *item){
    StackNode *newNode;
    newNode = malloc(sizeof(StackNode));
    newNode->item = item;
    newNode->next = sPtr->head;
    sPtr->head = newNode;
    sPtr->size++;
}

int pop(Stack *sPtr){
    if(sPtr == NULL || sPtr->head == NULL){
        return 0;
    }
    else{
       StackNode *temp = sPtr->head;
       sPtr->head = sPtr->head->next;
       free(temp);
       sPtr->size--;
       return 1;
    }
}

BTNode *peek(Stack s){
    return s.head->item;
}

int isEmptyStack(Stack s){
     if(s.size == 0) return 1;
     else return 0;
}

void deleteTree(BTNode **root){
    BTNode* temp;
    if(*root !=NULL)
    {
        temp = (*root)->right;
        deleteTree(&((*root)->left));
        free(*root);
        *root = NULL;
        deleteTree(&temp);
    }
}
