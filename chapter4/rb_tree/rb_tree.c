#include <stdio.h>
#include <assert.h>
#include <malloc.h>
#include "rb_tree.h"

/* the NULL node of tree */
#define _NULL(rbtree) (&((rbtree)->null))

static c_rb_node_t* rotate_right(c_rb_tree_t *tree,c_rb_node_t *node_x);
static c_rb_node_t* rotate_left(c_rb_tree_t *tree, c_rb_node_t *node_x);
static void c_rbtree_insert_fixup(c_rb_tree_t *tree, c_rb_node_t *node);

//#define rbnode_set_black(rbnode)   ((rbnode)->color = BLACK)
//#define rbnode_set_red(rbnode)     ((rbnode)->color = RED)

//#ifdef LLD
//#define rbnode_is_red(rbnode)   \
//	(rbnode == NULL) ? 0:(rbnode->color == RED)
//#define rbnode_is_black(rbnode)   \
//	rbnode == NULL ? 1:(rbnode->color == BLACK)
//#endif
//

void static rbnode_set_red(c_rb_node_t *rbnode)
{
	if(rbnode == NULL)
		return;
	rbnode->color = RED;
}

void static rbnode_set_black(c_rb_node_t *rbnode)
{
	if(rbnode == NULL)
		return;
	rbnode->color = BLACK;
}
static  rbnode_is_red(c_rb_node_t *rbnode)
{
	return rbnode == NULL ? 0:(rbnode->color == RED);
}
static  rbnode_is_black(c_rb_node_t *rbnode)
{
	return rbnode == NULL ? 1:(rbnode->color == BLACK);
}


/*         (x)                            (y)
 *        /   \                          /   \
 *    (y)     (c)											 (a)    (x) 
 *   /    \                                  /    \
 * (a)    (b)																 b     c
 *  右旋
 *
 */
c_rb_node_t* c_rb_subtree_min(c_rb_node_t *node)
{
	if(node == NULL)
		return NULL;

	if(node->left != NULL)
		node = node->left;
}

c_rb_node_t* c_rb_subtree_max(c_rb_node_t *node){
	if(node == NULL)
		return NULL;

	if(node->right != NULL)
		node = node->right;
}
static void free_node(c_rb_node_t *node)
{
	if(node == NULL)
		return ;

	if(node->left != NULL)
		free_node(node->left);
	else
		free_node(node->right);
	free(node);
}
static c_rb_node_t* search_node(c_rb_node_t *node, 
		const void *key,int(*compare)(const void *,const void *))
{
	c_rb_node_t *result = NULL;
	int comp = 0;

	assert(compare != NULL);

	if( node == NULL)
		return NULL;

	comp = compare(key,node->key);
	if( comp  < 0) // 要搜索的node是该节点的左子树
		result = search_node(node->left,key,compare);
	else if (comp > 0)
		result = search_node(node->right,key,compare);
	else
		result = node;

	return result;
}

static c_rb_node_t *search_tree(c_rb_tree_t *rbtree, const void *key)
{

	if( rbtree == NULL )
		return NULL;

	return search_node(rbtree->root,key,rbtree->compare);
}
/*         (x)                            (y)
 *        /   \                          /   \
 *    (3y)     (1c)                   (2a)    (2x) 
 *   /    \                                  /    \
 * (2a)    (1b)                            1b     1c
 *  右旋
 *
 */
static c_rb_node_t* rotate_right(c_rb_tree_t *rb_tree, c_rb_node_t *node_x)
{
	c_rb_node_t *node_y = NULL;
	c_rb_node_t *node_b = NULL;
	c_rb_node_t *node_parent = NULL;

	if(node_x == NULL || rb_tree == NULL || node_x->left == NULL)
		printf("rotate_right error \n");

	assert(node_x != NULL);
	assert(rb_tree != NULL);
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
		rb_tree->root = node_y;
	else
	{
		if(node_parent->left == node_x)
			node_parent->left = node_y;
		else 
			node_parent->right = node_y;
	}

	return node_y;
}
/*
 *    (x)                        (y)             
 *   /   \                      /   \
 *(1a)    (3y)              (2x)     (2c)
 *        /   \            /    \
 *       (1b)  (2c)      1a     1b 
 */
static c_rb_node_t* rotate_left(c_rb_tree_t *rb_tree, c_rb_node_t *node_x)
{ 
	c_rb_node_t *node_y;
	c_rb_node_t *node_parent;
	c_rb_node_t *node_b;

	if(node_x == NULL || rb_tree == NULL || node_x->right == NULL)
		printf("rotate_left error \n");

	assert(node_x != NULL);
	assert(rb_tree != NULL);
	assert(node_x->right !=  NULL);

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

	if( node_parent == NULL)
		rb_tree->root = node_y;
	else
	{
		if(node_parent->left == node_x)
			node_parent->left = node_y;
		else 
			node_parent->right = node_y;
	}

	return node_y;
}

