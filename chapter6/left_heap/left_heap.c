#include<malloc.h>
#include<stdio.h>
#include"left_heap.h"

static void free_node(node_t *node)
{
	if(node == NULL)
		return;

	free_node(node->left);
	free_node(node->right);

	free(node);
	node = NULL;
}
static void swap_node(node_t *x, node_t *y)
{
	if(x == NULL || y == NULL)
		return;

	node_t temp = *x;
  *x = *y;
	*y = temp;
}
/*
 * a 如果一个非空左堆和一个非空左堆和并，返回非空左堆
 * b 如果一个左堆都为非空，比较两个根节点，取较小的根节点作为新根节点
 * c 如果新堆得右孩子的NPL > 左孩子的NPL,交换左右孩子
 * d 设置新堆得根节点的NPL = 右子堆得NPL + 1
 */
static node_t* merge_left(node_t *x,node_t *y,
		int (*compare)(const void *,const void *))
{

	if(compare == NULL)
	{
		printf("compare not be null\n");
		return NULL;
	}

	if(x == NULL)
		return y;

	if(y == NULL)
		return x;
	
	if(compare(x->key,y->key) > 0) /* x > y*/
			swap_node(x,y);

	//将x的右孩子和y和并
	x->right = merge_left(x->right,y,compare);
	if(x->right != NULL)
	{
		x->right->parent = x;
	}
		

  if(x->left == NULL || x->left->npl < x->right->npl)
	{
		//交换左右节点
		node_t *temp = x->left;
		x->left = x->right;
		x->right = temp;
	}

	//设置npl
	if(x->right == NULL || x->left == NULL)
		x->npl = 0;
	else
		x->npl = x->right->npl + 1;

}

node_t *c_left_heap_next(node_t *node)
{
	node_t *result;

	if(node == NULL)
		return NULL;

	if(node->right == NULL)/* 该节点的左子树为空，说明该节点的next是它祖父节点*/
	{
		result = node->parent;
		while((result != NULL) && result->parent != NULL)/* 回溯到根节点 */
		{

			  /*
				 *
				 *
				 *        root                root( node 没有next节点 )
				 *       /    \               /   \
				 *      &                          &
				 *    /  \                          \
				 *        &1                         &1
				 *          \                          \
				 *           &2                         &3
				 *            \                           \
				 *             &3                          node
				 *               \                        /
				 *                node                         
				 *               / 
				 */          
			if(result->left == node)/*如果该节点是左节点，结束循环*/
				break;
			node = result;
			result = node->parent;
		}
		if(result == NULL || result->parent == NULL)
			return NULL;
		else
			return node;
	}else
	{
		result = node->right;
		while(result->left != NULL)
			result = result->left;
	}
	return result;
}

left_heap_t* c_left_heap_create(int(*compare)(const void *,const void *))
{
	left_heap_t *heap = NULL;

	if(compare == NULL)
	{
		printf("compare function not be null\n");
		return NULL;
	}

	heap = (left_heap_t *) malloc(sizeof(left_heap_t));
	if(heap == NULL)
	{
		printf("malloc left_heap tree failed\n");
		return NULL;
	}

	heap->root = NULL;
	heap->size = 0;
	heap->compare = compare;

	return heap;
}

void c_left_heap_destroy(left_heap_t *heap)
{
	if(heap == NULL)
		return;

	free_node(heap->root);
	free(heap);
	heap = NULL;
}

int c_left_heap_insert(left_heap_t *heap,void *key,void *value)
{
	node_t *new;

	if(heap == NULL || key == NULL)
		return -1;

	if( (new = (node_t *)malloc(sizeof(node_t))) == NULL)
	{
		printf("malloc left_heap failed \n");
		return;
	}

	new->key = key;
	new->value = value;
	new->npl = 0;
	new->left = NULL;
	new->right = NULL;
	
	heap->root = merge_left(heap->root,new,heap->compare);
	heap->size++;
	return 0;
}


left_heap_t *c_merge_left_heap(left_heap_t *h1,left_heap_t *h2)
{
	if(h1->compare != h2->compare)
	{
		printf("h1->compare and h2->compare must equal\n");
		return NULL;
	}

	if(h1 == NULL)
		return h2;

	if(h2 == NULL)
		return h1;

	h1->root = merge_left(h1->root,h2->root,h1->compare);
	h1->size += h2->size;
	free(h2);
	return h1;
}
