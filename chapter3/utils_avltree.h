
#ifndef UTILS_AVLTREE_H
#define UTILS_AVLTREE_H
struct c_avl_node_s
{
	void *key;
	void *value;
	int height;

	struct c_avl_node_s *left;
	struct c_avl_node_s *right;
	struct c_avl_node_s *parent;
};
typedef struct c_avl_node_s c_avl_node_t;
typedef struct c_avl_node_s C_AVL_NODE_S;

struct c_avl_tree_s
{
	c_avl_node_t *root;
	int (*compare)(const void *, const void *);
	int size;
};
typedef struct c_avl_tree_s c_avl_tree_t;
typedef struct c_avl_tree_s C_AVL_TREE_S;

struct c_avl_iterator_s
{
	C_AVL_TREE_S *tree;
	C_AVL_NODE_S *node;
};

typedef struct c_avl_iterator_s c_avl_iterator_t;
typedef struct c_avl_iterator_s C_AVL_ITERATOR_S;



c_avl_tree_t *c_avl_create(int (*compare)(const void *, const void *));

void c_avl_destory(c_avl_tree_t *tree);
int c_avl_remove(c_avl_tree_t *tree,const void *key);
int c_avl_insert(c_avl_tree_t *tree,void *key,void *value);

#endif
