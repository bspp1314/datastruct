#include<stdlib.h>
#include"rb_tree.h"
#include<string.h>
#include<malloc.h>
#include<time.h>
int compare(int *a,int *b){
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
int main(){
	c_rb_tree_t *data_sets;
	int i = 0;
	struct timeval  start,end;
	long iTimeInterval;

	data_sets = c_rbtree_create((int(*)(const void *,const void *))compare);
	if(data_sets == NULL)
		return -1;

	int p1 = 4;
	int p2 = 5;
	int p3 = 8;
	int p4 = 10;
	int p5 = 20;
	int p6 = 19;
	int p7 = 78;
	int p8 = 34;
	int p9 = -2;
	printf("======================================\n");
	c_rbtree_insert(data_sets,(void*)&p1,NULL);
	c_rbtree_insert(data_sets,(void*)&p2,NULL);
	c_rbtree_insert(data_sets,(void*)&p3,NULL);
	c_rbtree_insert(data_sets,(void*)&p4,NULL);
	c_rbtree_insert(data_sets,(void*)&p5,NULL);
	c_rbtree_insert(data_sets,(void*)&p6,NULL);
	c_rbtree_insert(data_sets,(void*)&p7,NULL);
	c_rbtree_insert(data_sets,(void*)&p8,NULL);
	c_rbtree_insert(data_sets,(void*)&p9,NULL);
	printf("root value is %d\n",*((int *)data_sets->root->key));
	
	c_rbtree_destroy(data_sets);
	return 0;

}
