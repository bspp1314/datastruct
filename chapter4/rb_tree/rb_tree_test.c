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

	int p1 = 10;
	int p2 = 5;
	int p3 = 20;
	int p4 = 33;
	int p5 = 44;
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
	printf("root->left value is %d\n",*((int *)data_sets->root->left->key));
	printf("root->left->left value is %d\n",*((int *)data_sets->root->left->left->key));
	printf("root->right value is %d\n",*((int *)data_sets->root->right->key));
	printf("root->right->right->left value is %d\n",*((int *)data_sets->root->right->left->key));
	printf("root->right->right->left->left value is %d\n",*((int *)data_sets->root->right->left->left->key));
	printf("root->right->right->right value is %d\n",*((int *)data_sets->root->right->right->key));
	printf("root->right->right->right->left value is %d\n",*((int *)data_sets->root->right->right->left->key));
	printf("root->right->right->right->right value is %d\n",*((int *)data_sets->root->right->right->right->key));
	
	c_rbtree_remove1(data_sets,(void*)&p4,NULL,NULL);

	printf("root value is %d\n",*((int *)data_sets->root->key));
	printf("root->left value is %d\n",*((int *)data_sets->root->left->key));
	printf("root->left->left value is %d\n",*((int *)data_sets->root->left->left->key));
	printf("root->right value is %d\n",*((int *)data_sets->root->right->key));
	printf("root->right->->left value is %d\n",*((int *)data_sets->root->right->left->key));
	printf("root->right->left->left->value is %d\n",*((int *)data_sets->root->right->left->left->key));
	printf("root->right->right->right value is %d\n",*((int *)data_sets->root->right->right->key));
	printf("root->right->right->right->right value is %d\n",*((int *)data_sets->root->right->right->right->key));
	c_rbtree_destroy(data_sets);
	return 0;

}