static void insert_fixup(c_rb_tree_t *tree, c_rb_node_t *node)
{
	c_rb_node_t *parent;
	c_rb_node_t *uncle;

	while(rbnode_is_red(node->parent)){
		parent = node->parent;
		if(parent == parent->parent->left){
			uncle = parent->parent->right;

			if(rbnode_is_red(uncle)){  /* case 1 p , u is rea*/
				rbnode_set_black(parent);
				rbnode_set_black(uncle);
				rbnode_set_red(parent->parent);
				node = parent->parent;
			}else{
				if(node == parent->right) {/* case 2 p is read u:black,node is right child */
					node = parent;
					rotate_left(tree,node);
					parent = node->parent;
				}
				/* case 3  p red u black node is left */
				rbnode_set_black(parent);
				rbnode_set_red(parent->parent);
				rotate_right(tree,parent->parent);
			}
		}else{/* parent is the right child */
			uncle = parent->parent->left;
			if(rbnode_is_red(uncle)){
				rbnode_set_black(parent);
				rbnode_set_red(parent->parent);
				node = parent->parent;
			}else{
				if(node == parent->left){
					node = parent;
					rotate_right(tree,node);
					parent = node->parent;
				}
				rbnode_set_black(parent);
				rbnode_set_red(parent->parent);
				rotate_left(tree,parent->parent);
			}
		}
	}

	/* set root to black */
	rbnode_set_black(tree->root);
}

c_rb_tree_t *c_rbtree_create(int(*compare)(const void *,const void *))
{
	c_rb_tree_t *tree  = NULL;

	tree  = (c_rb_tree_t *)malloc(sizeof(c_rb_tree_t));
	if(tree == NULL)
	{
		printf("malloc new tree failed \n");
		return NULL;
	}
	tree->root = NULL;
	tree->size = 0;
	tree->compare = compare;

	return tree;
}
void c_rbtree_destroy(c_rb_tree_t *rbtree)
{
	if(rbtree == NULL)
		return;
	free_node(rbtree->root);
}
int c_rbtree_insert(c_rb_tree_t *tree,void *key,void *value)
{
	c_rb_node_t *new = NULL;
	c_rb_node_t *index = NULL;
	int comp = 0;

	if(tree == NULL || key == NULL)
		return 0;

	new = (c_rb_node_t *)malloc(sizeof(c_rb_node_t));
	if(new == NULL){
		printf("malloc new node failed \n");
		return 0;
	}

	new->color = RED;
	new->key = key;
	new->value = value;

	if(tree->root == NULL){/* rbtree is empty */
		new->color = BLACK;
		tree->root = new;
		new->parent = NULL;
	}else{
		index = tree->root;
		while(1){
			comp = tree->compare(index->key,new->key);
			if(comp == 0){
				free(new);
				return 1;
			}else if( comp < 0 ){/* index < new*/
				if(index->right == NULL){
					index->right = new;
					new->parent = index;
					break;
				}else{
					index = index->right;
				}
			}else{
				if(index->left == NULL){
					index->left = new;
					new->parent = index;
					break;
				}else{
					index = index->left;
				}
			}	
		}
	}
	new->left = NULL;
	new->right = NULL;
	if(rbnode_is_red(new->parent))
		insert_fixup(tree,new);

	return 1;
}
/*case 1
 *   A brother is red
 *   set B red,set D black,left B
 *   set new Brohter = C
 *                                  
 *        (+) B                         (+) D
 *      /     \                       /     \
 *  A (+)     (-) D               B (-)      (+) F 
 *	  / \     /  \                 /   \
 *         E (+) (+) F        A  (+)    (+) C
 *
 *
 *case 2
 *   A brother D is black,
 *   and D left child and right child is black
 *   set A parent red,send new parent = B 
 *                                  
 *        (+-) B                       (+-) B
 *      /     \                       /     \
 *  A (+)     (+) D               A (+)      (+) D 
 *	  / \     /  \                          /   \
 *         E (+) (+) F                  A (+)    (+) C
 *
 *
 *case 3
 *   A brother D is black,
 *   and D left child is red and right child is black
 *   set left 
 *                                  
 *        (+-) B                        (+-) B
 *      /     \                       /     \
 *  A (+)     (-) D               A (+)      (+) E 
 *	  / \     /  \                          /   \
 *        E (-)  (+) F                          (-) D
 *                                              /  \
 *                                                  (+) F
 *
 *case 4
 *   A brother D is black,
 *   and D left child is red and right child is black
 *   set left 
 *                                  
 *        (+-) B                        (+-) D
 *      /     \                       /     \
 *  A (+)     (+) D               B (+)      (-) F 
 *	  / \     /  \                  /  \
 *        E (+-) (-) F          A (+)  E(+-)          
 *                                              
 *                                            
 */
