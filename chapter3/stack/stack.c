#include<stdio.h>
#include<malloc.h>
#include<assert.h>
#include"stack.h"

stack_t *c_stack_create()
{
	stack_t *stack = NULL;

	stack = (stack_t *) malloc(sizeof(stack_t));
	if(stack == NULL)
	{
		printf("malloc stack is null");
		return NULL;
	}

	stack->head = (node_t *)malloc(sizeof(node_t));
	if(stack->head == NULL)
	{
		printf("malloc stack->head is null");
		free(stack);
		return NULL;
	}

	stack->tail = (node_t *)malloc(sizeof(node_t));
	if(stack->tail == NULL)
	{
		printf("malloc stack->tail is null");
		free(stack->head);
		free(stack);
		return NULL;
	}

	stack->head->next = stack->tail;
	stack->head->pre = stack->tail;
	stack->tail->next = stack->head;
	stack->tail->pre = stack->head;

	return stack;
}

void c_stack_destroy(stack_t *stack)
{
	node_t  *node;
	node_t  *next;

	if(stack == NULL)
		return;
	
	node = stack->head->next;
	while(node != stack->tail)
	{
		next = node->next;
		free(node);
		node = next;
	}

	free(stack->head);
	free(stack->tail);
	free(stack);
}

/*入栈操作 */
int c_stack_push(stack_t *stack,int value)
{
	node_t *new;
	node_t *pre;
	node_t *next;

	if(stack == NULL)
		return -1;

	new = (node_t *)malloc(sizeof(node_t));
	if(new == NULL)
	{
		printf("malloc new node failed\n");
		return -1;
	}

	new->value = value;

	pre = stack->head;
	next = pre->next;

	pre->next = new;
	new->pre = pre;
	new->next = next;
	next->pre = new;

	stack->size++;
	return 0;
}

/* 出栈操作*/
int c_stack_pop(stack_t *stack)
{
	node_t *del = NULL;

	if(stack == NULL)
		return -1;

	if(stack->size == 0)
		return 0;

	del = stack->head->next;
	del->next->pre = stack->head;
	stack->head->next = del->next;

	stack->size--;

	return 0;
}
/*栈顶元素*/
node_t *c_get_stack_front(stack_t *stack)
{
	if(stack == NULL || stack->size == 0)
		return NULL;
	return stack->head->next;
}

/*栈底元素*/
node_t *c_get_stack_tail(stack_t *stack)
{
	if(stack == NULL || stack->size == 0)
		return NULL;
	return stack->tail->pre;
}


