#ifndef _LIST_H
#define _LIST_H
typedef struct node{
	struct node *next;
	struct node *pre;
	int value;
}node_t;

typedef struct double_list{
	node_t *head;
	node_t *tail;
	int size;
}double_list_t;

double_list_t *c_double_list_create();
void  c_double_list_destroy(double_list_t *double_list);
node_t *c_double_list_get_node(double_list_t *double_list,int index);
int c_double_list_add(double_list_t *double_list,int value);
int c_double_list_add_index(double_list_t *double_list,int value,int index);
int c_double_list_remove(double_list_t *double_list);
int c_double_list_remove_index(double_list_t *double_list,int index);



#endif
