#include<stdio.h>
#include<assert.h>
#include<malloc.h>
#include"splay_tree.h"

#ifdef DEBUG
static int check_splay_node(c_tree_t *tree,c_splay_node_t *node)
{
	int count = 1;
	if(node->left != NULL)
	{
		assert(node->left->parent == node);
		if(tree->compare(node->left->key,node->key) < 0)
			count += count(tree,node->left);
  }

	if(node->right != NULL)
	{
		assert(node->right->parent == node);
		if(tree->compare(node->right->key,node->key) > 0)
			count += count(tree,node->right);
	}

	return count;
}
#endif 

static void check_splay_tree(c_splay_tree_t *tree)
{
#ifdef DEBUG
	if(tree->root == NULL)
		assert(root->size == 0);
	else
		assert(root->size == check_splay_tree(tree,node));
#endif
}

static c_splay_node_t* left_max(c_splay_node_t *node)
{
	if(node == NULL)
		return NULL;
	
	while(node->right != NULL)
		node = node->right;

	return node;
}/* max value in the node left tree*/
static c_splay_node_t* right_min(c_splay_node_t *node)
{
	if(node == NULL)
		return NULL;
	
	while(node->right != NULL)
		node = node->right;

	return node;
}/* min value in the node right tree*/
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
/*         (x)                            (y)
 *        /   \                          /   \
 *    (y)     (c)											 (a)    (x) 
 *   /    \                                  /    \
 * (a)    (b)																 b     c
 *  右旋
 *
 */

static c_splay_node_t* rotate_right(c_splay_tree_t *tree,c_splay_node_t *node_x)
{
	assert(tree != NULL && node_x != NULL && node_x->left != NULL);

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
			tree->root = node_y;
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
static c_splay_node_t* rotate_left(c_splay_tree_t *tree, c_splay_node_t *node_x)
{ 
	assert(tree != NULL && node_x != NULL && node_x->right!= NULL);

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
		tree->root = node_y;
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
static c_splay_node_t* right_zig_zag(c_splay_tree_t *tree, c_splay_node_t *node_x)
{
	assert(tree != NULL && node_x != NULL && 
			node_x->left != NULL && node_x->left->right != NULL);

	rotate_left(tree,node_x->left);
	return rotate_right(tree,node_x);
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
static c_splay_node_t* left_zig_zag(c_splay_tree_t *tree, c_splay_node_t *node_x)
{
	assert(tree != NULL && node_x != NULL && 
			node_x->right!= NULL && node_x->right->left != NULL);

	rotate_right(tree,node_x->right);
	return rotate_left(tree,node_x);
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
static c_splay_node_t* right_zig_zig(c_splay_tree_t *tree,c_splay_node_t *node_x)
{
	assert(tree != NULL && node_x != NULL && 
			node_x->left != NULL && node_x->left->left != NULL);

	c_splay_node_t *node_y  = rotate_right(tree,node_x);
	return rotate_right(tree,node_y);
}

static c_splay_node_t* left_zig_zig(c_splay_tree_t *tree,
		c_splay_node_t *node_x)
{
	assert(tree != NULL && node_x != NULL && 
			node_x->right != NULL && node_x->right->right != NULL);

	c_splay_node_t *node_y = rotate_right(tree,node_x);
	return rotate_right(tree,node_y);
}
static c_splay_node_t* deal_with_grand_parent(c_splay_tree_t *tree,
		c_splay_node_t *node)
{
	c_splay_node_t *parent;
	c_splay_node_t *grand_parent;

	assert(tree != NULL && node != NULL && 
			node->parent != NULL && node->parent->parent != NULL);

	parent = node->parent;
	grand_parent= parent->parent;

	if(grand_parent->left->left == node)
		return right_zig_zig(tree,grand_parent);
	else if(grand_parent->right->right == node)
		return left_zig_zig(tree,grand_parent);
	else if(grand_parent->left->right == node)
		return right_zig_zag(tree,grand_parent);
	else
		return left_zig_zag(tree,grand_parent);
}

static void splay_the_tree(c_splay_tree_t *tree,c_splay_node_t *node)
{
	while(node->parent != tree->root)
		node = deal_with_grand_parent(tree,node);

	if(tree->root->left == node)
		rotate_right(tree,node);
	else if(tree->root->right == node)
		rotate_left(tree,node);
	else if(tree->root == node)
		return;
}

static c_splay_node_t *search(c_splay_tree_t *tree,const void *key)
{
	c_splay_node_t *node;
	int cmp;

	node = tree->root;
	while(node != NULL)
	{
		cmp = tree->compare(node->key,key);
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
	tree->size = 0;

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


int c_splay_insert(c_splay_tree_t *tree,void *key,void *value)
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

	if( tree->root == NULL )
	{
		new->parent == NULL;
		tree->root = new;
		tree->size = 1;
		return 0;
	}

	index = tree->root;

	while(1)
	{
		comp = tree->compare(index->key,new->key);
		if(comp == 0)
		{
			free_node(new);
			splay_the_tree(tree,index);
			return 1;
		}else if(comp < 0)
		{
			if(index->right == NULL)
			{
				index->right = new;
				new->parent = index;
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
				break;
			}else
			{
				index = index->left;
			}
		}
	}/*while(1)*/

	splay_the_tree(tree,new);
	tree->size++;
	check_splay_tree(tree);
	return 0;
}
int c_splay_get(c_splay_tree_t *tree, const void *key, void **value) {
	c_splay_node_t *node;

	assert(tree != NULL);

	node = search(tree, key);
	if (node == NULL)
		return -1;

	if (value != NULL)
		*value = node->value;

	splay_the_tree(tree,node);
	return 0;
}
int c_splay_remove(c_splay_tree_t *tree,const void *key,const void **rkey,const void **rvalue)
{
	c_splay_node_t *node;
	c_splay_node_t *new_root;

	assert(tree != NULL);

	node = search(tree, key);
	if (node == NULL)
		return;

	if (rkey != NULL)
		*rkey = node->key;
	if (rvalue != NULL)
		*rvalue = node->value;

	splay_the_tree(tree,node);
	if(node->left == NULL)
	{
		tree->root = node->right;
		if(node->right != NULL)
			node->right->parent = NULL;
		free_node(node);
	}else if(node->right == NULL)
	{
		tree->root = node->left;
		if(node->left != NULL)
			node->left->parent = NULL;	
		free_node(node);
	}else{
		c_splay_node_t *lmax = left_max(node->left);/* get max value in the node left tree*/
		node->value = lmax->value;
		node->key = lmax->key;

		if(node->left != NULL)
		{
			lmax->parent->right = lmax->left;
			lmax->left->parent = lmax->parent;
		}
		free_node(lmax);
	}

	tree->size--;
	check_splay_tree(tree);
}

