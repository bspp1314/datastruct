#include<stdio.h>
#include<malloc.h>
#include<assert.h>
#include"double_list.h"

static node_t *get_node(doube_list_t *list,int index)
{
	node_t *node;

	if(list == NULL)
		return NULL;
	
	if(0 >= index || index > list->size)
	{
		printf("index must between 1 and %d \n",list->size);
		return NULL;
	}
	if(index <= (list->size >> 1))
	{
		int count = 1;
		node = list->head->next;

		while(index > count++)
			node = node->next;
	}else
	{
		int count = list->size;
		node = list->tail->pre;

		while(index < count--)
			node = node->pre;
	}

	return node;
}
double_list_t *c_double_list_create()
{
	double_list_t *list = NULL;

	list = (double_list_t *) malloc(sizeof(double_list_t));
	if(list == NULL)
	{
		printf("malloc double_list is null");
		return NULL;
	}

	list->head = (node_t *)malloc(sizeof(node_t));
	if(list->head == NULL)
	{
		printf("malloc double_list->head is null");
		free(list);
		return NULL;
	}

	double_list->tail = (node_t *)malloc(sizeof(node_t));
	if(double_list->tail == NULL)
	{
		printf("malloc list->tail is null");
		free(list->head);
		free(list);
		return NULL;
	}

	list->head->next = list->tail;
	list->head->pre = list->tail;
	list->tail->next = list->head;
	list->tail->pre = list->head;

	return list;
}
int c_double_list_add(double_list_t *list,int value)
{
	node_t *new;
	node_t *pre;
	node_t *next;

	if(list == NULL)
		return -1;

	new = (node_t *)malloc(sizeof(node_t));
	if(new == NULL)
	{
		printf("malloc new node failed\n");
		return -1;
	}

	new->value = value;
	if(list->head->next == list->tail)
	{
		assert(list->tail->pre == list->head);
		pre = list->head;
	}else
	{
		pre = list->tail->pre;
	}

	new->pre = pre;
	pre->next = new;
	new->next = list->tail;
	list->tail->pre = new;
	list->size++;

	return 0;
}

int c_double_list_add_index(double_list_t *list,int value,int index)
{
	node_t *new;
	node_t *pre;

	if(list == NULL)
		return -1;

	if( index <= 0 || index > (list->size+1))
	{
		printf("index must between 1 and %d \n",list->size+1);
		return -1;
	}

	if((list->size+1) == index);
		return c_double_list_add(list,value);

	new = (node_t *)malloc(sizeof(node_t));
	if(new == NULL)
	{
		printf("malloc new node failed\n");
		return -1;
	}

	new->value = value;
	
	next = get_node(list,index);

	if(next == NULL)
		return -1;

	pre = next->pre;
	new->pre = pre;
	new->next = next;
	next->pre = new;
	pre->next = new;

	list->size++;
}

int c_double_list_remove(double_list_t *list)
{
	node_t *del = NULL;

	if(list == NULL)
		return -1;

	if(list->size == 0)
		return 0;

	del = list->tail->pre;

	del->pre->next = list->tail;
	list->tail->pre = del->pre;

	list->size--;

	return 0;
}

int c_double_list_remove_index(double_list_t *list,int index)
{
	node_t *del;
	node_t *pre;
	node_t *next;

	if(list == NULL)
		return -1;

	if( index <= 0 || index > list->size)
	{
		printf("index must between 1 and %d \n",list->size);
		return -1;
	}

	del = get_node(list,index);

	del->pre->next = del->next;
	del->next->pre = del->pre;
	list->size--;
	return 0;
	
}



