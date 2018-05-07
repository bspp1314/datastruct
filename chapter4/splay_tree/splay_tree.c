#include<stdio.h>
#include<assert.h>
#include<malloc.h>
#include"splay_tree.h"


/*         (x)                            (y)
 *        /   \                          /   \
 *    (y)     (c)											 (a)    (x) 
 *   /    \                                  /    \
 * (a)    (b)																 b     c
 *  右旋
 *
 */

static void free_node(c_splay_node_t *node)
{
	if(node == NULL)
		return;

	if(node->left != NULL)
		free_node(node->left);
	else if(node->right != NULL)
		free_node(node->right);

	free(node);
}
static c_splay_node_t* rotate_right(c_splay_tree_t *splay_tree,c_splay_node_t *node_x)
{
	assert(splay_tree != NULL && node_x != NULL && node_x->left != NULL);

	c_splay_node_t *node_y;
	c_splay_node_t *node_parent;
	c_splay_node_t *node_b;

	node_y = node_x->left;
	node_parent = node_x->parent;
	node_b = node_y->right;

	node_x->left = node_b;
	node_x->parent = node_y;

	node_y->right = node_x;
	node_y->parent = node_parent;

	if(node_b != NULL)
		node_b->parent = node_y;

	assert(node_parent == NULL || node_parent->left == node_x || node_parent->right == node_x);
		if(node_parent == NULL)
			splay_tree->root = node_y;
		else if(node_parent->left == node_x)
			node_parent->left = node_y;
		else
			node_parent->right = node_y;

	return node_y;
}
/*
 *    (x)                        (y)             
 *   /   \                      /   \
 *(a)    (y)                 (x)    (c)
 *      /   \               /   \
 *    (b)   (c)            a     b 
 */
static c_splay_node_t* rotate_left(c_splay_tree_t *splay_tree, c_splay_node_t *node_x)
{ 
	assert(splay_tree != NULL && node_x != NULL && node_x->right!= NULL);

	c_splay_node_t *node_y;
	c_splay_node_t *node_parent;
	c_splay_node_t *node_b;

	node_y = node_x->right;
	node_parent = node_x->parent;
	node_b = node_y->left;

	node_y->left = node_x;
	node_y->parent = node_parent;

	node_x->parent = node_y;
	node_x->right = node_b;

	if(node_b != NULL)
		node_b->parent = node_x;

	assert(node_parent == NULL || node_parent->left == node_x || node_parent->right == node_x);
	if(node_parent == NULL)
		splay_tree->root = node_y;
	else if(node_parent->left == node_x)
		node_parent->left = node_y;
	else 
		node_parent->right = node_y;

	return node_y;
}
/*         (x)                     (x)                         (z)
 *        /   \                   /   \                       /   \
 *      (y)		(d)               (z)   (d)                    y     x
 *     /   \           left    /  \         right           / \   / \
 *   (a)   (z)      ======> (y)   (c)    ==============>   a   b  c  d
 *         / \              /   \
 *      (b)  (c)         (a)    (b)
 *
 */
static c_splay_node_t* right_zig_zag(c_splay_tree_t *splay_tree, c_splay_node_t *node_x)
{
	assert(splay_tree != NULL && node_x != NULL && 
			node_x->left != NULL && node_x->left->right != NULL);

	rotate_left(splay_tree,node_x->left);
	return rotate_right(splay_tree,node_x);
}


/*       (x)                        (x)                           (z)                         
 *      /   \        right         /   \            right        /   \
 *  (a)     (y)      ====>       (a)   (z)     ============>    x     y
 *          /  \                      /   \                    / \   / \
 *       (z)   (d)                  (b)    (y)                a   b c   d
 *      /  \                              /  \
 *    (b)    (c)                       (c)    (d)
 *先左旋,在右旋
 * 
 */
static c_splay_node_t* left_zig_zag(c_splay_tree_t *splay_tree, c_splay_node_t *node_x)
{
	assert(splay_tree != NULL && node_x != NULL && 
			node_x->right!= NULL && node_x->right->left != NULL);

	rotate_right(splay_tree,node_x->right);
	return rotate_left(splay_tree,node_x);
}

/*
 *
 *         (x)                (y)                     (z)          
 *        /   \             /     \                  /   \
 *      (y)		(d)        (z)       (x)              (a)  (y)                 
 *     /   \            /   \     /   \								  /   \
 *   (z)   (c)        (a)   (b)  (c)	(d)							(d)	 (x)    
 *   / \									                                /   \
 *(a)  (b)                                              (c)   (d)
 *
 */
 
/* left zig-zig */
static c_splay_node_t* right_zig_zig(c_splay_tree_t *splay_tree,c_splay_node_t *node_x)
{
	assert(splay_tree != NULL && node_x != NULL && 
			node_x->left != NULL && node_x->left->left != NULL);

	c_splay_node_t *node_y  = rotate_right(splay_tree,node_x);
	return rotate_right(splay_tree,node_y);
}

