#include<stdio.h>
#include<malloc.h>
#include<assert.h>
#include<math.h>
#include"fibonacci_heap.h"

/*
 *斐波那契堆是最小堆有序树的集合。
 * 
 */

/* 插入节点到一个堆中，直接将该节点插入根链表min节点之前即可,重置min节点。
 *
 */
#define LOG2(x) ((log((double)(x))) / (log(2.0)))
static fibonacci_node_t* create_node(void *key)
{
	fibonacci_node_t *node = NULL;

	if(key == NULL)
	{
		printf("create_node:key is null\n");
		return NULL;
	}

	node = (fibonacci_node_t *)malloc(sizeof(fibonacci_node_t));
	if(node == NULL)
	{
		printf("malloc fibonacci node failed\n");
		return NULL;
	}

	node->key = key;
	node->degree = 0;
	node->left = node;
	node->right = node;
	node->parent= NULL;
	node->child = NULL;

	return node;
}
/* 将单个节点node加入链表root之前*/
static void fibonacci_node_add(fibonacci_node_t *node,fibonacci_node_t *root)
{
	node->left = root->left;
	root->left->right = node;
	node->right = root;
	root->left = node;
}
/*         ------->    ------->          ->->->
 *  x->left         x            x->right      x                
 *         <------    <----------        <-<-<-
 *
 * *******************************************************      
 *          ------->   --------->         ->->->  
 *    y->left        y            y->right      y
 *          <--------   <--------         <-<-<-
 *
 **********************************************************
 *   ------------>           ->->->      ------------->         ->->->
 *   x               y->right         y                x->right        x
 *   <------------           <-<-<-     <--------------         <-<-<-
 *
 *将双向链表a添加到双向链表b之后
 */


static void fibonacci_node_cat(fibonacci_node_t *x,fibonacci_node_t *y)
{
	fibonacci_node_t *tmp;

	tmp = x->right;
	x->right = y->right;
	y->right->left = x;
	y->right = tmp;
	tmp->left = y;
}

static void fibonacci_node_remove(fibonacci_node_t *node)
{
	node->left->right = node->right;
	node->right->left = node->left;
}
int c_fibonacci_heap_insert(c_fibonacci_heap_t *heap,void *key)
{
	fibonacci_node_t *node = NULL;

	if(heap == NULL || key == NULL)
		return -1;

	node = create_node(key);
	if(node == NULL)
		return -1;

	if(heap->size == 0)
		heap->min_node = node;
	else
	{
		fibonacci_node_add(node,heap->min_node);
		if(heap->compare(heap->min_node,node) > 0)
			heap->min_node = node;
	}
	heap->size++;
}
c_fibonacci_heap_t* c_fibonacci_heap_union(c_fibonacci_heap_t *h1,
		c_fibonacci_heap_t *h2)
{
	if(h1 == NULL)
		return h2;

	if(h2 == NULL)
		return h1;

	if(h1->compare != h2->compare)
		return NULL;

	if(h1->min_node == NULL)//h1->size  == 0
	{
		assert(h1->size == 0);
		h1->min_node = h2->min_node;
		h1->size = h2->size;
		h1->max_degree = h2->max_degree;
		free(h2);
	}else if(h2->min_node == NULL)
	{
		assert(h2->size == 0);
		free(h2);
	}else
	{
		fibonacci_node_cat(h1->min_node,h2->min_node);

		if(h1->compare(h1->min_node->key,h2->min_node->key) > 0)
		   h1->min_node = h2->min_node;
		h1->size += h2->size;
		h1->max_degree = (h1->max_degree > h2->max_degree ? 
				h1->max_degree:h2->max_degree);
		free(h2);
	}

	return h1;
}
static void fibonacci_create_cons(c_fibonacci_heap_t *heap)
{
	if(heap == NULL)
		return;

	int old = heap->max_degree;
  heap->max_degree = LOG2(heap->max_degree) + 1;
	//log(heap->max_degree);

	if(old >= heap->max_degree)
		return;

	heap->cons = (fibonacci_node_t **)realloc(heap->cons,
			sizeof(fibonacci_node_t *) * (heap->max_degree) + 1);
	
}
static fibonacci_node_t *fibonacci_heap_remove_min(c_fibonacci_heap_t *heap)
{
	fibonacci_node_t *min_node = heap->min_node;
	if(heap->min_node == min_node->right)
		heap->min_node = NULL;
	else
	{
		fibonacci_node_remove(min_node);
		heap->min_node = min_node->right = min_node;
	}

	min_node->left = min_node->right = min_node;
	return min_node;
}
/**
 *
 *
 *
 *将y连接到x里面
 *y->key > x->key
 */
