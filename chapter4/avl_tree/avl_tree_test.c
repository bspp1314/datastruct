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
	int i = 0;
	struct timeval  start,end;
	long iTimeInterval;

	data_sets = c_avl_create((int(*)(const void *,const void *))compare);
	if(data_sets == NULL)
		return -1;

	for(i = 0;i < 10000;i++)
	{
		int *p = (int *)malloc(sizeof(int));
		*p = i;
		printf("%d\n",*p);
		c_avl_insert(data_sets,(void*)p,NULL);
	}
	printf("root value is %d\n",*((int *)data_sets->root->key));
	printf("root height is %d\n",calc_height(data_sets->root));
	

	int *p;
	while(c_avl_pick(data_sets,(void **)&p,NULL) == 0)
	{
		free(p);
	}
	c_avl_destroy(data_sets);
	return 0;

}
