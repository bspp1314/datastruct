#include <malloc.h>
#include <stdio.h>
#include <assert.h>

#include"utils_bstree.h"
#define sfree(ptr)                                                             \
	do {                                                                         \
		free(ptr);                                                                 \
		(ptr) = NULL;                                                              \
	} while (0)


static void free_node(c_bs_node_t *node)
{
	if(node == NULL)
		return;

	if(node->left != NULL)
		free_node(node->left);
	if(node->right != NULL)
		free_node(node->right);
}
static c_bs_node_t *find(c_bs_tree_t *tree,const void *key)
{
	c_bs_node_t *node;
	int cmp = 0;

	node = tree->root;
	while(node != NULL)
	{
		cmp = tree->compare(node->key,key);
		if(cmp == 0)
			return node;
		else if(cmp < 0)//节点比关键字小
			node = node->right;
		else if(cmp > 0)
			node = node->left;
	}

	return NULL;
}
static c_bs_node_t *find_min(c_bs_node_t *node)
{
	c_bs_node_t *node_min;

	assert(node != NULL);

	node_min = node;

	while(node_min->left != NULL)
		node_min = node_min->left;

	return node_min;
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
int c_bs_get(c_bs_tree_t *tree,const void *key,void **value)
{
	c_bs_node_t *node;

	assert(tree != NULL);

	node = find(tree,key);
	if(node == NULL || value == NULL)
	{
		return -1;
	}

	*value = node->value;
	return 0;
}
int c_bs_remove(c_bs_tree_t *tree,const void *key)
{
	c_bs_node_t *node;
	c_bs_node_t *node_min;

	assert(tree != NULL);

	node = find(tree,key);
	if(node == NULL)
	{
		return 0;
	}

	if(node->left != NULL && node->right != NULL)
	{
		node_min = find_min(node);

		node_min->parent->left = NULL;

		node_min->parent = node->parent;

		if(node->parent == NULL)
			tree->root = node_min;
		else
		{
			if(node->parent->left == node)
				node->parent->left = node_min;
			else
				node->parent->right == node_min;
		}

		node->left->parent = node_min;
		node->right->parent = node_min;
		node_min->left = node->left;
		node_min->right = node->right;

		sfree(node);
	}else
	{
		if(node->left == NULL)
		{
			node->right->parent = node->parent;
			if(node->parent == NULL)
				tree->root = node->right;
			else
			{
				if(node->parent->left == node)
					node->parent->left = node->right;
				else
					node->parent->right = node->right;
			}
			sfree(node);

		}else if(node->right == NULL)
		{
			node->left->parent = node->parent;

			if(node->parent == NULL)
				tree->root == node->left;
			else
			{
				if(node->parent->left = node)
					node->parent->left = node->left;
				else
					node->parent->right = node->left;
			}

			sfree(node);
		}else
		{
			if(node->parent == NULL)
				tree->root == NULL;
			sfree(node);
		}

	}
	return 0;	
}
int main()
{
	return -1;
}
