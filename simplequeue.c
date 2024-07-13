#include <stdio.h>
#include <stdlib.h>

struct queueNode {
    char data;
    struct queueNode *nextPtr;
};

typedef struct queueNode QueueNode;
typedef QueueNode *QueueNodePtr;

void printQueue(QueueNodePtr currentPtr);
int isEmpty(QueueNodePtr headPtr);
char dequeue(QueueNodePtr *headPtr, QueueNodePtr *tailPtr);
void enqueue(QueueNodePtr *headPtr, QueueNodePtr *tailPtr, char value);

int main(void) {
    QueueNodePtr headPtr = NULL;
    QueueNodePtr tailPtr = NULL;
    char item;

    printf("Enter: \n"
            "   1: add an item\n"
            "   2: remove an item\n"
            "   3: end\n");
    printf("%s", "? ");
    unsigned int choice;
    scanf("%u", &choice);

    while (choice != 3) {
        switch (choice) {
            case 1:
                printf("%s", "Enter a character: ");
                scanf("\n%c", &item);
                enqueue(&headPtr, &tailPtr, item);
                printQueue(headPtr);
                break;
            case 2:
                if (!isEmpty(headPtr)) {
                    item = dequeue(&headPtr, &tailPtr);
                    printf("%c has been removed.\n", item);
                }
                printQueue(headPtr);
                break;
            default:
                puts("Invalid choice.\n");
                break;
        }

        printf("%s", "? ");
        scanf("%u", &choice);
    }

    puts("End of run.");
}

void enqueue(QueueNodePtr *headPtr, QueueNodePtr *tailPtr, char value) {
    QueueNodePtr newPtr = malloc(sizeof(QueueNode));
    if (newPtr != NULL) { // is space available? 
        newPtr->data = value;
        newPtr->nextPtr = NULL;
        // if empty, insert node at head
        if (isEmpty(*headPtr)) { 
            *headPtr = newPtr;
        }
        else {
            (*tailPtr)->nextPtr = newPtr;
        }

        *tailPtr = newPtr;
    }
    else {
        printf("%c not inserted. No memory available.\n", value);
    } 
}

char dequeue(QueueNodePtr *headPtr, QueueNodePtr *tailPtr) {
    char value = (*headPtr)->data;
    QueueNodePtr tempPtr = *headPtr;
    *headPtr = (*headPtr)->nextPtr;

    if (*headPtr==NULL) {
        *tailPtr = NULL;
    }

    free(tempPtr);
    return value;
}

int isEmpty(QueueNodePtr headPtr) {
    return headPtr==NULL;
}

void printQueue(QueueNodePtr currentPtr) {
    if (currentPtr==NULL) {
        puts("Queue is empty.\n");
    }
    else {
        puts("The queue is:");
        while (currentPtr != NULL) {
            printf("%c-->", currentPtr->data);
            currentPtr = currentPtr->nextPtr;
        }
        puts("NULL\n");
    }
}
