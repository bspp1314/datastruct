#include<stdio.h>
#include<malloc.h>
#include"binomial_heap.h"
/*注:<>下标 []上标
 * 二项树
 *                     (*)
 *                    / |
 *                   /  |
 *       (*)       (*) (*)
 *        |        |
 *        |        |
 * (*)   (*)       (*)
 * B<0>  B<1>     B<2>
 * 二项树的性质
 * a  B<k>节点共有2[k]个节点 
 * b  B<k>节点的高度为k
 * c  B<k>在深度i出恰好有C<(k,i)>个节点，其中i = 0，1，2，3 .....k
 * d  根的度数为k,它大于任何其他节点的度数，节点的度数是该节点
 * 二项堆
 * 二项堆是一组二项树的集合
 * 每棵二项树都满足最小堆性质。即，父节点的关键字 <= 它的孩子的关键字
 * 不能有两棵或以上的二项树具有相同的度数(包括度数为0)。换句话说，具有度数k的二项树有0个或1个。
 */

/* 将连个二项堆所在的节点链表合并成一个节点链表,并按照其度的大小排序 */
static heap_node_t* heap_merge(heap_node_t *node1,heap_node_t *node2)
{
	heap_node_t *head = NULL;
	heap_node_t **pos = &head;

	while(node1 && node2)
	{
			if(node1->degree < node2->degree)
			{
				*pos = node1;
				node1 = node1->next;
			}else
			{
				*pos = node2;
				node2 = node2->next;
			}
	
		pos = &(*pos)->next;//存放节点next指针所在的地址
	}

	if(node1)
		*pos = node1;
	else
		*pos = node2;
	return head;
}

/* 合并两个二项树 */
static void heap_link(heap_node_t *node1,heap_node_t *node2)
{
	node1->parent = node2;
	node1->next = node2->left;
	node2->left = node1;
}

/* 合并而项堆 */
static heap_node_t* heap_union(heap_node_t *node1,heap_node_t *node2,
		int (*compare)(const void *,const void *))
{
	heap_node_t *heap = NULL;
	heap_node_t *pre = NULL;
	heap_node_t *cur = NULL;
	heap_node_t *next = NULL;

	heap = heap_merge(node1,node2);

	if(heap == NULL)
		return NULL;

	pre = NULL;
	cur = heap;
	next = cur->next;
	while(next != NULL)
	{
		if(next->degree != cur->degree 
				|| ( next->next != NULL && next->degree == next->next->degree))
		{
			//case1 cur->degree != next->degree
			//case2 cur->degree == next->degree == next->next->degree
			pre = cur;
			cur = next;
		}else if(compare(cur->key,next->key) <= 0)
		{
			//case3 cur->degree == next->degree != next->next->degree
			// and cur->key <= next->key
			cur->next = next->next;
			heap_link(next,cur);
		}else
		{
			//case3 cur->degree == next->degree != next->next->degree
			// and cur->key > next->key
			if(pre == NULL)
				heap = next;
			else
				pre->next = next;

			heap_link(cur,next);
			cur = next;
		}
		next = cur->next;
	}

	return heap;
}

c_binomial_heap_t *c_binomial_heap_union(c_binomial_heap_t *heap1,
		c_binomial_heap_t *heap2)
{
	if(heap1->compare = heap2->compare)
	{
		printf("heap1->compar must equal heap2->");
		return NULL;
	}

	if(heap1 == NULL)
		return heap2;

	if(heap2 == NULL)
		return heap1;

	heap1->root = heap_union(heap1->root,heap2->root,heap1->compare); 
	heap1->size += heap2->size;

	heap2->size = 0;
	heap2->root = NULL;
	return heap1;
}
int c_binomial_heap_insert(c_binomial_heap_t *heap,void *key)
{
	if(heap == NULL || key == NULL)
		return -1;

	heap_node_t *node = (heap_node_t *)malloc(sizeof(heap_node_t));
	if(node == NULL)
	{
		printf("malloc heap_node failed\n");
		return -1;
	}

	node->degree = 0;
	node->left = NULL;
	node->parent = NULL;
	node->next = NULL;
	node->key = key;

	heap->root = heap_union(heap->root,node,heap->compare);
	heap->size++;
}

static heap_node_t *heap_reverse(heap_node_t *node)
{
	heap_node_t *tail = NULL;
	heap_node_t *next;

	if(node == NULL)
		return NULL;

	node->parent = NULL;
	while(node->next != NULL)
	{
		next = node->next;
		node->next = tail;
		tail = node;
		node = next;
		node->parent = NULL;
	}
	node->next = tail;
	return node;
}
void  c_binomial_heap_delete(c_binomial_heap_t *heap)
{
	heap_node_t *min = NULL;
	heap_node_t *min_pre = NULL;
	heap_node_t *next = NULL;
	heap_node_t *next_pre = NULL;

	if(heap == NULL || heap->root == NULL)
		return;

	min = heap->root;
	next = min->next;
	next_pre = min;

	while(next != NULL)
	{
		if(heap->compare(min->key,next->key) > 0)
		{
			min_pre = next_pre;
			min = next;
		}
		next_pre = next;
		next = next->next;
	}/*查找最小的节点*/

	if(min_pre != NULL)
		min_pre->next = min->next;
	else
		heap->root = min->next;
 
	heap->root = heap_union(heap->root,heap_reverse(min->left),
			heap->compare);
	free(min);
	heap->size--;
}

int main()
{
	heap_node_t node1 = {0};
	heap_node_t node2 = {0};
	node1.degree = 1;
	node2.degree = 2;
	heap_merge(&node1,&node2);
}

