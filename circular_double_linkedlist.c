#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    struct node *prev;
    struct node *next;
} Node;

Node *head = NULL;

void print()
{
    Node *start = head;
    if (start == NULL) {
        printf("Linked List is empty\n");
    } else {
        puts("The circular double linked list is:");
        while (start != NULL) {
            printf("%d", start->data);
            start = start->next;

            if (start == head) break;
            printf("<=>");
        }
    }
}

void insert(int data)
{
    Node *node = (Node*) malloc(sizeof(Node));

    node->data = data;
    // if head is empty, set prev and next node point itself
    if (head == NULL) {
        node->next = node->prev = node;
        head = node;
    } else {
        Node *tail = head->prev;

        node->next = head;
        node->prev = tail;
        head->prev = node;
        tail->next = node;

        head = node;
    }
}

void delete()
{
    if (head == NULL) return;

    Node *newHead = head->next, *newTail = head->prev, *temp = head;

    if (newHead == newTail) {
        free(head);
        return;
    }

    newHead->prev = newTail;
    newTail->next = newHead;
    head = newHead;
    free(temp);
}

int main()
{
    int numbers[5] = {1,2,3,4,5};

    for (int i = 0; i < 5; i++)
    {
        insert(numbers[i]);
    }

    print();
    delete();
    printf("\n");
    print();
    
    return 0;
}