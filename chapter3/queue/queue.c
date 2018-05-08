#include<stdio.h>
#include<malloc.h>
#include<assert.h>
#include"queue.h"

queue_t *c_queue_create()
{
	queue_t *queue = NULL;

	queue = (queue_t *) malloc(sizeof(queue_t));
	if(queue == NULL)
	{
		printf("malloc queue is null");
		return NULL;
	}

	queue->head = (node_t *)malloc(sizeof(node_t));
	if(queue->head == NULL)
	{
		printf("malloc queue->head is null");
		free(queue);
		return NULL;
	}

	queue->tail = (node_t *)malloc(sizeof(node_t));
	if(queue->tail == NULL)
	{
		printf("malloc queue->tail is null");
		free(queue->head);
		free(queue);
		return NULL;
	}

	queue->head->next = queue->tail;
	queue->head->pre = queue->tail;
	queue->tail->next = queue->head;
	queue->tail->pre = queue->head;

	return queue;
}

void c_queue_destroy(queue_t *queue)
{
	node_t  *node;
	node_t  *next;

	if(queue == NULL)
		return;
	
	node = queue->head->next;
	while(node != queue->tail)
	{
		next = node->next;
		free(node);
		node = next;
	}

	free(queue->head);
	free(queue->tail);
	free(queue);
}

/* 入队操作 */
int c_enqueue(queue_t *queue,int value)
{
	node_t *new;
	node_t *pre;
	node_t *next;

	if(queue == NULL)
		return -1;

	new = (node_t *)malloc(sizeof(node_t));
	if(new == NULL)
	{
		printf("malloc new node failed\n");
		return -1;
	}

	new->value = value;
	if(queue->head->next == queue->tail)
	{
		assert(queue->tail->pre == queue->head);
		pre = queue->head;
	}else
	{
		pre = queue->tail->pre;
	}

	new->pre = pre;
	pre->next = new;
	new->next = queue->tail;
	queue->tail->pre = new;
	queue->size++;

	return 0;
}

/* 出队操作*/
int c_dequeue(queue_t *queue)
{
	node_t *del = NULL;

	if(queue == NULL)
		return -1;

	if(queue->size == 0)
		return 0;

	del = queue->head->next;
	del->next->pre = queue->head;
	queue->head->next = del->next;

	queue->size--;

	return 0;
}
/* 获取队头节点 */
node_t *c_get_queue_front(queue_t *queue)
{
	if(queue == NULL || queue->size == 0)
		return NULL;
	return queue->head->next;
}

/* 获取队尾节点 */
node_t *c_get_queue_tail(queue_t *queue)
{
	if(queue == NULL || queue->size == 0)
		return NULL;
	return queue->tail->pre;
}


