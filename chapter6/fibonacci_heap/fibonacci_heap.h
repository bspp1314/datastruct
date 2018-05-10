#ifndef FIBONACCI_HEAP_H
#define FIBONACCI_HEAP_H
#include<stdint.h>
typedef struct fibonacci_node{
	int degree;
	uint8_t marked;//是否被删除第一孩子节点
	void *key;
	struct fibonacci_node *left;//左兄弟
	struct fibonacci_node *right;//右兄弟
	struct fibonacci_node *parent;//父节点
	struct fibonacci_node *child;//第一个孩子节点
}fibonacci_node_t;

typedef struct c_fibonacci_heap{
	int size;
	int max_degree;
	fibonacci_node_t *min_node;
	fibonacci_node_t **cons;
	int (* compare)(const void *,const void *);
}c_fibonacci_heap_t;

#endif
