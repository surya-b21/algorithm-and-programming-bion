#include <stdio.h>

typedef struct node {
    int data;
    struct node *next;
} Node;

Node *head = NULL;

void printLinkedList()
{
    Node *start = head;
    if (start == NULL) {
        printf("Linked List is empty");
    } else {
        puts("The queue is:");
        while (start != NULL) {
            printf("%d-->", start->data);
            start = start->next;
        }
        puts("NULL\n");
    }
}

void insert(int data)
{
    Node *lk = (Node*) malloc(sizeof(Node));
    lk->data = data;
    lk->next = head;

    head = lk;
}

void insertAfterNode(Node *before, int data)
{
    Node *lk = (Node*) malloc(sizeof(Node));
    lk->data = data;
    lk->next = NULL;
    
    if (before->next != NULL)
    {
        lk->next = before->next;
    }

    before->next = lk;
}

Node* searchNode(Node *node, int data)
{
    if (node == NULL) {
        return NULL;
    }

    if (node->data == data) {
        return node;
    }

    return searchNode(node->next, data);
}

void deleteNode(int data)
{
    Node *start = head, *prev;
    if (start != NULL && start->data == data) {
        head = start->next;
        return;
    }

    while (start != NULL && start->data != data) {
        prev = start;
        start = start->next;
    }

    if (start == NULL) {
        printf("Linked List is empty");
        return;
    }

    prev->next = start->next;
    free(start);
}

void main()
{
    int choice;
    puts("1. Insert node; 2. Insert node after value; 3. Remove value; 4. End");
    scanf("%d", &choice);

    while (choice != 4)
    {
        int value, nodeValue;
        switch (choice)
        {
        case 1:
            printf("Insert a number : ");
            scanf("%d", &value);
            insert(value);
            printLinkedList();
            break;
        
        case 2:
            printf("Insert a number : ");
            scanf("%d", &value);
            printf("Insert a number in node : ");
            scanf("%d", &nodeValue);
            printf("%d \n", head->data);
            
            // find node
            Node *node = searchNode(head, nodeValue);
            insertAfterNode(node, value);

            printLinkedList();
            break;

        case 3:
            printf("Insert a number : ");
            scanf("%d", &value);
            deleteNode(value);
            printLinkedList();

            break;
        default:
            puts("Invalid choice");
            break;
        }

        printf("Insert your choice ?");
        scanf("%d", &choice);
    }
}