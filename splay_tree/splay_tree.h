#ifndef SPLAY_TREE
#define SPLAY_TREE

typedef struct c_splay_node_s
{
	void *value;
	void *key;
	struct c_splay_node_s *left;
	struct c_splay_node_s *right;
	struct c_splay_node_s *parent;
}c_splay_node_t;

typedef struct c_splay_tree_s
{
	c_splay_node_t *root;
	int size;
	int (* compare)(const void *,const void *);	
}c_splay_tree_t;

#endif
