#include "QueueTypes.h"
#include <stdio.h>
#include <stdlib.h>

void InitializeQueue(Queue *Q)
{
	Q->Count = 0;
	Q->Head = NULL;
	Q->Tail = NULL;
}

int EmptyQueue(Queue *Q)
{
	return(Q->Count == 0);
	/* or return(Q->Head == NULL); */
}

void Enqueue(ItemType *X, Queue *Q)
{
	if(Q->Head == NULL) /* Insert as first node in queue */
		Q->Head = Q->Tail = X;
	else  /* Insert at end of queue */
	{
		(Q->Tail)->next = X;
		Q->Tail = X;
	}
	Q->Count++;
}

int Dequeue(Queue *Q, ItemType *X)
{
	Customer *temp;

	if(!EmptyQueue(Q))
	{
		temp = Q->Head;		/* Save to free the removed node */
		*X = *(Q->Head);	/* Copy entire structure */
		Q->Head = (Q->Head)->next;
		Q->Count--;
		if(Q->Head == NULL) Q->Tail = NULL;	/* Fix tail if Dequeuing last node */
		free(temp);
		return TRUE;
	}
	else
		return FALSE;	/* Flag nothing was dequeued */
}
