#include<malloc.h>
#include<stdio.h>
#include"left_heap.h"

/*左堆得性质
 * a 节点的键值小于或等于它的左右节点（注:如果是大根堆则是相反）
 * b 节点的左孩子的NPL >= 右孩子的NPL
 * c 节点的NPL =  它的右孩子的NPL + 1
 * 注:NPL(NULL Path Length) 从一个节点到其子孙节点第一个不满节点的距离，
 * 满节点:一个节点的左右子树都存在
 */

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

/* 按照中序遍历获取某其next节点 */
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
			 *         &0                  root( node 没有next节点 )
			 *       /    \               /   \
			 *      &1                         &0
			 *    /  \                          \
			 *        &2                         &1
			 *          \                          \
			 *           &3                         &2
			 *            \                           \
			 *             &4                          node
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
			return result;
	}else
	{
		result = node->right;
		while(result->left != NULL)
			result = result->left;
	}
	return result;
}

/* 按照反中序遍历（右中左）获取某其pre节点 */
node_t *c_left_heap_pre(node_t *node)
{

	node_t *result;

	if(node == NULL)
		return NULL;

	if(node->left == NULL)
	{
		result = node->parent;
		/*            &0                           root (node 没有pre 节点)       
		 *              \                          /
		 *               &1                       &1
		 *              /                        /
		 *             &2                       &2
		 *            /                       /
		 *           &3                     &3
		 *          /                      /
		 *         &4                     node
		 *        /
		 *      node
		 *        \
		 */
		while(result != NULL && result->parent != NULL)
		{
			if(result->right == node)/*如果该节点是右节点，结束循环*/
				break;
			node = result;
			result = node->parent;
		}

		if(result== NULL || result->parent == NULL)
			return NULL;
		else
			return result;
	}else
	{
		result = node->left;
		while(result->right != NULL)
			result = result->right;
	}
	return result;
}

c_left_heap_t* c_left_heap_create(int(*compare)(const void *,const void *))
{
	c_left_heap_t *heap = NULL;

	if(compare == NULL)
	{
		printf("compare function not be null\n");
		return NULL;
	}

	heap = (c_left_heap_t *) malloc(sizeof(c_left_heap_t));
	if(heap == NULL)
	{
		printf("malloc c_left_heap tree failed\n");
		return NULL;
	}

	heap->root = NULL;
	heap->size = 0;
	heap->compare = compare;

	return heap;
}

void c_left_heap_destroy(c_left_heap_t *heap)
{
	if(heap == NULL)
		return;

	free_node(heap->root);
	free(heap);
	heap = NULL;
}

int c_left_heap_insert(c_left_heap_t *heap,void *key,void *value)
{
	node_t *new;

	if(heap == NULL || key == NULL)
		return -1;

	if( (new = (node_t *)malloc(sizeof(node_t))) == NULL)
	{
		printf("malloc c_left_heap failed \n");
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


c_left_heap_t *c_merge_left_heap(c_left_heap_t *h1,c_left_heap_t *h2)
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

	h2->root = NULL;
	h2->size = 0;

	return h1;
}
void c_left_heap_remove(c_left_heap_t *heap)
{
	if(NULL == heap || 0 == heap->size)
		return;

	node_t *left_node = heap->root->left;
	node_t *right_node = heap->root->right;

	left_node->parent = NULL;
	right_node->parent = NULL;

	free(heap->root);
	merge_left(right_node,left_node,heap->compare);
}
c_left_heap_iterator_t *c_left_heap_iter_create(c_left_heap_t *heap)
{
	c_left_heap_iterator_t *iter = NULL;

	if(NULL == heap || 0 == heap->size)
		return NULL;

	iter = ( c_left_heap_iterator_t * )malloc(sizeof(c_left_heap_iterator_t));
	if(iter == NULL)
	{
		printf("malloc iter failed \n");
		return NULL;
	}

	iter->heap = heap;
	iter->node = NULL;

	return iter;
}

int c_left_heap_iterator_next(c_left_heap_iterator_t *iter,void **key, void **value) 
{
	node_t *node;

	if(iter == NULL || iter->heap == NULL)
		return -1;

	if(iter->node == NULL)
	{
		node =iter->heap->root;
		while(node != NULL && node->left != NULL)
			node = node->left;
	}else
	{
		node = c_left_heap_next(iter->node);
	}

	iter->node = node;

	if(key != NULL)
		*key = node->key;

	if(value != NULL)
		*value = node->value;
	return 0;
}

int c_left_heap_iterator_pre(c_left_heap_iterator_t *iter,void **key, void **value) 
{
	node_t *node;

	if(iter == NULL || iter->heap == NULL)
		return -1;

	if(iter->node == NULL)
	{
		node =iter->heap->root;
		while(node != NULL && node->right != NULL)
			node = node->right;
	}else
	{
		node = c_left_heap_pre(iter->node);
	}

	iter->node = node;

	if(key != NULL)
		*key = node->key;

	if(value != NULL)
		*value = node->value;
	return 0;
}



