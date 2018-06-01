#include<stdio.h>
#include"list.h"

int main()
{
	list_t *list = NULL;
	node_t *node = NULL;

	list = c_list_create();
	if(list == NULL)
		return -1;

	for(int i = 0;i < 10;i++)
		c_list_add(list,i*2-1);

	for(int i = 1;i <= list->size;i++)
	{
		node = c_list_get_node(list,i);
		if(node != NULL)
			printf("value is %d \n",node->value);
	}

	for(int i = 5;i <= list->size;i++)
		c_list_remove_index(list,i);

	for(int i = 1;i <= list->size;i++)
	{
		if(node != NULL)
			node = c_list_get_node(list,i);
		printf("value is %d \n",node->value);
	}

	c_list_destroy(list);
	
	return 0;
}

