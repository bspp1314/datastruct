#include<stdio.h>
#include"queue.h"

int main()
{
	queue_t *queue = c_queue_create();
	node_t *node;

	if(queue == NULL)
		return 0;

	for(int i = 0;i < 10;i++)
		c_enqueue(queue,i*2-1);/*入队*/
  node = c_get_queue_front(queue);
	while(node != queue->tail){
		printf("%d ",node->value);
		node = node->next;
	}
	printf("\n");
	printf("\n===========================================================\n\n");

	node = c_get_queue_front(queue);	
	printf("The front of queue value is :%d \n",node->value);
	node = c_get_queue_tail(queue);
	printf("The tail of queue value is :%d \n",node->value);
	printf("\n===========================================================\n\n");

	printf("enqueue value %d\n",100);
	c_enqueue(queue,100);
	printf("dequeue\n");
	c_dequeue(queue);
	printf("\n===========================================================\n\n");

	node = c_get_queue_front(queue);	
	printf("The front of queue value is :%d \n",node->value);
	node = c_get_queue_tail(queue);
	printf("The tail of queue value is :%d \n",node->value);
	c_queue_destroy(queue);
	return 0;
}

