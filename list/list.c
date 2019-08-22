#include<stdio.h>
#include<malloc.h>
#include"list.h"

static node_t *get_node(list_t *list,int index)
{
	node_t *node;
	int count = 1;

	if(list == NULL)
		return NULL;
	
	if(0 >= index || index > list->size)
	{
		printf("index must between 1 and %d \n",list->size);
		return NULL;
	}
	
	node = list->head->next;

	while(index > count++)
		node = node->next;

	return node;
}

list_t *c_list_create()
{
	list_t *list = NULL;

	list = (list_t *) malloc(sizeof(list_t));
	if(list == NULL)
	{
		printf("malloc list is null");
		return NULL;
	}

	list->head = (node_t *)malloc(sizeof(node_t));
	if(list->head == NULL)
	{
		printf("malloc list->head is null");
		free(list);
		return NULL;
	}

	list->head->next = NULL;
	list->size = 0;

	return list;
}

void c_list_destroy(list_t *list)
{
	node_t  *node;
	node_t  *next;
	if(list == NULL)
		return;

	node = list->head->next;
	if(node != NULL)
	{
		next = node->next;
		free(node);
		node = next;
	}
	
	free(list->head);
	free(list);
}

node_t *c_list_get_node(list_t *list,int index)
{
		return get_node(list,index);
}

int c_list_add_index(list_t *list,int value,int index)
{
	node_t *new;
	node_t *pre;
	node_t *next;
	if(list == NULL)
		return -1;

	if( index <= 0 || index > (list->size+1))
	{
		printf("index must between 1 and %d \n",list->size+1);
		return -1;
	}

	new = (node_t *)malloc(sizeof(node_t));
	if(new == NULL)
	{
		printf("malloc new node failed\n");
		return -1;
	}

	new->value = value;
	new->next = NULL;

	if(index == 1)
		pre = list->head;
	else
		pre = get_node(list,index-1);

	if(pre->next == NULL)
	{
		pre->next = new;
	}
	else
	{
		next = pre->next;
		pre->next = new;
		new->next = next;
	}

  list->size++;
	return 0;
}
int c_list_add(list_t *list,int value)
{
	return c_list_add_index(list,value,list->size+1);
}

int c_list_remove_index(list_t *list,int index)
{
	node_t *del = NULL;
	node_t *pre = NULL;
	node_t *next = NULL;


	if(index <= 0 || index >= list->size)
	{
		printf("index must between 1 and %d \n",list->size);
		return -1;
	}

	if(index == 1)
		pre = list->head->next;
	else
		pre = get_node(list,index-1);

	del = pre->next;
	if(del->next != NULL)
	{
		next = del->next;
		pre->next = next;
	}

	free(del);
	list->size--;
	return 0;	
}
int c_list_remove(list_t *list)
{
	return(list,list->size);
}



