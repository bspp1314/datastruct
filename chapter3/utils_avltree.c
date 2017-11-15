#include<stdio.h>
#include<malloc.h>
#include<assert.h>

#include"utils_avltree.h"

static int calc_balance(c_avl_node_t *node)
{
	int left_hight = (node->left == NULL) ? 0 :node->left->height;
	int right_hight = (node->right == NULL) ? 0:node->right->height;
	return left_hight - right_hight;
}/*staitc int calc_balance  计算左右子树的高度差，既获取平衡因子。*/

static void verify_tree (c_avl_node_t *node)
{
	if (node == NULL)
		return;

	verify_tree (node->left);
	verify_tree (node->right);

	assert ((calc_balance (node) >= -1) && (calc_balance (node) <= 1));
	assert ((node->parent == NULL) || (node->parent->right == node) || (node->parent->left == node));

} /* void verify_tree  验证是否为avl树*/

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

/*         (x)             (y)
 *        /   \           /   \
 *	3	 (y)    /\ 1       /\    (x) 2
 *    /   \  /_c\  ==>  / a\  /   \
 *   /\   /\           /__2_\/\   /\
 *  / a\ /1b\               /1b\ /1c\
 * /_2___\
 *  c > x > b
 *  右旋
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
 *  
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
/*         (x)                     (x)                         (z)
 *        /   \                   /   \                       /   \
 *      (3y) (1d)               (3z)  (1d)                   y     x
 *     /   \           left    /  \         right           / \   / \
 *   (1a)  (2z)      ======> (2y) (1c)    ==============>  a   b  c  d
 *         / \              /   \
 *      (1b)  (1c)         (1a) (ab)
 *
 *
 *  先右旋,再左旋
 *
 */
static c_avl_node_t *rotate_left_right(c_avl_tree_t *tree,c_avl_node_t *x)
{ 
	rotate_left(tree,x->left);
	return rotate_right(tree,x);
}
/*       (x)                        (x)                           (z)                         
 *      /   \        right         /   \            right        /   \
 *  (1a)    (3y)      ====>    (1a)    (3z)     ============>   x     y
 *          /   \                    /    \                    / \   / \
 *      (2z)    (1d)             (1b)      (2y)               a   b c   d
 *      /  \                              /    \
 *  (1b)    (1c)                      (1c)      (1d)
 *先左旋,在右旋
 * 
 */
static c_avl_node_t *rotate_right_left(c_avl_tree_t *tree,c_avl_node_t *x)
{
	rotate_right(tree,x->right);
	return rotate_left(tree,x);
}

static void rebalance(c_avl_tree_t *tree, c_avl_node_t *node)
{
	int balance_p;
	int balance_c;
	while(node != NULL)
	{
		balance_p  = calc_balance(node);
		assert((balance_p <=2 && balance_p <= 2));
		if(balance_p == -2)//右子树高
		{
			assert(node->right != NULL);
			balance_c = calc_balance(node->right);
			assert((balance_c >= -1) && (balance_c <= 1));
			if(balance_c == -1)
				node = rotate_left(tree,node);
			else
				node = rotate_right_left(tree,node);

		}else if(balance_p == 2)
		{
			assert(node->left != NULL);
			balance_c = calc_balance(node->left);
			assert((balance_c >= -1) && (balance_c <= 1));
			if(balance_c == -1)
				node = rotate_left_right(tree,node);
			else
				node = rotate_right(tree,node);
		}else
		{
			int height = calc_height(node);
			if(height != node->height)//节点改变导致其记录值和实际值不相同
				node->height = height;
			else
				break;
		}

		assert(node->height == calc_height(node));
		node = node->parent;
	}
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
}/* c_avl_tree_t *c_avl_create  */

void c_avl_destory(c_avl_tree_t *tree)
{
	if(tree == NULL)
		return;

	free_node(tree->root);
	free(tree);
	tree = NULL;
}/* void c_avl_destory */

int c_avl_insert(c_avl_tree_t *tree,void *key,void *value)
{
	c_avl_node_t *new;
	c_avl_node_t *ptr;
	int cmp;

	new  = (c_avl_node_t *)malloc(sizeof(c_avl_node_t)); 
	if(new == NULL)
		return -1;

	new->key = key;
	new->value = value;
	new->height = 1;
	new->left = NULL;
	new->right = NULL;

	if(tree->root == NULL)
	{
		new->parent = NULL;
		tree->root = new;
		tree->size = 1;
		return 0;
	}

	ptr = tree->root;
	while(1)
	{
		cmp = tree->compare(ptr->key,new->key);
		if(cmp == 0)
		{
			free_node(new);
			return -1;
		}else if(cmp < 0)//prt->key < new->key
		{
			if(ptr->right == NULL)
			{
				ptr->right = new;
				new->parent = ptr;
				rebalance(tree,ptr);
			}else
			{
				ptr = ptr->right;
			}
		}else//ptr->key > new->key
		{
			if(ptr->left == NULL)
			{
				ptr->left = new;
				new->parent = ptr;
				rebalance(tree,ptr);
			}else
			{
				ptr = ptr->right;
			}
		}
	}
	verify_tree(tree->root);
	tree->size++;
	return 1;
}

int main()
{
	return -1;
}
