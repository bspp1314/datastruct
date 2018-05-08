#include<stdio.h>
#include"stack.h"

int main()
{
	stack_t *stack = c_stack_create();
	node_t *node;

	if(stack == NULL)
		return 0;

	for(int i = 0;i < 10;i++)
		c_stack_push(stack,i*2-1);

  node = c_get_stack_front(stack);
	while(node != stack->tail){
		printf("%d ",node->value);
		node = node->next;
	}
	printf("\n");
	printf("\n===========================================================\n\n");

	node = c_get_stack_front(stack);	
	printf("The front of stack value is :%d \n",node->value);
	node = c_get_stack_tail(stack);
	printf("The tail of stack value is :%d \n",node->value);

	printf("\n===========================================================\n\n");
	printf("enstack value %d\n",100);
	c_stack_push(stack,100);
  node = c_get_stack_front(stack);
	while(node != stack->tail){
		printf("%d ",node->value);
		node = node->next;
	}
	printf("\n");
	printf("\n===========================================================\n\n");

	printf("destack\n");
	c_stack_pop(stack);
  node = c_get_stack_front(stack);
	while(node != stack->tail){
		printf("%d ",node->value);
		node = node->next;
	}
	printf("\n");

	printf("\n===========================================================\n\n");
	node = c_get_stack_front(stack);	
	printf("The front of stack value is :%d \n",node->value);
	node = c_get_stack_tail(stack);
	printf("The tail of stack value is :%d \n",node->value);
	c_stack_destroy(stack);
	return 0;
}

