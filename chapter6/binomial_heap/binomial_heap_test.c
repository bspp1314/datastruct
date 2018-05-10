#include<stdio.h>
#include<stdlib.h>
#include"binomial_heap.h"
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

int main()
{
	printf("%d\n",(1154 % 10));
	c_binomial_heap_t *heap = NULL;

	heap = c_binomial_heap_create(compare);
	if(heap == NULL)
		return 0;

	for(int i = 0;i < 1000;i++)
	{
		int *p = (int *)malloc(sizeof(int));
		*p = rand() % 10;
		c_binomial_heap_insert(heap,p);
	}

	int i  = 0;
	while(heap->size)
	{
		int *p = NULL;
		c_binomial_heap_delete(heap,(void **)&p);
		if(p != NULL)
		{
			printf(" %d ",*p);
			free(p);
		}	
		if((i + 1) % 10 == 0)
			printf("\n");
		i++;
	}

	c_binomial_heap_destroy(heap);
}