static c_splay_node_t* left_zig_zig(c_splay_tree_t *splay_tree,
		c_splay_node_t *node_x)
{
	assert(splay_tree != NULL && node_x != NULL && 
			node_x->right != NULL && node_x->right->right != NULL);

	c_splay_node_t *node_y = rotate_right(splay_tree,node_x);
	return rotate_right(splay_tree,node_y);
}
static c_splay_node_t* deal_with_grand_parent(c_splay_tree_t *splay_tree,
		c_splay_node_t *splay_node)
{
	c_splay_node_t *parent;
	c_splay_node_t *grand_parent;

	assert(splay_tree != NULL && splay_node != NULL && 
			splay_node->parent != NULL && splay_node->parent->parent != NULL);

	parent = splay_node->parent;
	grand_parent= parent->parent;

	if(grand_parent->left->left == splay_node)
		return right_zig_zig(splay_tree,grand_parent);
	else if(grand_parent->right->right == splay_node)
		return left_zig_zig(splay_tree,grand_parent);
	else if(grand_parent->left->right == splay_node)
		return right_zig_zag(splay_tree,grand_parent);
	else
		return left_zig_zag(splay_tree,grand_parent);
}

static void splay_the_tree(c_splay_tree_t *splay_tree,c_splay_node_t *splay_node)
{
	while(splay_node->parent != splay_tree->root)
		splay_node = deal_with_grand_parent(splay_tree,splay_node);

	if(splay_tree->root->left == splay_node)
		rotate_right(splay_tree,splay_node);
	else if(splay_tree->root->right == splay_node)
		rotate_left(splay_tree,splay_node);
	else if(splay_tree->root == splay_node)
		return;
}

static c_splay_node_t *search(c_splay_tree_t *splay_tree,const void *key)
{
	c_splay_node_t *node;
	int cmp;

	node = splay_tree->root;
	while(node != NULL)
	{
		cmp = splay_tree->compare(node->key,key);
		if(cmp == 0)
			break;
		else if(cmp < 0) // node->key < key
			node = node->right;
		else
			node = node->left;//node->key > key;
	}

	return node;
}
c_splay_tree_t *c_splay_create(int (*compare)(const void *,const void *))
{
	c_splay_tree_t *tree;

	if(compare == NULL)
		return NULL;

	tree = (c_splay_tree_t *)malloc(sizeof(c_splay_tree_t));
	if(tree == NULL)
	{
		printf("Out of space . \n");
		return NULL;
	}

	tree->root = NULL;
	tree->compare = compare;

	return tree;
}/* c_splay_tree_t *c_splay_create  */
void c_splay_destory(c_splay_tree_t *tree)
{
	if(tree == NULL)
		return;

	free_node(tree->root);
	free(tree);
	tree = NULL;
}/* void c_splay_destory */


int c_splay_insert(c_splay_tree_t *splay_tree,void *key,void *value)
{
	c_splay_node_t *new;
	c_splay_node_t *index;
	int comp;

	if( (new = (c_splay_node_t *)malloc(sizeof(c_splay_node_t))) == NULL)
	{
		printf("malloc c_splay_node_t failed \n");
		return;
	}

	new->key = key;
	new->value = value;
	new->left = NULL;
	new->right = NULL;
	new->parent = NULL;

	if( splay_tree->root == NULL )
	{
		new->parent == NULL;
		splay_tree->root = new;
		splay_tree->size = 1;
		return 0;
	}

	index = splay_tree->root;

	while(1)
	{
		comp = splay_tree->compare(index->key,new->key);
		if(comp == 0)
		{
			free_node(new);
			splay_the_tree(splay_tree,index);
			return 1;
		}else if(comp < 0)
		{
			if(index->right == NULL)
			{
				index->right = new;
				new->parent = index;
				splay_the_tree(splay_tree,new);
				break;
			}else
			{
				index = index->right;
			}
		}else if(comp > 0)
		{
			if(index->left == NULL)
			{
				index->left = new;
				new->parent = index;
				splay_the_tree(splay_tree,new);	
				break;
			}else
			{
				index = index->left;
			}
		}
	}/*while(1)*/

	return 0;
}
int c_splay_get(c_splay_tree_t *splay_tree, const void *key, void **value) {
	c_splay_node_t *node;

	assert(splay_tree != NULL);

	node = search(splay_tree, key);
	if (node == NULL)
		return -1;

	if (value != NULL)
		*value = node->value;

	splay_the_tree(splay_tree,node);
	return 0;
}
int c_splay_remove(c_splay_tree_t *splay_tree,const void *key,const void **rkey,const void **result)
{
	c_splay_node_t *node;
	c_splay_node_t *new_root;

	assert(splay_tree != NULL);

	node = search(splay_tree, key);
	if (node == NULL)
		return;

	if (rkey != NULL)
		*rkey = node->key;
	if (rvalue != NULL)
		*rvalue = node->value;

	if(node->left == NULL && node->right == NULL)
	{
		splay_tree->root == NULL;
		free_node(node);
	}else
	{
		splay_tree(splay_tree,node);
		if(node->left != NULL)
		{
			new_root = node->left;
			while(new_root->left != NULL)
				new_root = new_root->left;

			new_root-
		}
	}
	
	
}



int main()
{
	return 0;
}
