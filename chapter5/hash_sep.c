/**
 *
 * 分离链接法解决HASH冲突
 *
 * *******************************************************************************************************************/

#include<stdio.h>
#include<malloc.h>
#include<string.h>

#include"hash_sep.h"
LIST_S *list_create(int (*compare)(const void *,const void *))
{
	LIST_S *list = NULL;

	if(compare == NULL)
	{
		printf("compare function not be null");
		return NULL;
	}

	list = (LIST_S *)malloc(sizeof(LIST_S));
	if(list == NULL)
	{
		printf("Out of space .\n");
		return NULL;
	}

	list->len = 0;
	list->compare = compare;
	list->first = NULL;

	return list;
}
void list_node_free(LIST_NODE_S *list_node)
{
	LIST_NODE_S *p = NULL;

	p = list_node;
	while(list_node != NULL)
	{
		list_node = p->next;
		free(p);
	}
}

void lists_free(LIST_S **lists,int num)
{
	if(lists == NULL)
		return;

	for(int i = 0;i < num ;i++){
		if(lists[i] != NULL)
		{
			list_node_free(lists[i]->first);
			free(lists[i]);	
		}
	}
	
	free(lists);
}/*void lists_free*/

HASH_TABLE_S *init_hash_table(int table_size,int (*compare)(const void *,const void *),
		long(*hash_fun)(const void *,int table_size))
{
	HASH_TABLE_S *hash_table = NULL;
	int i = 0;

	if(table_size < MIN_TABLE_SIZE)
	{
		printf("Table size too size .\n");
		return NULL;
	}

	if(compare == NULL)
	{
		printf("compare function not be null");
		return NULL;
	}

	if(hash_fun == NULL)
	{
		printf("hash_fun not be null");
		return NULL;
	}


	hash_table = (HASH_TABLE_S *)malloc(sizeof(HASH_TABLE_S));
	if(hash_table == NULL)
	{
		printf("Out of space .\n");
		return NULL;
	}

	hash_table->table_size = table_size;
	hash_table->hash_fun = hash_fun;
	hash_table->lists = malloc(sizeof(LIST_S) * table_size);
	if(hash_table->lists == NULL)
	{
		free(hash_table);
		printf("Out of space .\n");
		return NULL;
	}

	for(int i = 0;i < table_size;i++)
	{
		hash_table->lists[i] = list_create(compare);
		if(hash_table->lists[i] == NULL)
		{
			lists_free(hash_table->lists,i);
			free(hash_table);
			return NULL;
		}
	}

	return hash_table;
}
LIST_NODE_S *hash_find(const void *key,HASH_TABLE_S *hash_table)
{
	LIST_S *list = NULL;
	long hash_val = 0;
	LIST_NODE_S *list_node = NULL;
	
	hash_val = hash_table->hash_fun(key,hash_table->table_size);
	list = hash_table->lists[hash_val];

	list_node = list->first;
	while(list_node != NULL)
	{
		if(list->compare(key,list_node->key) == 0)
			break;

		list_node = list_node->next;
	}
	
	return list_node;
}
void hash_insert(void *key,void *value,HASH_TABLE_S *hash_table)
{
	LIST_S *list = NULL;
	long hash_val = 0;
	LIST_NODE_S *list_node = NULL;
	int status;

	hash_val = hash_table->hash_fun(key,hash_table->table_size);
	list = hash_table->lists[hash_val];
	list_node = list->first;
	
	while(list_node != NULL)
	{
		if(list->compare(list_node->key,key) == 0)
			return ;
		else
			list_node = list_node->next;
	}

	list_node = malloc(sizeof(LIST_NODE_S));
	if(list_node == NULL)
	{
		printf("Out of space .\n");
		return;
	}

	list_node->key = key;
	list_node->value = value;
	list_node->next = NULL;

	if(list->len == 0)
		list->first = list_node;
	list->len++;
}



int main(void)
{
	//LIST_S **lists = malloc(sizeof(LIST_S) * 3);
	//lists[0] = list_create((int(*)(const void *,const void *))strcmp);
	//lists[1] = list_create((int(*)(const void *,const void *))strcmp);
	//lists[2] = list_create((int(*)(const void *,const void *))strcmp);
	//lists_free(lists,3);
	return -1;
}
