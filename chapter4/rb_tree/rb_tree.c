#include <stdio.h>
#include <assert.h>
#include "rb_tree.h"

/* the NULL node of tree */
#define _NULL(rbtree) (&((rbtree)->null))

static c_rb_node_t* rotate_right(c_rb_tree_t *tree,c_rb_node_t *node_x);
static c_rb_node_t* rotate_left(c_rb_tree_t *tree, c_rb_node_t *node_x);
static void c_rbtree_insert_current(c_rb_tree_t *tree, c_rb_node_t *node);


/*         (x)                            (y)
 *        /   \                          /   \
 *    (y)     (c)											 (a)    (x) 
 *   /    \                                  /    \
 * (a)    (b)																 b     c
 *  右旋
 *
 */

static c_rb_node_t* rotate_right(c_rb_tree_t *tree,c_rb_node_t *node_x)
{
	assert(tree != NULL && node_x != NULL && node_x->left != NULL);

	c_rb_node_t *node_y;
	c_rb_node_t *node_parent;
	c_rb_node_t *node_b;

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
static c_rb_node_t* rotate_left(c_rb_tree_t *tree, c_rb_node_t *node_x)
{ 
	assert(tree != NULL && node_x != NULL && node_x->right!= NULL);

	c_rb_node_t *node_y;
	c_rb_node_t *node_parent;
	c_rb_node_t *node_b;

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
static void c_rbtree_insert_current(c_rb_tree_t *tree, c_rb_node_t *node)
{
	c_rb_tree_t *parent;
	c_rb_tree_t *uncle;

	while(node->parent->color == READ)
}
int main(){
	return 0;
}


