#ifndef SKEW_HEAP_H
#define SKEW_HEAP_H
typedef struct node{	
	void *value;
	void *key;
	struct node *left;
	struct node *right;
	struct node *parent;
}node_t;

typedef struct c_skew_heap{
	long size;
	int (* compare)(const void *,const void *);
	node_t *root;
}c_skew_heap_t;

typedef struct c_skew_heap_iterator_s{
	c_skew_heap_t *heap;
	node_t *node;
}c_skew_heap_iterator_t;

void c_skew_heap_destroy(c_skew_heap_t *heap);
int c_skew_heap_insert(c_skew_heap_t *heap,void *key,void *value);
void c_skew_heap_remove(c_skew_heap_t *heap);
c_skew_heap_t* c_skew_heap_create(int(*compare)(const void *,const void *));

c_skew_heap_iterator_t *c_skew_heap_iter_create(c_skew_heap_t *heap); 
int c_skew_heap_iterator_next(c_skew_heap_iterator_t *iter,void **key, void **value); 
int c_skew_heap_iterator_pre(c_skew_heap_iterator_t *iter,void **key, void **value);

#endif