void  remove_fixup(c_rb_tree_t *rbtree,c_rb_node_t *node)
{
	c_rb_node_t *brother = NULL;

	while((node != rbtree->root) && rbnode_is_black(node))
	{
		if(node == node->parent->left)
		{
			brother = node->parent->right;
			if(rbnode_is_red(brother))/* brother is red*/
			{
				rbnode_set_black(brother);
				rbnode_set_red(node->parent);
				rotate_left(rbtree,node);
				brother = node->parent->right;
			}

			if(rbnode_is_black(brother->right) && rbnode_is_black(brother->left))
			{
				rbnode_set_red(brother);
				node = node->parent;
			}else
			{
				if(rbnode_is_black(brother->right))
				{
					rbnode_set_black(brother->left);
					rbnode_set_red(brother);
					rotate_right(rbtree,brother);
					brother = node->parent->right;
				}

				brother->color = node->parent->color;
				rbnode_set_black(node->parent);
				rbnode_set_black(brother->right);
				rotate_left(rbtree,node->parent);
				node = rbtree->root;/* break loop*/
			}
		}else/* node is right child*/
		{
			brother = node->parent->left;

			if(rbnode_is_red(brother))/*case1: brother is red*/
			{
				rbnode_set_black(brother);
				rbnode_set_red(node->parent);
				rotate_right(rbtree,node);
				brother = node->parent->left;
			}

			/* case 2 b is black and b->left is black and b->right is black*/
			if(rbnode_is_black(brother->right) && rbnode_is_black(brother->left))
			{
				rbnode_set_red(brother);
				node = node->parent;
			}else
			{
				/* case 3 is black and b->left is black and b->right is red*/
				if(rbnode_is_black(brother->left))
				{
					rbnode_set_black(brother->right);
					rbnode_set_red(brother);
					rotate_left(rbtree,brother);
					brother = node->parent->left;
				}

				brother->color = node->parent->color;
				rbnode_set_black(node->parent);
				rbnode_is_black(brother->left);
				rotate_right(rbtree,node->parent);
				node = rbtree->root;/* break loop*/
			}
		}
	}
	rbnode_is_black(node);
}
static void transplant(c_rb_tree_t *rbtree,c_rb_node_t *node1,c_rb_node_t *node2)
{
	if(node1->parent == NULL)
		rbtree->root = node2;
	else if(node1->parent->left == node1)
		node1->parent->left = node2;
	else
		node1->parent->right = node2;

	if(node2 != NULL)
		node2->parent = node1->parent;
}

static void _remove(c_rb_tree_t *rbtree,c_rb_node_t *node)
{
	color_t color;
	c_rb_node_t *x;

	if((rbtree == NULL) || (node) == NULL) 
		return;


	if((node->left != NULL) && (node->right != NULL))
	{
		c_rb_node_t *min = c_rb_subtree_min(node->right);
		node->key = min->key;
		node->value = min->value;
		node = min;
	}

	if((node->left == NULL) && (node->right == NULL))
	{
		if(node == rbtree->root)
		{
			free(node);
			rbtree->size--;
#if DEBUG
			assert(rbtree->size == 0);
#endif
			return;
		}
		x = node->parent;
	}else if(node->left == NULL)
	{
		x = node->right;
		transplant(rbtree,node,node->left);
	}else
	{
		x = node->right;
		transplant(rbtree,node,node->right);
	}

	color = rbnode_is_black(node);
	free(node);
	rbtree->size--;

	if(color == BLACK)
		remove_fixup(rbtree,node);

}
void c_rbtree_remove1(c_rb_tree_t *rbtree,void const *key,void **rkey,void **rvalue)
{
	c_rb_node_t *node;

	assert(rbtree != NULL);
	node = search_tree(rbtree,key);
	if(node == NULL)
		return;

	if(rkey != NULL)
		*rkey = node->key;
	if(rvalue != NULL)
		*rvalue = node->value;

	 _remove(rbtree,node);
}

void c_rbtree_remove2(c_rb_tree_t *rbtree,c_rb_node_t *node)
{
	_remove(rbtree,node);
}



