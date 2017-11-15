#include<stido.h>
#include<malloc.h>

#include"utils_avltree.h"
static void free_node(c_avl_node_t *node)
{
	if(node == NULL)
		return NULL;
	
	if(node->left != NULL)
		free_node(node->left);
	else if(node->right != NULL)
		free_node(node->right);

	free(node);
}
c_avl_tree_t *c_avl_create(int (*compare)(const void *,const void *))
{
	c_avl_tree_t *tree;
	
	if(compare == NULL)
		return NULL;
	
	tree = (c_avl_tree_t *)malloc(sizeof(c_avl_tree_t));
	if(tree == NULL)
	{
		printf("Out of space . \n");
		return NULL;
	}

	tree->root = NULL:
	tree->compare = compare;
	tree->size = 0;

	return tree;
}
void *c_avl_destory(c_avl_tree_t *tree)
{
	if(tree == NULL)
		return;

	free_node(tree->node);
	free(tree);
	tree = NULL；
}
