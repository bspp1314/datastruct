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
  node_y->parent = node_parent;

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



/*
 *    (x)                        (y)             
 *   /   \                      /   \
 *(1a)    (3y)              (2x)     (2c)
 *        /   \            /    \
 *       (1b)  (2c)      1a     1b 
 */
static c_avl_node_t* 
rotate_left(c_avl_tree_t *avl_tree, c_avl_node_t *node_x)
{ 
	c_avl_node_t *node_y;
	c_avl_node_t *node_parent;
	c_avl_node_t *node_b;

	assert(node_x != NULL);
	assert(avl_tree != NULL);
	assert(node_x->right !=  NULL);

	node_y = node_x->right;
	node_parent = node_x->parent;
	node_b = node_y->right;

	node_y->left = node_x;
	node_y->parent = node_parent;

	node_x->parent = node_y;
	node_x->right = node_b;

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
	return node_y;
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
static c_avl_node_t* 
rotate_left_right(c_avl_tree_t *avl_tree, c_avl_node_t *node_x)
{
	
	rotate_left(avl_tree,node_x->left);
	return rotate_right(avl_tree,node_x);
}

/*       (x)                        (x)                           (z)                         
 *      /   \        right         /   \            right        /   \
 *  (1a)    (3y)      ====>    (1a)    (3z)     ============>   x     y
 *          /   \                    /    \                    / \   / \
 *      (2z)    (1d)             (1b)      (2y)               a   b c   d
 *      /  \                              /    \
 *  (1b)    (1c)                      (1c)      (1d)
 *先左旋,在右旋
 */
static c_avl_node_t*
rotate_right_left(c_avl_tree_t *avl_tree,c_avl_node_t *node_x)
{
	rotate_right(avl_tree,node_x->right);
	return rotate_left(avl_tree,node_x);
}

static void 
rebalance(c_avl_tree_t *avl_tree,c_avl_node_t *avl_node)
{
	int b1;
	int b2;

	while(avl_node != NULL)
	{
		b1 = calc_balance(avl_node);
		assert( b1 >= -2 && b1 <=2 );

		if( b1 == -2 )
		{
			assert(avl_node != NULL);
			b2 = calc_balance(avl_node->right);
			assert( b2 >= -1 && b2 <=1 );
			if( b2 == 1 )
			 avl_node = rotate_right_left(avl_tree,avl_node);
			else
				avl_node = rotate_left(avl_tree,avl_node);
		}else if(b1 == 2)
		{
			assert(avl_node != NULL);
			b2 = calc_balance(avl_node->left);
			assert( b2 >= -1 && b2 <=1 );
			if( b2 == 1 )
				avl_node = rotate_right(avl_tree,avl_node);
			else
				avl_node = rotate_left_right(avl_tree,avl_node);
		}else{
			int height = calc_balance(avl_node);
			if(height == avl_node->height)//子节点改变会导致parent节点的改变，见上面4个图
				break;
			avl_node->height = height;
		}
    
		assert(avl_node->height == calc_balance(avl_node));//旋转后的高节点的高度并不会改变，详细见上四个图
		avl_node = avl_node->parent;
	}
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

int
c_avl_insert(c_avl_tree_t *avl_tree,void *key,void *value)
{
	c_avl_node_t *new;
	c_avl_node_t *index;
	int comp;

	if( (new = (c_avl_node_t *)malloc(sizeof(c_avl_node_t))) == NULL)
	{
		printf("malloc c_avl_node_t failed \n");
		return;
	}

	new->key = key;
	new->value = value;
	new->height = 1;
	new->left = NULL;
	new->right = NULL;

	if( avl_tree->root == NULL )
	{
		new->parent == NULL;
		avl_tree->root = new;
		avl_tree->size = 1;
		return 0;
	}

	index = avl_tree->root;

	while(1)
	{
		comp = avl_tree->compare(index->key,new->key);
		if(comp == 0)
		{
			free_node(new);
			return 1;
		}else if(comp < 0)
		{
			if(index->right == NULL)
			{
				index->right = new;
				new->parent = index;
				rebalance(avl_tree,index);
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
				rebalance(avl_tree,index);
			}else
			{
				index = index->left;
			}
		}
	}/*while(1)*/

	verify_tree(avl_tree);
	avl_tree->size++;
	return 0;
}




int main(){
	return 0;
}
