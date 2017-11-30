#ifndef _BIN_HEAP_H
#define _BIN_HEAP_H
struct bin_heap
{
	int length;
	int size;
	int *values;
	int (*compare)(const void *,const void *);
};
typedef struct bin_heap PRI_QUEUE_S;

PRI_QUEUE_S *init_priority_queue(int length,int (*compare)(const void *,const void *));

#endif 
