#ifndef AVL_TREE
#define AVL_TREE

typedef struct c_avl_node_s
{
	void *key;
	void *value;
	int  height;//where is the node 
	
	struct c_avl_node_s *left;
	struct c_avl_node_s *right;
	struct c_avl_node_s *parent;
}c_avl_node_t;

typedef struct c_avl_tree_s
{
	c_avl_node_t *root;
	int size;
	int (* compare)(const void *,const void *);
}c_avl_tree_t;

c_avl_tree_t *c_avl_create(int(*compare)(const void *,const void *));


#endif
