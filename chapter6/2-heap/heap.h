#ifndef HEAP_H
#define HEAP
typedef struct node{	
	void *value;
	void *key;
}node_t;

typedef struct heap{
	int capacity;
	int size;/*实际大小*/
	int (* compare)(const void *,const void *);
	node_t *nodes;
}heap_t;
heap_t *c_heap_create(int capacity,int (*compare)(const void *,const void *));
void *c_heap_destroy(heap_t *heap);
int c_heap_insert(heap_t *heap,void *key,void *value);
int c_heap_remove(heap_t *heap,void *key,void **rkey,void **rvalue);
#endif
