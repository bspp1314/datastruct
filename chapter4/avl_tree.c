#include<stdio.h>
#include<malloc.h>
#include<assert.h>

#include"avl_tree.h"


static int 
calc_balance(c_avl_node_t *avl_node)
{
	int left_hight = (avl_node->left == NULL) ? 0 : avl_node->left->height;
	int right_hight = (avl_node->right == NULL) ? 0 : avl_node->right->height;
	return left_hight-right_hight;
}/* 计算左右子树的高度差，获取平衡因子 */

static void
verify_node(c_avl_node_t *avl_node)
{
	if( avl_node == NULL )
		return;
	
	verify_node(avl_node->left);
	verify_node(avl_node->right);

	assert((calc_balance(avl_node)) >= -1 && calc_balance(avl_node) <=1 );
	assert((avl_node->parent == NULL) || (avl_node->parent->left == avl_node) 
			|| (avl_node->parent->right == avl_node)); 
}/*验证所有节点是否符合平衡二叉树的性质*/

static void 
verify_tree(c_avl_tree_t *avl_tree)
{
	if( avl_tree == NULL )
		return;
	
	verify_node(avl_tree->root);
}

static void 
free_node(c_avl_node_t *avl_node)
{
	if(avl_node == NULL)
		return;
	
	free_node(avl_node->left);
	free_node(avl_node->right);

	free(avl_node);
	avl_node = NULL;
}

static int
calc_height(c_avl_node_t *avl_node)
{
	if(avl_node == NULL)
		return 0;

	int left_height = avl_node->left == NULL ? 0 : avl_node->left->height;
	int right_height = avl_node->right == NULL ? 0 : avl_node->right->height;

	return left_height > right_height ? (left_height +1 ):(right_height +1);
}

c_avl_tree_t*
c_avl_create(int(*compare)(const void *,const void *))
{
	c_avl_tree_t *avl_tree = NULL;

	if(compare == NULL)
	{
		printf("compare function not be null\n");
		return NULL;
	}
	
	avl_tree = (c_avl_tree_t *) malloc(sizeof(c_avl_tree_t));
	if(avl_tree == NULL)
	{
		printf("malloc avl tree failed\n");
		return NULL;
	}

	avl_tree->root = NULL;
	avl_tree->size = 0;
	avl_tree->compare = compare;

	return avl_tree;
}

void 
c_avl_destroy(c_avl_tree_t *avl_tree)
{
	if(avl_tree == NULL)
		return;

	free_node(avl_tree->root);
	free(avl_tree);
	avl_tree = NULL;
}

static c_avl_node_t*
search_node(c_avl_node_t *avl_node, const void *key,int(*compare)(const void *,const void *))
{
	c_avl_node_t *result_node = NULL;
	int comp = 0;

	assert(compare != NULL);

	if( avl_node == NULL)
		return NULL;

	comp = compare(key,avl_node->key);
	if( comp  < 0) // 要搜索的node是该节点的左子树
		 result_node = search_node(avl_node->left,key,compare);
	else if (comp > 0)
		result_node = search_node(avl_node->right,key,compare);
	else
		result_node = avl_node;

	return result_node;
}

static 
c_avl_node_t *search_tree(c_avl_tree_t *avl_tree, const void *key)
{
	
	if( avl_tree == NULL )
		return NULL;
	
	return search_node(avl_tree->root,key,avl_tree->compare);
}
/*         (x)                            (y)
 *        /   \                          /   \
 *    (3y)     (1c)                   (2a)    (2x) 
 *   /    \                                  /    \
 * (2a)    (1b)                            1b     1c
 *  右旋
 *
 */

static c_avl_node_t*
rotate_right(c_avl_tree_t *avl_tree, c_avl_node_t *node_x)
{
	c_avl_node_t *node_y = NULL;
	c_avl_node_t *node_b = NULL;
	c_avl_node_t *node_parent = NULL;

	assert(node_x != NULL);
	assert(avl_tree != NULL);
	assert(node_x->left !=  NULL);
	
	node_y = node_x->left;
	node_b = node_y->right;
	node_parent = node_x->parent;

	node_y->right = node_x;
  node_y->parent = node_x->parent;

	node_x->left = node_b;
	node_x->parent = node_y;

	if(node_b != NULL)
		node_b->parent = node_x;

	assert((node_parent == NULL) || (node_parent->left == node_x) || (node_parent->right) == node_x);
	if( node_parent == NULL)
			avl_tree->root = node_y;
	else
	{
		 if(node_parent->left == node_x)
			 node_parent->left = node_y;
		 else 
			 node_parent->right = node_y;
	}

	node_x->height = calc_height(node_x);
	node_y->height = calc_height(node_y);

	return node_y;
}

int main(){
	return 0;
}
