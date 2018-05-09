#ifndef BINOMIAL_HEAP
#define BINOMIAL_HEAP
typedef struct binomial_heap{
	void *key;
	int degree;
	struct binomial_heap *left // parent 
  struct binomial_heap *parent;
	struct binomial_heap *next;
}binomial_heap_t;
#endif
