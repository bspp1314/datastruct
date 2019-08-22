#ifndef _LIST_H
#define _LIST_H
typedef struct node{
	struct node *next;
	struct node *pre;
	int value;
}node_t;

typedef struct queue{
	node_t *head;
	node_t *tail;
	int size;
}queue_t;

queue_t *c_queue_create();
void  c_queue_destroy(queue_t *queue);
int c_enqueue(queue_t *queue,int value);
int c_dequeue(queue_t *queue);
node_t *c_get_queue_front(queue_t *queue);
node_t *c_get_queue_tail(queue_t *queue);



#endif
