#include<stdlib.h>
#include"rb_tree.h"
#include<string.h>
#include<malloc.h>
#include<time.h>
int compare(const void  *a,const void  *b){
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
//static void print_pre_order(c_rb_node_t *node)
//{
//	if(node != NULL)
//	{
//			
//		print_pre_order(node->left);
//		printf("-- next is --%d\n",*((int *)node->key));
//		print_pre_order(node->right);
//	}
//}
static void free_key(c_rb_node_t *node)
{
	if(node  != NULL)
	{
		free_key(node->left);
		free(node->key);
		free_key(node->right);
	}

}
int main(){
	c_rb_tree_t *data_sets;

	data_sets = c_rbtree_create(compare);
	if(data_sets == NULL)
		return -1;

	for(int i = 0;i < 10;i++)
	{
		int *p = (int *)malloc(sizeof(int));
		*p = 22 - i ;
		c_rbtree_insert(data_sets,(void*)p,NULL);
	}
	printf("root value is %d\n",*((int *)data_sets->root->key));
//	verif_rb_node(data_sets,data_sets->root);

	free_key(data_sets->root);	

	c_rbtree_destroy(data_sets);
	return 0;
}
