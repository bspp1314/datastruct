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

typedef struct c_avl_iterator_s
{
	c_avl_tree_t *tree;
	c_avl_node_t *node;
}c_avl_iterator_t;

c_avl_tree_t *c_avl_create(int(*compare)(const void *,const void *));
void c_avl_destroy(c_avl_tree_t *avl_tree);
int  c_avl_insert(c_avl_tree_t *avl_tree,void *key,void *value);
int  c_avl_remove(c_avl_tree_t *avl_tree,const *key,void **rkey,void **rvalue);
int  c_avl_get(c_avl_tree_t *avl_tree,const *key,void **rvalue);
int c_avl_pick(c_avl_tree_t *t, void **key, void **value);
int calc_height(c_avl_node_t *node);

#endif
