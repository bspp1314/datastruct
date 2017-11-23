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

/*         (x)                            (y)
 *        /   \                          /   \
 *    (3y)     (1c)                   (2a)    (2x) 
 *   /    \                                  /    \
 * (2a)    (1b)                            1b     1c
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
 *    (x)                        (y)             
 *   /   \                      /   \
 *(1a)    (3y)              (2x)		 (2c)
 *        /   \            /    \
 *       (1b)  (2c)      1a     1b 
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
static c_avl_node_t *search(c_avl_tree_t *tree,const void *key)
{
	c_avl_node_t *node;
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

//中序遍历(左中右)
static c_avl_node_t *c_avl_node_next(c_avl_node_t *node)
{
	c_avl_node_t *r_node;
	if(node == NULL)
		return NULL;
	/* 向上回溯，直到该节点的父节点的左节点是其身 */
	if(node->right == NULL)
	{
		r_node = node->parent;
		while((r_node != NULL) && (r_node->parent != NULL))
		{
			if(r_node->left == node)
				break;

			node = r_node;
			r_node = node->parent;
		}
		/*
		 * next is null
		 * */
		if((r_node == NULL) || (r_node->left != node))
		{
			assert((r_node == NULL) || (r_node->left != node));
			return NULL;
		}else
		{
			assert((r_node->left == node));
			return r_node;
		}
	}else
	{
		r_node = node->right;
		while(r_node->left != NULL)
			r_node = r_node->right;
	}
	return r_node;
}

static c_avl_node_t *c_avl_node_prev(c_avl_node_t *node)
{
	c_avl_node_t *r_node; //return node;

	if(node == NULL)
		return NULL;
	if(node->left == NULL)
	{
		r_node = node->parent;
		while(r_node != NULL && r_node->parent != NULL)
		{
			if(r_node->right == r_node)
				break;
			node =	r_node;
			r_node = node->parent;
		}

		if(r_node == NULL || r_node->right != node)
		{
			assert((r_node == NULL) || (r_node->parent == NULL));
			return NULL;
		}else{
			assert(r_node->right == NULL);
			return r_node;
		}
	}else//左子树里面的最大值
	{
		r_node = node->left;
		while(r_node->right != NULL)
			r_node = r_node->right;
	}
	return r_node;
}/*逆中序遍历 右中左*/

static int _remove(c_avl_tree_t *tree,c_avl_node_t *node)
{
	assert((tree != NULL) && (node != NULL));

	if((node->left != NULL) && (node->right != NULL))//have two child tree
	{
		c_avl_node_t *r_node; //replace node
		if(calc_balance(node) > 0)/* left subtree is higher */
		{
			assert(node->left != NULL);
			r_node = c_avl_node_prev(node);//node节点左子树方向的最大值
		}else
		{
			assert(node->right != NULL);
			r_node = c_avl_node_next(node);//node节点右子树方向的最小值
		}

		assert((r_node->right == NULL) || (r_node->left == NULL));
		node->key = r_node->key;
		node->value = r_node->value;

		node = r_node;
	}

	assert((node->left == NULL) || node->right == NULL);
	assert(node->parent == NULL || node->parent->left == node || node->parent->right == node);

	if((node->left == NULL) && node->right == NULL)
	{
		if(node->parent == NULL)
		{
			assert(tree->root == node);
			tree->root = NULL;
		}else
		{
			if(node->parent->left == node)
				node->parent->left = NULL;
			else
				node->parent->right = NULL;

			rebalance(tree,node->parent);
		}
		free_node(node);
	}else if((node->left == NULL))
	{
		assert(calc_balance(node) == -1);
		if(node->parent == NULL)
		{
			assert(tree->root == node);
			tree->root = node->right;
		}else
		{
			if(node->parent->left == node)
				node->parent->left = node->right;
			else
				node->parent->right == node->right;
			rebalance(tree,node);
		}
		free_node(node);
	}else if((node->right == NULL))
	{
		assert(calc_balance(node) == 1);
		if(node->parent == NULL)
		{
			assert(tree->root == node);
			tree->root = node->left;
		}else
		{
			if(node->parent->left == node)
				node->parent->left = node-> left;
			else
				node->parent->right = node->right;
			rebalance(tree,node);
		}
		free_node(node);
	}
	return 0;
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
int c_avl_remove(c_avl_tree_t *tree,const void *key)
{
	c_avl_node_t *node;

	assert(tree != NULL);

	node = search(tree,key);
	if(node == NULL)
		return -1;


	_remove(tree,node);
	verify_tree(tree->root);
	tree->size--;

	return 0;
}
int c_avl_get(c_avl_tree_t *tree, const void *key, void **value)
{ 
	c_avl_node_t *node;

	assert(tree != NULL);

	node = search(tree,key);
	if(node == NULL)
		return -1;

	if(value != NULL)
		*value = node->value;

	return 0;
}
C_AVL_ITERATOR_S *c_avl_get_iterator(C_AVL_TREE_S *psTree)
{
	C_AVL_ITERATOR_S *psIter;

	if(psTree == NULL)
		return NULL;

	psIter = (C_AVL_ITERATOR_S *)malloc(sizeof(C_AVL_ITERATOR_S));
	if(psIter == NULL)
	{
		printf("Out of space .\n");
		return NULL;
	}
	psIter->tree = psTree;
	psIter->node = NULL;

	return psIter;
}
int c_avl_iterator_next(c_avl_iterator_t *iter,void **key,void **value)
{
	c_avl_node_t *node;

	if ((iter == NULL) || (key == NULL) || (value == NULL))
		return -1;

	if(iter->node == NULL)
	{
		for(node = iter->tree->root; node != NULL; node->left)
			if(node->left == NULL)
				break;
	}else
	{
		node = c_avl_node_next(iter->node);
	}

	if(node == NULL)
		return -1;

	iter->node = node;
	*key = node->key;
	*value = node->value;
}/*迭代器*/

int c_avl_iterator_prev(c_avl_iterator_t *iter,void **key,void **value)
{
	c_avl_node_t *node;

	if ((iter == NULL) || (key == NULL) || (value == NULL))
		return -1;

	if(iter->node == NULL)
	{
		for(node = iter->tree->root; node != NULL; node->right)
			if(node->right == NULL)
				break;
	}else
	{
		node = c_avl_node_prev(iter->node);
	}

	if(node == NULL)
		return -1;

	if(node == NULL)
		return -1;

	iter->node = node;
	*key = node->key;
	*value = node->value;
}
void c_avl_iterator_destroy(c_avl_iterator_t *iter) { free(iter);  }

int c_avl_size(c_avl_tree_t *t) {
	if (t == NULL)
		return 0;
	return t->size;

}


int main()
{
	return -1;
}
