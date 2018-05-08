#include <stdio.h>
#include <assert.h>
#include <malloc.h>
#include "rb_tree.h"

/* the NULL node of tree */
#define _NULL(rbtree) (&((rbtree)->null))

static c_rb_node_t* rotate_right(c_rb_tree_t *tree,c_rb_node_t *node_x);
static c_rb_node_t* rotate_left(c_rb_tree_t *tree, c_rb_node_t *node_x);
static void c_rbtree_insert_current(c_rb_tree_t *tree, c_rb_node_t *node);

#define rbnode_color(rbnode)                        \
	(rbnode == NULL) ? BLACK : (node->color)        

#define rbnode_set_black(rbnode)   ((rbnode)->color = BLACK)
#define rbnode_set_red(rbnode)     ((rbnode)->color = RED)

#define rbnode_is_red(rbnode)   \
	(rbnode == NULL) ? 0:(rbnode->color == RED)
#define rbnode_is_black(rbnode)   \
	(rbnode == NULL) ? 1:(rbnode->color == BLACK)
	
static free_node(c_rb_node_t *node)
{
	if(node == NULL)
		return;

	free_node(node->left);
	free_node(node->right);
	free(node);
	node = NULL;
}

/*         (x)                            (y)
 *        /   \                          /   \
 *    (y)     (c)											 (a)    (x) 
 *   /    \                                  /    \
 * (a)    (b)																 b     c
 *  右旋
 *
 */

static c_rb_node_t* search_node(c_rb_node_t *node, 
		const void *key,int(*compare)(const void *,const void *))
{
	c_rb_node_t *result_node = NULL;
	int comp = 0;

	assert(compare != NULL);

	if( node == NULL)
		return NULL;

	comp = compare(key,node->key);
	if( comp  < 0) // 要搜索的node是该节点的左子树
		result_node = search_node(node->left,key,compare);
	else if (comp > 0)
		result_node = search_node(node->right,key,compare);
	else
		result_node = node;

	return result_node;
}

static c_rb_node_t *search_tree(c_rb_tree_t *tree, const void *key)
{

	if( tree == NULL )
		return NULL;

	return search_node(tree->root,key,tree->compare);
}
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

static void c_rbtree_insert_fixup(c_rb_tree_t *tree, c_rb_node_t *node)
{
	c_rb_node_t *parent;
	c_rb_node_t *uncle;

	assert(node->parent != NULL);
	assert(node->parent->parent != NULL);
	assert(tree != NULL);


	while(rbnode_is_red(node)){
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
					parent = parent->parent;
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
					parent = parent->parent;
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
static c_rb_node_t* left_max(c_rb_node_t *node)
{
	if(node == NULL)
		return NULL;
	
	while(node->right != NULL)
		node = node->right;

	return node;
}/* max value in the node left tree*/
static c_rb_node_t* right_min(c_rb_node_t *node)
{
	if(node == NULL)
		return NULL;
	
	while(node->right != NULL)
		node = node->right;

	return node;
}/* min value in the node right tree*/

c_rb_tree_t* until_rbtree_create()
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

	return tree;
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
	new->parent = NULL;
	new->left = NULL;
	new->right = NULL;

	if(tree->root == NULL){/* rbtree is empty */
		tree->root = new;
		rbnode_set_black(new);
		tree->size++;
		return 1;
	}

	index = tree->root;
	while(1){
		comp = tree->compare(index->key,new->key);
		if(comp == 0){
			free_node(new);
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
  // 如果当前节点父节点为黑色的话，就什么都不用做
	if(rbnode_is_red(new->parent))
		c_rbtree_insert_fixup(tree,new);

	return 1;
}
void c_rbtree_destroy(c_rb_tree_t *tree)
{
	if(tree == NULL)
		return;
	
	free_node(tree->root);
	free(tree);
	tree = NULL;
}

static c_rbtree_transplant(c_rb_tree_t *tree,c_rb_node_t *u,c_rb_node_t *v)
{
	if(u->parent == NULL)
		tree->node = v;
	else if(u == u->parent->left)
		u->parent->left = v;
	else if(u.parent.right == v)
		v.parent = u.parent;
}
static int _remove(c_rb_tree_t *tree,c_avl_node_t *node)
{
	int isblack;
	c_rb_node_t *temp = NULL;
	c_rb_node_t *subst = NULL;

	if(tree == NULL || node == NULL)
		return -1;

	tree->size--;

	if(node->left == NULL){
		temp = node;
		subst = node->right;
	}else if(node->right == NULL){
		temp = node;
		subst = node->left;
	}else{
		temp = left_max(node->left);//get the node left child max value
		if(temp->left != NULL)
			subst = temp->left;
	}

	if( temp == tree->root )//if temp is root,node->left == NULL | node->right == NULL
	{
		tree->root = subst;
		if(tree->root != NULL)
			rbnode_set_black(tree->root);
		subst->parent = NULL;
		free_node(subst);
		return;
	}

	isblack = rbnode_is_black(temp);

}


int main(){
	return 0;
}

324     temp = node;

