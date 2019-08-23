#include<stdlib.h>
#include"avl_tree.h"
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
	c_avl_tree_t *data_sets;
	c_avl_node_t *node;
	int i = 0;
    time_t start;
    time_t end;

    time(&start);
	data_sets = c_avl_create((int(*)(const void *,const void *))compare);
	if(data_sets == NULL)
		return -1;

	for(i = 0;i < 10;i++)
	{
		int *p = (int *)malloc(sizeof(int));
		*p = i+1;
		c_avl_insert(data_sets,(void*)p,NULL);
	}
	printf("root value is %d\n",*((int *)data_sets->root->key));
	printf("root value is %d\n",*((int *)data_sets->root->left->key));
	printf("root value is %d\n",*((int *)data_sets->root->right->key));
	
	c_avl_destroy(data_sets,1,0);
    time(&end);
    printf("need time :%ld",end-start);
	return 0;

}
