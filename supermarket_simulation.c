#include <stdio.h>
#include <time.h>
#include <stdlib.h>

typedef struct customer
{
    int serviceTime;
} Customer;

typedef struct node
{
    Customer customer;
    struct node *next;
} Node;

Node *head = NULL;
Node *tail = NULL;

void Enqueue(Customer customer)
{
    Node *node = (Node *) malloc(sizeof(Node));
    node->customer = customer;
    node->next = NULL;

    if (head == NULL) {
        head = node;
    } else {
        tail->next = node;
    }

    tail = node;
}

void Dequeue()
{
    Node *temp = head;
    head = temp->next;

    if (head == NULL) {
        tail == NULL;
    }

    free(temp);
}

int randomNumber()
{
    return (rand() % 4) + 1;
}

void main()
{
    time_t start, end;
    int line = 1, serviceTime = 0, nextService = 0;

    time(&start);
    time(&end);
    puts("Simulation start");
    do
    {
        if (serviceTime == 0) {
            Customer customer;
            customer.serviceTime = randomNumber() * 60;

            Enqueue(customer);

            printf("Customer %d served, next customer will be serve after %d minutes\n", line, customer.serviceTime / 60);
            nextService = customer.serviceTime;
        }
        serviceTime++;

        if (serviceTime == nextService) {
            Dequeue();

            printf("Customer %d finish\n", line);
            line++;
            serviceTime = 0;
        }

        sleep(1);
        time(&end);
    } while ((end - start) <= (10 * 60));

    puts("Simulation end");
    printf("Total customer arrive is %d", line);
}