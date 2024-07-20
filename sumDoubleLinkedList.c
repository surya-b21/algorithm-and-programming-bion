#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
   int data;
   struct node *prev;
   struct node *next;
} Node;

Node *head = NULL;
Node *tail = NULL;

void Insert(int data)
{
    Node *node = (Node*) malloc(sizeof(Node));

    node->data = data;
    if (head == NULL) {
        head = node;
    } else {
        tail->next = node;
    }

    Node *temp = tail;
    tail = node;
    tail->prev = temp;
}

void Delete()
{
    if (head == NULL && tail == NULL) return;
    Node *temp = tail;

    if (temp->prev != NULL) {
        tail = temp->prev;
        tail->next = NULL;
    } else {
        head = NULL;
        tail = NULL;
    }

    free(temp);
}

void Print()
{
    Node *start = head;
    if (start == NULL) {
        printf("Linked List is empty\n");
    } else {
        puts("The queue is:");
        printf("NULL<=>");
        while (start != NULL) {
            printf("%d<=>", start->data);
            start = start->next;
        }
        puts("NULL\n");
    }
}

void FindingMatch(int number)
{
    if (head == NULL && tail == NULL)  {
        Print();
        return;
    }

    Node *start = head;
    while (start != NULL)
    {
        Node *current = start;
        while (current != NULL)
        {
            if ((start->data + current->data) == number && start->data != current->data) {
                printf("%d, %d\n", start->data, current->data);
                break;
            }

            current = current->next;
        }
        
        start = start->next;
    }
    
}

void main()
{
    int choice;
    puts("1. Insert node; 2. Delete node; 3. Find match pair; 4. End");
    scanf("%d", &choice);

    do
    {
       int value;
       switch (choice)
       {
       case 1:
        printf("Insert a number : ");
        scanf("%d", &value);
        Insert(value);
        Print();

        break;

        case 2:
        Delete();
        Print();

        break;

        case 3:
        printf("Insert a number : ");
        scanf("%d", &value);
        FindingMatch(value);

        break;
       
       default:
            puts("Invalid choice");
            break;
       }

        printf("Insert your choice ?");
        scanf("%d", &choice);
    } while (choice != 4);
    
}