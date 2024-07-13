typedef struct QueueNodeType
{
	int                    numItems;      
	long                   checkOutTime; 
	struct QueueNodeType   *next;
}Customer;

typedef Customer	ItemType;

typedef struct
{
	int       Count;
	Customer  *Head;
	Customer  *Tail;
}Queue;

#ifndef FALSE
#define FALSE (0)
#endif

#ifndef TRUE
#define TRUE (!FALSE)
#endif

