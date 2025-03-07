#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    struct node *next;
} Node;

Node *top = NULL;

void push(int data) 
{
    Node *newNode = (Node*) malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = top;

    top = newNode;
}

// Remove head because stack order is LIFO
void pop()
{
    if (top == NULL) {
        printf("Stack is empty");
        return;
    }
    Node *topTemp = top->next;

    top = topTemp;
}

void printStack()
{
    Node *start = top;
    if (start == NULL)
    {
        printf("Linked List is empty");
        return;
    }

    puts("The stack is:");
    while (start != NULL)
    {
        printf("%d-->", start->data);
        start = start->next;
    }
    puts("NULL\n");
}

int main()
{
    int numbers[5] = {1,2,3,4,5};

    for (int i = 0; i < 5; i++)
    {
        push(numbers[i]);
    }
    printStack();
    printf("Do delete stack\n");
    pop();
    printStack();

    return 0;
}