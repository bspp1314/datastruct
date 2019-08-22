#ifndef TREE
#define TREE

typedef struct c_bs_node_s
{
	void *key;
	void *value;
	
	struct c_bs_node_s *left;
	struct c_bs_node_s *right;
	struct c_bs_node_s *parent;
}c_bs_node_t;

typedef struct c_bs_tree_s
{
	c_bs_node_t *root;
	int size;
	int (* compare)(const void *,const void *);
    void (* print_key_func)(const void *);
}c_bs_tree_t;

c_bs_tree_t *c_bs_tree_create(int(*compare)(const void *,const void *),void (* print_key_func)(const void *));
void c_bs_tree_destroy(c_bs_tree_t *bs_tree,int key_free ,int value_free);
void  c_bs_tree_remove(c_bs_tree_t *bs_tree,const void *key,void **rkey,void **rvalue);
void  c_bs_tree_get(c_bs_tree_t *bs_tree,const void *key,void **rvalue);
int c_bs_tree_insert(c_bs_tree_t *bs_tree,void *key,void *value);
void c_bs_tree_preorder(c_bs_tree_t *tree);
void c_bs_tree_inorder(c_bs_tree_t *tree);
void c_bs_tree_postorder(c_bs_tree_t *tree);

#endif
