#ifndef UTILS_BSTREE_H
#define UTILS_BSTREE_H
struct c_bs_node_s
{
	void *key;
	void *value;
	int height;
	struct c_bs_node_s *left;
	struct c_bs_node_s *right;
	struct c_bs_node_s *parent;

};  
typedef struct c_bs_node_s c_bs_node_t;

struct c_bs_tree_s
{
	c_bs_node_t *root;
	int (*compare)(const void *,const void *);
	int size;

};
typedef struct c_bs_tree_s c_bs_tree_t;
c_bs_tree_t *c_bs_create(int (*compare)(const void *, const void *));
void c_bs_destroy(c_bs_tree_t *tree);
int c_bs_insert(c_bs_tree_t *tree,void *key,void *value);

#endif

