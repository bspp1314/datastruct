#include<stdlib.h>
#include"heap.h"
#include<string.h>
#include<malloc.h>
#include<time.h>
int compare(const void *a,const void *b){
	if( *((int*)a) == *((int *)b)  )
	{
		return 0;

	}else if(*((int*)a) < *((int *)b))
	{
		return -1;

	}else{
		return 1;
	}
	return 1;

}


static void print_heap(heap_t *heap,int start,int end)
{
		
}
int main(){

	heap_t *heap = c_heap_create(100,compare);
	if(heap == NULL)
		return -1;

	int p0 = -7;;
	int p1 = 10;
	int p2 = 5;
	int p3 = 20;
	int p4 = 33;
	int p5 = 44;
	int p6 = 19;
	int p7 = 78;
	int p8 = 34;
	int p9 = -2;

	c_heap_insert(heap,&p0,NULL);
	c_heap_insert(heap,&p1,NULL);
	c_heap_insert(heap,&p2,NULL);
	c_heap_insert(heap,&p3,NULL);
	c_heap_insert(heap,&p4,NULL);
	c_heap_insert(heap,&p5,NULL);
	c_heap_insert(heap,&p6,NULL);
	c_heap_insert(heap,&p7,NULL);
	c_heap_insert(heap,&p8,NULL);
	c_heap_insert(heap,&p9,NULL);


	for(int i = 0;i < heap->size;i++)
	{
		int *value =(int *) heap->nodes[i].key;
		printf("%d ",*value);
	}
	printf("\n");

	printf("\n===================================================================\n\n");
	printf("remove max value 78\n");
	c_heap_remove(heap,&p7,NULL,NULL);

	for(int i = 0;i < heap->size;i++)
	{
		int *value =(int *) heap->nodes[i].key;
		printf("%d ",*value);
	}

	printf("\n");

	c_heap_destroy(heap);
	return 0;

}
