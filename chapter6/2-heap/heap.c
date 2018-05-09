#include<malloc.h>
#include"heap.h"
/* 2 叉堆得性质
 * 2 叉堆是一个完成2叉树
 * 2 叉堆任一节点的其左右子树的所有节点值都比它小
 */
heap_t *c_heap_create(int capacity,int (*compare)(const void *,const void *))
{
	heap_t *heap = NULL;
	if(capacity <= 0)
	{
		printf("heap capacity must > 0\n");
		return NULL;
	}
	heap = (heap_t *)malloc(sizeof(heap_t));
	if(heap == NULL)
	{
		printf("malloc heap failed");
		return NULL;
	}
	heap->nodes = (node_t *)malloc(sizeof(heap_t) * capacity);
	if(heap->nodes == NULL)
	{
		printf("malloc heap->nodes failed \n");
		free(heap);
		return NULL;
	}

	heap->size = 0;
	heap->capacity = capacity;
	heap->compare = compare;
	return heap;
}

void *c_heap_destroy(heap_t *heap)
{
	if(heap == NULL)
		return NULL;
}

/* 首个节点的索引为0
 * node i 
 * node->parent (i-1) >> 1
 * node->left   (i << 1) + 1;
 * node->right  (i << 1) + 2;
 *  
 *
 */
static void insert_fixup(heap_t *heap,int index)
{
	int c = index;
	int p = (c -1) >> 1;
	node_t temp = heap->nodes[c];

	while(c > 0)
	{
		if(heap->compare(heap->nodes[p].key,temp.key) > 0)
			break;
		else
		{
			heap->nodes[c] = heap->nodes[p];
			c = p ;
			p = (c -1) >> 1;
		}
	}
	heap->nodes[c] = temp;
}
int c_heap_insert(heap_t *heap,void *key,void *value)
{
	if(heap == NULL || heap->capacity == 0 || key == NULL)
		return -1;

	if(heap->size == heap->capacity)
	{
		printf("heap->capatiy == heap->size\n");
		return -1;
	}

	heap->nodes[heap->size].key = key;
	heap->nodes[heap->size].value = value;

	insert_fixup(heap,heap->size);
	heap->size++;
	return 0;
}

static int get_index(heap_t *heap,void *key)
{
 int index  = -1;
	int i = 0;

	for(i = 0 ; i < heap->size;i++)
	{
		if(heap->compare(heap->nodes[i].key,key) == 0)
		{
			index = i;
			break;
		}		
	}

	return index;
}
static void remove_fixup(heap_t *heap,int index,int end)
{
	int c = index;/*cureent node*/
	int l = (c  << 1 )+ 1;/*cureent left node*/
	node_t temp = heap->nodes[c];

	while(l <= end)
	{
		if(l < end && heap->compare(heap->nodes[l].key,heap->nodes[l+1].key) < 0)
			l++;

		if(heap->compare(temp.key,heap->nodes[l].key) >= 0)
			break;
		else
		{
			heap->nodes[c] = heap->nodes[l];
			c  = l;
			l = (c << 1 ) + 1;
		}
	}

	heap->nodes[c]  = temp;
}
int c_heap_remove(heap_t *heap,void *key,void **rkey,void **rvalue)
{
		int index = 0;

		if(heap == NULL || key == NULL)
			return -1;

		if((index = get_index(heap,key)) < 0)
				return -1;

		if(rkey != NULL)
		{

			*rkey = heap->nodes[index].key;
		}

		if(rvalue != NULL)
			*rvalue = heap->nodes[index].value;

		heap->nodes[index] = heap->nodes[--heap->size];
		remove_fixup(heap,index,--heap->size);
		return 0;
}



