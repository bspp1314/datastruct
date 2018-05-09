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

typedef struct c_left_heap{
	long size;
	int (* compare)(const void *,const void *);
	node_t *root;
}c_left_heap_t;

typedef struct c_left_heap_iterator_s{
	c_left_heap_t *heap;
	node_t *node;
}c_left_heap_iterator_t;

void c_left_heap_destroy(c_left_heap_t *heap);
int c_left_heap_insert(c_left_heap_t *heap,void *key,void *value);
void c_left_heap_remove(c_left_heap_t *heap);
c_left_heap_t* c_left_heap_create(int(*compare)(const void *,const void *));

c_left_heap_iterator_t *c_left_heap_iter_create(c_left_heap_t *heap); 
int c_left_heap_iterator_next(c_left_heap_iterator_t *iter,void **key, void **value); 
int c_left_heap_iterator_pre(c_left_heap_iterator_t *iter,void **key, void **value);

#endif
