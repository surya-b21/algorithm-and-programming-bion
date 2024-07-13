#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "QueueInterface.h"


#define RandomArrivalAvg   120       /* Customer arrives approx. every x seconds */
#define ItemTime           1.75
#define StartUpTime        5.0
#define CloseOutTime       76.8

void AddCustomer(Queue *Q);

int main(void)
{
	Queue    theQueue;
	time_t   simStartTime;     /* System time when simulation is begun */
	time_t   simEndTime;       /* System time when simulation is to end */
	time_t   simTime;          /* Current time in the simulation */
	time_t   holdTime;         /* Holder to mark simTime change */
	time_t   plus3RunningTot;  /* Total time there has been more then 3 customers in line */
	time_t   plus3Current;     /* Current time there has been more then 3 customers */
	time_t   checkOutEndTime;  /* Time when the current customer will be finished checking out */
	time_t   addCustomerTime;  /* Time when a new customer is added to the line */
	int      recording = FALSE;/* Boolean flag.  Is time recording for >3 in queue? */
	Customer dummy;            /* Holder for structure Dequeue() returns */


	InitializeQueue(&theQueue);
	srand((unsigned)time(NULL));

	printf("\n\nEnter total running time in minutes.\n");
	scanf("%d", &simEndTime);
	AddCustomer(&theQueue); 
	time(&simStartTime); 

	simTime = simStartTime;
	simEndTime = ((simEndTime * 60) + simStartTime);
	checkOutEndTime = simTime + (theQueue.Head)->checkOutTime;
	plus3RunningTot = 0;
	addCustomerTime = simTime + (rand() % RandomArrivalAvg); /* Set time to add the next customer */
	holdTime = 0;

	/* Main Simulation Loop */
	do
	{
		time(&simTime); 
		if(holdTime < simTime)
		{
			printf("\n\nSim Time = %d:%d (min:sec).\n",
				(simTime - simStartTime) / 60,
				(simTime - simStartTime) % 60);
			printf("Customers in line = %d", theQueue.Count);
			holdTime = simTime;
		}
			
		if((checkOutEndTime <= simTime) && (checkOutEndTime != 0)) 
		{   /* new customer check out, remove customer finished check out */
			Dequeue(&theQueue, &dummy); 
			printf("\n\nCustomer checked out and leaving store.\n");
			/* check to see if any more customers are still in line */
			if(theQueue.Head != NULL)
				/* if still a customer in line calc. the time when he will be checked out */
				checkOutEndTime = simTime + (theQueue.Head)->checkOutTime;	 
			else
				checkOutEndTime = 0;
		}
		/* check number in the queue and recording of time for > 3 in queue */
		if(theQueue.Count > 3)
		{
			if(!recording)
			{
				recording = TRUE;
				plus3Current = simTime;
			}
		}
		else
		{
			if(recording)
			{
				recording = FALSE;
				plus3RunningTot += (simTime - plus3Current);
			}
		}
		/* check for time to add a new customer to the queue */
		if(addCustomerTime <= simTime) 
		{
			AddCustomer(&theQueue);
			addCustomerTime = simTime + (rand() % RandomArrivalAvg);
			printf("\n\nNew customer arriving in line.\n");
		}
	}
	while(simTime < simEndTime);

	if(recording) /* add in any remaining time with more than 3 customers in line */
		plus3RunningTot += (simTime - plus3Current);

	printf("\n\nResults from simulation:\n");
	printf("Total simulation time = %d:%d (min:sec)\n", 
		(simEndTime - simStartTime) / 60,
		(simEndTime - simStartTime) % 60);
	printf("Total time more then 3 customers in line = %d:%d (min:sec)\n", 
		plus3RunningTot / 60,
		plus3RunningTot % 60);
	printf("Number of customers left in line at end of simulation = %d\n", theQueue.Count);
	printf("-----End Simulation Run-----\n\n");
	return(0);
}


void AddCustomer(Queue *Q)
{
	Customer *newCustomer;

	newCustomer = (Customer *)malloc(sizeof(Customer));
	newCustomer->numItems = (rand() % 25) + 5; /* Set to 5..30 items */
	newCustomer->checkOutTime = (long)ceil(StartUpTime + (newCustomer->numItems * ItemTime) +
									   CloseOutTime);
	Enqueue(newCustomer, Q);
}	

