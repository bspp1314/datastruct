#ifndef _LIST_H
#define _LIST_H
typedef struct node{
	struct node *next;
	struct node *pre;
	int value;
}node_t;

typedef struct stack{
	node_t *head;
	node_t *tail;
	int size;
}stack_t;

stack_t *c_stack_create();
void  c_stack_destroy(stack_t *stack);
int c_stack_push(stack_t *stack,int value);
int c_stack_pop(stack_t *stack);
node_t *c_get_stack_front(stack_t *stack);
node_t *c_get_stack_tail(stack_t *stack);



#endif
