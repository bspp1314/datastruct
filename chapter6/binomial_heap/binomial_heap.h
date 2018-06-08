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


#endif
