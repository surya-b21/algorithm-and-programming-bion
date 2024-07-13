#include "QueueTypes.h"

void InitializeQueue(Queue *Q);
int EmptyQueue(Queue *Q);
void Enqueue(ItemType *X, Queue *Q);
int Dequeue(Queue *Q, ItemType *X);
