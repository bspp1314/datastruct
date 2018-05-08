#include<stdio.h>
#include"double_list.h"

int main()
{
	double_list_t *list = c_double_list_create();
	node_t *node;

	if(list == NULL)
		return 0;

	for(int i = 0;i < 10;i++)
		c_double_list_add(list,i*2-1);

	for(int i = 1;i <= list->size;i++)
	{
		node = c_double_list_get_node(list,i);
		printf("=  %d  =",node->value);
	}
	printf("\n");
	c_double_list_destroy(list);
	return 0;
}