static  fibonacci_node_t* fibonacci_heap_link(c_fibonacci_heap_t *heap,
		fibonacci_node_t *x,fibonacci_node_t *y)
{
	if(heap == NULL || x == NULL || y == NULL)
		return NULL;

	if(heap->compare(x->key,y->key) > 0)
		return fibonacci_heap_link(heap,y,x);

	assert(heap->compare(x->key,y->key) < 0);

	//将x移除根链表
	fibonacci_node_remove(y);
	if(x->child == NULL)
		x->child = y;
	else
		fibonacci_node_add(y,x->child);

	y->parent = x;
	x->degree++;
	y->marked = 0;

	return x;
}

static void fibonacci_consolidata(c_fibonacci_heap_t *heap)
{
	if(heap == NULL)
		return;
	
  int d = 0;
	fibonacci_node_t *x = NULL;
	fibonacci_node_t *y = NULL;
	fibonacci_node_t *temp = NULL;

	fibonacci_create_cons(heap);
	for(int i = 0;i < heap->max_degree+1;i++)
		heap->cons[i] = NULL;

	while(heap->min_node != NULL)/*合并度相同的根节点，使得每个树的度都不相同*/
	{
		x = fibonacci_heap_remove_min(heap);
		d = x->degree;
		while(heap->cons[d] != NULL)
		{
			y = heap->cons[d]; // y 是和x具有相同度数相同的数
			x = fibonacci_heap_link(heap,x,y);
			heap->cons[d] == NULL;
			d++;
		}

		heap->cons[d] = x;
	}

	heap->min_node = NULL;

	for(int i = 0;i < heap->max_degree+1;i++)
	{
		if(heap->cons[i] != NULL)
		{
			if(heap->min_node == NULL)
				heap->min_node = heap->cons[i];
			else
			{
				fibonacci_node_add(heap->cons[i],heap->min_node);
				if(heap->compare(heap->min_node->key,heap->cons[i]) > 0)
					heap->min_node = heap->cons[i];
			}
		}
	}

}
fibonacci_node_t * c_fibonacci_heap_remove(c_fibonacci_heap_t *heap)
{
	if(heap == NULL || heap->min_node == NULL)
		return NULL;

	fibonacci_node_t *child = NULL;
	fibonacci_node_t *min_node = heap->min_node;

	while(min_node->child != NULL)
	{
		child = min_node->child;
		if(child->right == child)
			min_node->child = NULL;
		else
			min_node->child = child->right;

		fibonacci_node_remove(child);
		fibonacci_node_add(child,heap->min_node);
		child->parent = NULL;
	}

	//移除min
	fibonacci_node_remove(min_node);
	if(min_node == min_node->right)
		heap->min_node = NULL;
	else
		fibonacci_consolidata(heap);

	
}
void c_fibonacci_heap_extract_remove(c_fibonacci_heap_t *heap)
{
	fibonacci_node_t *node;
	if(heap == NULL || heap->min_node == NULL)
		return;

	node = c_fibonacci_heap_remove(heap);
	if(node != NULL)
		free(node);	
}

void c_fibonacci_heap_get_min(c_fibonacci_heap_t *heap,void **rkey)
{
	if(heap == NULL || heap->min_node == NULL || rkey == NULL)
		return;
	
	rkey = heap->min_node->key;
}

/*
 *在堆从查找键值为key的节点
 *
 */
static fibonacci_node_t *fibonacci_node_search(fibonacci_node_t *root,void *key,
		int (*compare)(const void *,const void *))
{
	fibonacci_node_t *tmp = root;
	fibonacci_node_t *p = NULL;

	if(key == NULL)
		return NULL;

	if(root == NULL)
		return root;

	do
	{
		if(compare(tmp->key,key) == 0)
		{
			p = tmp;
			break;
		}else
		{
			p = fibonacci_node_search(root->child,key,compare);
			if(p != NULL)
				break;
		}

		tmp = tmp->right;
	}while(tmp != root);

	return p;
}
 fibonacci_node_t *fibonacci_heap_search(c_fibonacci_heap_t *heap,void *key)
{
	if(heap == NULL)
		return NULL;

	return fibonacci_node_search(heap->min_node,key,heap->compare);
}
uint8_t fibonacci_heap_have_key(c_fibonacci_heap_t *heap,void *key)
{
	if(heap == NULL)
		return 0;

	if(NULL == fibonacci_node_search(heap->min_node,key,heap->compare))
		return 0;
	return 1;
}

