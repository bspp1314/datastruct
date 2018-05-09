#ifndef LEFT_HEAP_H
#define LEFT_HEAP_H
typedef struct node{	
	void *value;
	void *key;
	struct node *left;
	struct node *right;
	struct node *parent;
	long npl;
}node_t;

typedef struct left_heap{
	long size;
	int (* compare)(const void *,const void *);
	node_t *root;
}left_heap_t;
left_heap_t* c_left_heap_create(int(*compare)(const void *,const void *));
void c_left_heap_destroy(left_heap_t *heap);
int c_left_heap_insert(left_heap_t *heap,void *key,void *value);
node_t *c_left_heap_next(node_t *node);
#endif
