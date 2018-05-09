#include<stdlib.h>
#include"skew_heap.h"
#include<malloc.h>

int compare(const void *a,const void *b){
	if( *((int*)a) == *((int *)b)  )
	{
		return 0;

	}else if(*((int*)a) < *((int *)b))
	{
		return -1;

	}else{
		return 1;
	}
	return 1;

}


static void print_pre_order(node_t *node)
{
	if(node != NULL)
	{
			
		print_pre_order(node->left);
		printf("-- next is --%d\n",*((int *)node->key));
		print_pre_order(node->right);
	}
}
int main(){

//	c_left_heap_t *left_heap = c_left_heap_create(compare);
//	if(left_heap == NULL)
//		return -1;
//
//	int p0 = 1;;
//	int p1 = 2;
//	int p2 = 3;
//	int p3 = 4;
//	int p4 = 5;
//	int p5 = 6;
//	int p6 = 7;
//	int p7 = 8;
//	int p8 = 9;
//	int p9 = 10;
//
//	c_left_heap_insert(left_heap,&p0,NULL);
//	c_left_heap_insert(left_heap,&p1,NULL);
//	c_left_heap_insert(left_heap,&p2,NULL);
//	c_left_heap_insert(left_heap,&p3,NULL);
//	c_left_heap_insert(left_heap,&p4,NULL);
//	c_left_heap_insert(left_heap,&p5,NULL);
//	c_left_heap_insert(left_heap,&p6,NULL);
//	c_left_heap_insert(left_heap,&p7,NULL);
//	c_left_heap_insert(left_heap,&p8,NULL);
//	c_left_heap_insert(left_heap,&p9,NULL);
//
//	printf("%d\n",*((int *)left_heap->root->key));
//	printf("%d\n",*((int *)left_heap->root->left->key));
//	printf("%d\n",*((int *)left_heap->root->right->key));
//
//	
//	//node_t *n = c_left_heap_next(left_heap->root);
//	//printf("root next is %d\n",*((int *)n->key));
//
//	printf("=================================================\n");
//  print_pre_order(left_heap->root);
//	c_left_heap_destroy(left_heap);
	return 0;

}
