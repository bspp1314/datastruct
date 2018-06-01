#ifndef _LIST_H
#define _LIST_H
typedef struct node{
	struct node *next;
	int value;
}node_t;

typedef struct list{
	node_t *head;
	int  size;
}list_t;

list_t *c_list_create();
void  c_list_destroy(list_t *list);
node_t *c_list_get_node(list_t *list,int index);
int c_list_add(list_t *list,int value);
int c_list_add_index(list_t *list,int value,int index);
int c_list_remove(list_t *list);
int c_list_remove_index(list_t *list,int index);



#endif
