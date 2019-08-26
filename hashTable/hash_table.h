#ifndef HASH_SEP_H
#define HASH_SEP_H

#define MIN_TABLE_SIZE 10
struct list_node
{
	void *key;
	void *value;
	struct list_node *next;
};
typedef struct list_node LIST_NODE_S;

struct list
{
	int len;
	int (*compare)(const void *, const void *);
	LIST_NODE_S *first;
};
typedef struct list LIST_S;

struct hash_table
{
	int table_size;
	LIST_S **lists;
	long (*hash_fun)(const void *key,int table_size);
};
typedef struct hash_table HASH_TABLE_S;
LIST_S *list_create(int (*compare)(const void *,const void *));
#endif
