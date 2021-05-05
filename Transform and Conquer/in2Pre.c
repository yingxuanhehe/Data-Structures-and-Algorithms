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

void in2Pre(char*, char*);

int main()
{
    char infix[SIZE];
    char prefix[SIZE];

    printf("Enter an infix expression:\n");
    gets(infix);

    in2Pre(infix,prefix);
    printf("The prefix expression is \n");
    printf("%s\n",prefix);

    return 0;
}

void in2Pre(char* infix, char* prefix)
{
    Stack s;
    s.head = NULL;
    s.size = 0;

    char c;
    char revInfix[SIZE];
    char revPrefix[SIZE];
    int i = 0, j = 0, begin, end, count = 0;

    while (infix[count]!='\0')
        count++;

    end = count - 1;

    for (begin = 0; begin < count; begin++) {
      revInfix[begin] = infix[end];
      end--;
    }

   revInfix[count] = '\0';

   while(revInfix[i] != '\0')
    {
        c = revInfix[i++];
        if((c >=48 && c <=57) || (c >=65 && c <=90) || (c >=97 && c <=122))
        {
            revPrefix[j++]= c;
        }

        else if(c == '(')
        {
            while(peek(s) != ')')
            {
                revPrefix[j++] = peek(s);
                pop(&s);
            }
            pop(&s);
        }

        else if(c == ')')
        {
            push(&s, c);
        }

        else
        {
            while(!isEmptyStack(s) && peek(s)!= ')' && precedence(peek(s))> precedence(c))
            {
                revPrefix[j++] = peek(s);
                pop(&s);
            }
            push(&s, c);
        }
    }

    while(!isEmptyStack(s))
    {
        revPrefix[j++]=peek(s);
        pop(&s);
    }
    revPrefix[j]='\0';

    count = 0;

    while (revPrefix[count] != '\0')
    {
        count++;
    }

    end = count - 1;

    for (begin = 0; begin < count; begin++) {
      prefix[begin] = revPrefix[end];
      end--;
    }
   prefix[count] = '\0';

}

int precedence(char op)
{
    if(op == '*' || op == '/')
        return 1;
    else return 0;
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
