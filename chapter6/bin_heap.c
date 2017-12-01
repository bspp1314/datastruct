/**
 *		使用二叉堆（binary heap）实优先队列
 * （1）堆是一颗完全被填满的二叉树，有可能的例外是在底层，底层上的数字从左往右填入，也称
 * 完成二叉树（complete binary tree）
 * （2）一颗完全二叉树可以用数组实现,对于数组中的任意位置i,左子树为2i,右子树为2i+1，父节点为 (i/2)向下取整。
 * （3）堆序：在任意一个堆中，任意一个节点X，其父节点都大于X/.
 ********************************************************************************/

#include<stdio.h>
#include<malloc.h>
#include<limits.h>

#include"bin_heap.h"
int compare(int *a,int *b)
{
	if(*a == *b)
		return 0;
	else if(*a > *b)
		return 1;
	else
		return -1;
}
PRI_QUEUE_S *priority_queue_init(int length,int (*compare)(const void *,const void *))
{
	PRI_QUEUE_S *queue = NULL;

	if(length < 1)
	{
		printf("priority queue length must big 1 \n");
		return NULL;
	}

	if(compare == NULL)
	{
		printf("compare funtion must not be null.\n");
	}

	queue = malloc(sizeof(PRI_QUEUE_S));
	if(queue == NULL)
	{
		printf("Out of space .\n");
		return NULL;
	}

	/* Allocate the array plus one extra for sentinel(哨兵标记) */
	queue->values = malloc(sizeof(int) * (length+1));
	if(queue->values == NULL)
	{
		free(queue);
		printf("Out of space.\n");
		return NULL;
	}

	queue->compare = compare;
	queue->length = length;
	queue->size = 0;
	queue->values[0] = INT_MIN;

	return queue;

}
int  *priority_queue_build(PRI_QUEUE_S *queue,int values[],int value_len)
{
	if(queue == NULL)
	{
		printf("queue not be null");
		return -1;
	}

	if(queue->size != 0)
	{
		printf("queue size must be null");
		return -1;
	}

	if(value_len > queue->length)
	{
		printf("queue max length is %d ,but values len is %d",queue->length,value_len);
		return -1;
	}

	

}
int priority_queue_insert(int value,PRI_QUEUE_S *queue)
{
	int i = 0;

  if(queue->length == queue->size)
	{
		printf("Priority queue is full \n");
		return -1;
	}

	for(i = ++queue->size;compare(&queue->values[i/2],&value) > 0;i = i / 2)
	{
		queue->values[i] = queue->values[i/2];
	}

  queue->values[i] = value;

	 return 0;
}
int priority_queue_delete_min(PRI_QUEUE_S *queue)
{
	int i = 0;
	int child = 0;
	int min_value = 0;
	int last_value = 0;

	if(0 == queue->size)
	{
		printf("Priority queue is empty .\n");
		return queue->values[0];
	}

	min_value = queue->values[1];
	last_value = queue->values[queue->size--];

	for(i = 1; i * 2 <= queue->size; i = child)
	{
		child = i * 2;
	  if(child != queue->size && queue->values[child+1] < queue->values[child])
			child;

		/* Percolate one level */

		if(last_value > queue->values[child])
			queue->values[i] = queue->values[child];
		else
			break;
	}		
	
	queue->values[i] = last_value;
	return min_value;
}
int priority_queue_find_min(PRI_QUEUE_S *queue)
{
	if(queue == NULL)
	{
		printf("queue is muset not be null");
		return INT_MIN;
	}

	if(queue->size == 0)
	{
		printf("queue size is 0 \n");
		return INT_MIN;
	}

	return queue->values[i];
}
void priority_queue_destroy(PRI_QUEUE_S *queue)
{
	if(NULL == queue)
		return;

	free(queue->values);
	queue->values = NULL;
	free(queue);
	queue = NULL:
}

int main(void)
{
	PRI_QUEUE_S *queue = priority_queue_init(10,(int(*)(const void *,const void *))compare);
	priority_queue_insert(10,queue);
	priority_queue_insert(16,queue);
	priority_queue_insert(9,queue);
	priority_queue_insert(99,queue);
	priority_queue_destroy(queue);
}
