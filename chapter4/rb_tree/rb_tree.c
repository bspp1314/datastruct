#include <stdio.h>
#include <assert.h>
#include <malloc.h>
#include "rb_tree.h"

/* the NULL node of tree */
#define _NULL(rbtree) (&((rbtree)->null))

static c_rb_node_t* rotate_right(c_rb_tree_t *tree,c_rb_node_t *node_x);
static c_rb_node_t* rotate_left(c_rb_tree_t *tree, c_rb_node_t *node_x);
static void c_rbtree_insert_fixup(c_rb_tree_t *tree, c_rb_node_t *node);

#define rbnode_set_black(rbnode)   ((rbnode)->color = BLACK)
#define rbnode_set_red(rbnode)     ((rbnode)->color = RED)

#define rbnode_is_red(rbnode)   \
	 rbnode->color == RED
#define rbnode_is_black(rbnode)   \
	rbnode->color == BLACK


/*         (x)                            (y)
 *        /   \                          /   \
 *    (y)     (c)											 (a)    (x) 
 *   /    \                                  /    \
 * (a)    (b)																 b     c
 *  右旋
 *
 */
c_rb_node_t* c_rb_subtree_min(c_rb_node_t *node, c_rb_node_t *sentinel)
{
	if(node == sentinel)
		return NULL;

	if(node->left != sentinel)
		node = node->left;
}

c_rb_node_t* c_rb_subtree_max(c_rb_node_t *node, c_rb_node_t *sentinel){
	if(node == sentinel)
		return NULL;

	if(node->right != sentinel)
		node = node->right;
}
static c_rb_node_t* rotate_right(c_rb_tree_t *tree,c_rb_node_t *node_x)
{

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

	if(node_b != _NULL(tree))
		node_b->parent = node_y;

	if(node_parent == _NULL(tree))
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

	if(node_b != _NULL(tree))
		node_b->parent = node_x;

	if(node_parent == _NULL(tree))
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

c_rb_tree_t* until_rbtree_create()
{
	c_rb_tree_t *tree  = NULL;

	tree  = (c_rb_tree_t *)malloc(sizeof(c_rb_tree_t));
	if(tree == NULL)
	{
		printf("malloc new tree failed \n");
		return NULL;
	}
	rbnode_set_black(_NULL(tree));
	tree->root = _NULL(tree);
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

	if(tree->root == _NULL(tree)){/* rbtree is empty */
		tree->root = new;
		new->parent = _NULL(tree);
	}else{
		index = tree->root;
		while(1){
			comp = tree->compare(index->key,new->key);
			if(comp == 0){
				free(new);
				return 1;
			}else if( comp < 0 ){/* index < new*/
				if(index->right == _NULL(tree)){
					index->right = new;
					new->parent = index;
					break;
				}else{
					index = index->right;
				}
			}else{
				if(index->left == _NULL(tree)){
					index->left = new;
					new->parent = index;
					break;
				}else{
					index = index->left;
				}
			}	
		}
	}
	// 如果当前节点父节点为黑色的话，就什么都不用做
	new->left = _NULL(tree);
	new->right = _NULL(tree);
	if(rbnode_is_red(new->parent))
		c_rbtree_insert_fixup(tree,new);

	return 1;
}

static void _remove(c_rb_tree_t *rbtree,c_rb_node_t *node)
{
	int isblack;
	c_rb_node_t *temp;
	c_rb_node_t *subst;

	if((rbtree == NULL) || (node) == NULL || node == _NULL(rbtree)) 
		return;
	rbtree->size--;
	/* find deleted poistion,indicated by temp */
	if(node->left == _NULL(rbtree)){
		temp = node;
		subst = node->right;
	}else if(node->right == _NULL(rbtree)){
		temp = node;
		subst = node->right;
	}else
	{
		temp = c_rb_subtree_min(node->right,_NULL(rbtree)); 
		if(temp->left != _NULL(rbtree)){
			subst = temp->left;
		}else{
			subst = temp->right;
		}
	}

	if(temp == rbtree->root)
	{
		rbtree->root = subst;
		rbnode_set_black(subst);
		free(temp);
		temp = NULL;
		return;
	}

	isblack = rbnode_is_black(temp);
	if(temp->parent == node)
	{
		subst->parent = node;
	}else{
		subst->parent = parent;
	}

	if(temp == temp->parent->left)
	{
		temp->parent->left = subst;
	}else
	{
		temp->parent->right = subst;
	}

	if(temp != node)/* node maybe root */
	{
		temp->parent = node->parent;
		if(node == rbtree->temp)
		{
			rbtree->root = temp;
		}else
		{
			if(node->parent->left == node)
				node->parent->left = temp;
			else
				node->parent->right = temp;
		}
	}
	temp->right = node->right;
	temp->left = node->left;
	if(temp->left != _NULL(rbtee))
	{
		temp->left->parent = temp;
	}

	if(temp->left != _NULL(rbtee))
	{
		temp->left->parent = temp;
	}


}


int main(){
	return 0;
}


