
#ifndef UTILS_AVLTREE_H
#define UTILS_AVLTREE_H
struct c_avl_node_s
{
	void *key;
	void *value;

	struct c_avl_node_s *left;
	struct c_avl_node_s *right;
	struct c_avl_node_s *parent;
}
struct c_avl_node_s c_avl_node_t;

struct c_avl_tree_s
{
	c_avl_node_t *root;
	int (*compare)(const void *, const void *);
	int size;
};
typedef struct c_avl_tree_s c_avl_tree_t;

c_avl_tree_t *c_avl_create(int (*compare)(const void *, const void *));

void c_avl_destory(c_avl_tree_t *tree);

#endif
