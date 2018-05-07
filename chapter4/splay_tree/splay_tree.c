#include<stdio.h>
#include"splay_tree.h"
#include<assert.h>


/*         (x)                            (y)
 *        /   \                          /   \
 *    (y)     (c)											 (a)    (x) 
 *   /    \                                  /    \
 * (a)    (b)																 b     c
 *  右旋
 *
 */

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

	assert((node_parent == NULL) || (node_parent->left == node_x) || (node_parent->right) == node_x);

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

static c_splay_node_t* left_zig_zig(c_splay_tree_t *splay_tree,c_splay_node_t *node_x)
{
	assert(splay_tree != NULL && node_x != NULL && 
			node_x->right != NULL && node_x->right->right != NULL);

	c_splay_node_t *node_y = rotate_right(splay_tree,node_x);
	return rotate_right(splay_tree,node_y);
}

int main()
{
	return 0;
}
