#include <stdio.h>
#include <stdlib.h>

#define SIZE 80 //The limit of expression length

typedef struct _stackNode{
    char item;
    struct _stackNode *next;
}StackNode;

typedef struct _stack{
   int size;
   StackNode *head;
}Stack;

void push(Stack *sPtr, char item);
int pop(Stack *sPtr);
char peek(Stack s);
int isEmptyStack(Stack s);
int precedence(char op);

void in2Post(char*, char*);

int main()
{
    char infix[SIZE];
    char postfix[SIZE];

    printf("Enter an infix expression:\n");
    gets(infix);

    in2Post(infix,postfix);
    printf("The postfix expression is \n");
    printf("%s\n",postfix);
    return 0;
}

void in2Post(char* infix, char* postfix)
{
    Stack s;
    s.head=NULL;
    s.size=0;
    int i = 0;
    int j = 0;
    char c;
    while(*infix != '\0')
    {
        c = *infix;
        if((c >='0' && c <='9') || (c >='A' && c <='Z') || (c >='a' && c <='b')) //operands
        {
            postfix[i]= c;
            i++;
        }

        else if(c == ')')
        {
            while(peek(s) != '(')
            {
                postfix[i] = peek(s);
                i++;
                pop(&s);
            }
            pop(&s);
        }

        else if(c == '(')
        {
            push(&s, c);
        }

        else
        {
            while(!isEmptyStack(s) && peek(s)!= '(' && precedence(peek(s))>= precedence(*infix))
            {
                postfix[i] = peek(s);
                i++;
                pop(&s);
            }
            push(&s, c);
        }
        infix++;
    }

    while(!isEmptyStack(s))
    {
        postfix[i]=peek(s);
        i++;
        pop(&s);
    }
    postfix[i]='\0';
}
int precedence(char op)
{
    if (op == '*' || op == '/')
        return 1;
    return 0;
}

void push(Stack *sPtr, char item){
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

char peek(Stack s){
    return s.head->item;
}

int isEmptyStack(Stack s){
     if(s.size == 0) return 1;
     else return 0;
}
