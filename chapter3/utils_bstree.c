#include <malloc.h>
#include <stdio.h>

#include"utils_bstree.h"

static void free_node(c_bs_node_t *node)
{
	if(node == NULL)
		return;

	if(node->left != NULL)
		free_node(node->left);
	if(node->right != NULL)
		free_node(node->right);
}
c_bs_tree_t *c_bs_create(int (*compare)(const void *, const void *))
{
	c_bs_tree_t *tree;
	if(compare == NULL)
		return NULL;
	tree = (c_bs_tree_t *)malloc(sizeof(c_bs_tree_t));
	if(tree == NULL)
	{
		printf("out of space.\n");
		return NULL;
	}

	tree->root = NULL;
	tree->compare = compare;
	tree->size = 0;

	return tree;
}
void c_bs_destroy(c_bs_tree_t *tree)
{
	if(tree == NULL)
		return;

	free_node(tree->root);
	free(tree);
}
int c_bs_insert(c_bs_tree_t *tree,void *key,void *value)
{
	c_bs_node_t *new;
	c_bs_node_t *nptr;
	int cmp; 

	if(tree == NULL)
		return -1;

	if ((new = malloc(sizeof(*new))) == NULL)
		return -1;
	new->key = key;
	new->value = value;
	new->left = NULL;
	new->right = NULL;
	new->height = 1;

	if(tree->root == NULL)
	{
		tree->root = new;
		tree->size = 1; 
	}

	nptr = tree->root;

	while(1)
	{
		cmp = tree->compare(nptr->key,new->key);
		if(cmp == 0)
		{
			free_node(new);
		}else if(cmp < 0)//在右子树上增加节点
		{
			if(nptr->right == NULL)
			{
				new->height += 1;
				nptr->right = new;
				new->parent = nptr;
			}
		}else
		{
			if(nptr->left == NULL)
			{
				new->height += 1;
				nptr->left = new;
				new->parent = nptr;
			}
		}
	}

	return 1;
}
int main()
{
	return -1;
}