/*
 *
 *更新度数
 */
static void update_degree(fibonacci_node_t *parent,int degree)
{
	parent->degree -= degree;
	if(parent->parent != NULL)
		update_degree(parent->parent,degree);
}

/*
 *
 *将node从父节点parent的子链表剥离出来
 *并添加到根链表节点中
 */
static void fibonacci_node_cut(c_fibonacci_heap_t *heap,fibonacci_node_t *node,
		fibonacci_node_t *parent)
{
	  //从链表上移除
		fibonacci_node_remove(node);

		if(node == node->right)
			parent->child = NULL; //父节点只有一个孩子
		else
			parent->child = node->right;
		
		node->parent = NULL;
		node->right = node->left = node;//自省形成一个双向链表
		node->marked = 0;
		fibonacci_node_add(node,heap->min_node);
}

static void fibonacci_node_cascading_cut(c_fibonacci_heap_t *heap,fibonacci_node_t *node)
{
	fibonacci_node_t *parent = node->parent;
	if(parent == NULL)
		return;

	if(node->marked == 0)
		node->marked = 1;
	else
	{
		fibonacci_node_cut(heap,node,parent);
		fibonacci_node_cascading_cut(heap,parent);
	}
}
/*
 *
 * 将菲薄那列堆heap中节点的值减少为key
 * 
 */
static void fibonacci_node_decreate(c_fibonacci_heap_t *heap,fibonacci_node_t *node,void *key)
{ 
	fibonacci_node_t *parent = NULL;
	if(heap == NULL || heap->min_node == NULL || node == NULL)
		return;

	if(heap->compare(key,node->key) == 0)
	{
		printf("decreate failed:the new key ie equal the oldkey");
		return;
	}

	node->key = key;
	if(parent != NULL && heap->compare(node->key,parent->key) < 0)
	{
		//将node从父节点上剥离出来，并将node添加到根链表节点
		fibonacci_node_cut(heap,node,parent);
		fibonacci_node_cascading_cut(heap,parent);
	}

	if(heap->compare(node->key,heap->min_node->key) < 0)
		heap->min_node = node->key;

}

static void fibonacci_node_increate(c_fibonacci_heap_t *heap,fibonacci_node_t *node,void *key)
{
	fibonacci_node_t *child = NULL;
	fibonacci_node_t *parent = NULL;
	fibonacci_node_t *right = NULL;
	if(heap == NULL || heap->min_node == NULL || node == NULL)
		return;

	if(heap->compare(key,node->key) == 0)
	{
		printf("decreate failed:the new key ie equal the oldkey");
 		return;
	}
	/*将node节点的每一个child都添加到根链表节点当中去*/
	while(node->child != NULL)
	{
		child = node->right;

		fibonacci_node_remove(child);/*从child从node的孩子链表中移除*/
		if(child->right == right)
			node->child = NULL;
		else
			node->child = child->right;

		fibonacci_node_add(child,heap->min_node);/*将node添加到根链表中去*/
	}

	node->key = node;
	node->degree = 0;

	parent = node->parent;
	if(parent != NULL)
	{
		fibonacci_node_cut(heap,node,parent);
		fibonacci_node_cascading_cut(heap,parent);
	}
}
void fibonacci_node_update(c_fibonacci_heap_t *heap,void *oldkey,void *newkey)
{
	 fibonacci_node_t *node = NULL;
	 if(heap == NULL || heap->min_node == NULL
			 || oldkey == NULL || newkey == NULL)
		 return;

	 if(heap->compare(oldkey,newkey) == 0)
	 {
		 printf("oldkey == newkey,no need to updata");
		 return;
	 }

	 node = fibonacci_node_search(heap->min_node,oldkey,heap->compare);
	 if(node != NULL)
	 {
		 if(heap->compare(oldkey,newkey) < 0)
		 {
			 //increae
			 fibonacci_node_decreate(heap,node,newkey);
		 }else
		 {
			 //decreae
			 fibonacci_node_increate(heap,node,newkey);
		 }
	 }
}
