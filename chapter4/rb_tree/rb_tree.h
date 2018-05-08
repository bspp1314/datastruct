#ifndef RB_TREE
#define RB_TREE

typedef enum { 
	RED = 0, 
	BLACK = 1
}color_t;

typedef struct c_rb_node_s
{
	void *key;
	void *value;
	color_t color;
	
	struct c_rb_node_s *left;
	struct c_rb_node_s *right;
	struct c_rb_node_s *parent;
}c_rb_node_t;

typedef struct c_rb_tree_s
{
	c_rb_node_t *root;
	c_rb_node_t  null;
	int (* compare)(const void *,const void *);
	int size;
}c_rb_tree_t;

typedef struct c_rb_iterator_s
{
	c_rb_tree_t *tree;
	c_rb_node_t *node;
}c_rb_iterator_t;

c_rb_tree_t *c_rbtree_create(int(*compare)(const void *,const void *));
void c_rbtree_destroy(c_rb_tree_t *rb_tree);
int  c_rbtree_insert(c_rb_tree_t *rb_tree,void *key,void *value);
void c_rbtree_remove1(c_rb_tree_t *rbtree,const *key,void **rkey,void **rvalue);
void c_rbtree_remove2(c_rb_tree_t *rbtree,c_rb_node_t *node);
int  c_rbtree_get(c_rb_tree_t *rbtree,const *key,void **rvalue);
int	 c_rb_pick(c_rb_tree_t *t, void **key, void **value);

c_rb_node_t* util_rbsubtree_min(c_rb_node_t *node, c_rb_node_t *sentinel);
c_rb_node_t* util_rbsubtree_max(c_rb_node_t *node, c_rb_node_t *sentinel);

#endif
