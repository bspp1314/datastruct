#ifndef BINOMIAL_HEAP
#define BINOMIAL_HEAP
typedef struct heap_node{
	void *key;
	int degree;
	struct heap_node *left; 
  struct heap_node *parent;
	struct heap_node *next;
}heap_node_t;

typedef struct c_binomial_heap{
	long size;
	int (* compare)(const void *,const void *);
	heap_node_t *root;
}c_binomial_heap_t;

c_binomial_heap_t* c_binomial_heap_create(int(*compare)(const void *,const void *));
void c_binomial_heap_destroy(c_binomial_heap_t *heap);
c_binomial_heap_t *c_binomial_heap_union(c_binomial_heap_t *heap1,c_binomial_heap_t *heap2);
int c_binomial_heap_insert(c_binomial_heap_t *heap,void *key);
void  c_binomial_heap_delete(c_binomial_heap_t *heap,void **rkey);
heap_node_t *c_binomial_min(c_binomial_heap_t *heap);

#endif
