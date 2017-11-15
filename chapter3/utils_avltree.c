#include<stdio.h>
#include<malloc.h>
#include<assert.h>

#include"utils_avltree.h"


static int calc_height(c_avl_node_t *node)
{
	int height_left;
	int height_right;

	if(node == NULL)
		return 0;

	height_left = (node->left == NULL) ? 0:node->left->height;
	height_right =(node->right == NULL) ? 0:node->right->height;

	return height_left > height_right ? height_left : height_right;
}

/*         (x)             (y)
 *        /   \           /   \
 *	3	 (y)    /\ 1       /\    (x) 2
 *    /   \  /_c\  ==>  / a\  /   \
 *   /\   /\           /__2_\/\   /\
 *  / a\ /1b\               /1b\ /1c\
 * /_2___\
 *  c > x > b
 *  右旋
 *  x 的平衡因子为-2,且其左子树的平衡在[-1,-2]区间
 *
 */
static c_avl_node_t *rotate_right(c_avl_tree_t *tree, c_avl_node_t *x) {
	c_avl_node_t *parent;
	c_avl_node_t *y;
	c_avl_node_t *b;

	assert(x != NULL);
	assert(x->left != NULL);
	assert(tree != NULL);

	parent = x->parent;
	y = x->left;
	b = y->right;

	if(b != NULL)
		b->parent = x;
	x->parent = y;
	x->left = b;

	y->right = x;
	if(parent == NULL)
		tree->root = y;
	else if(parent->left == x)
		parent->left = y;
	else
		parent->right = y;
	
	y->height = calc_height(y);
	x->height = calc_height(x);
	return y;
}
/*
 *    (x)                   (y)
 *   /   \                 /   \
 *  /\ 1  (y) 3         (x) 2  /\ 2
 * /1a\  /   \   ==>   /   \  / c\
 *      /\   /\       /\   /\/____\
 *     /1b\ / c\     /1a\ /1b\
 *         /2___\
 *  b > x > a
 *  x的平衡因为为2,且其右子树的平衡因子在[1,2]区间
 */
static c_avl_node_t *rotate_left(c_avl_tree_t *tree,c_avl_node_t *x)
{
	c_avl_node_t *parent;
	c_avl_node_t *y;
	c_avl_node_t *b;

	assert(x != NULL);
	assert(x->right != NULL);
	assert(tree != NULL);

	parent = x->parent;
	y = x->right;
	b = y->left;

	if(b != NULL)
		b->parent = x;

	x->right = b;
	x->parent = y;
	
	y->left = x;

	if(parent == NULL)
		tree->root = y;
	else
		if(parent->left == x)
			parent->left = y;
		else
			parent->right = y;

	y->height = calc_height(y);
	y->height = calc_height(x);
	return y;
}
/*         (x)                 (x)                           (x)
 *        /   \               /   \             在右旋      /   \
 *	3	 (y)    /\ 1        3  (z)  (d) 1        ======>     y 2   x 2
 *    /   \  /_d\     ==>   /   \                         / \   / \
 *   /\		(z) 2        2  (y)  (c1)                      1a  1b 1c 1d
 *  /1a\ /   \           /   a    
 *      /\   /\         /\   /\
 *     /1b\ /1c\       /1a\ /1b\
 *
 *  先右旋,再左旋
 *  x的平衡因子等于-2,且其左子树的平衡因子在[1,2] 区间
 */
static c_avl_node_t *rotate_left_right(c_avl_tree_t *tree,c_avl_node_t *x)
{ 
	rotate_left(tree,x->left);
	return rotate_right(tree,x);
}
/*       (x)                       (x)
 *      /   \                     /   \
 *     /\    (y)                (1a)  (z)
 *    /a_\  /   \  ==========>        /
 *        (z)   /\
 *       /   \ /1d\
 *      /\   /\
 *     /1b\ /1c\
 *先左旋,在右旋
 */
static a_avl_node_t *rotate_right_left(c_avl_tree_t *tree,c_avl_node_t *x)
{
	rotate_right(x,x->right);
	return rotate_left(tree,x);
}
static void free_node(c_avl_node_t *node)
{
	if(node == NULL)
		return;
	
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

	tree->root = NULL;
	tree->compare = compare;
	tree->size = 0;

	return tree;
}
void c_avl_destory(c_avl_tree_t *tree)
{
	if(tree == NULL)
		return;

	free_node(tree->root);
	free(tree);
	tree = NULL;
}
int main()
{
	return -1;
}
