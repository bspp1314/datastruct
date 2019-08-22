#include<stdlib.h>
#include<string.h>
#include<malloc.h>
#include<time.h>
#include<assert.h>

#include"bs_tree.h"

int compare(const void *a,const void *b)
{
    assert(a != NULL);
    assert(b != NULL);
    int v1 = *((int *)a);
    int v2 = *((int *)b);
    return v1 == v2 ? 0: (v1 < v2 ? -1:1);
}
void print_key_func(const void *a){
    if (a == NULL) {
        return;
    }

    int *v = (int *)a;
    printf(" %d ",*v);
}

int main(){
	c_bs_tree_t *data_sets;
    int i = 0;

	//data_sets = c_bs_tree_create((int(*)(const void *,const void *))compare,(void (*)()));
	data_sets = c_bs_tree_create(compare,print_key_func);
	if(data_sets == NULL)
		return -1;
    int arry[11] = {1000,500,2000,250,750,1500,4000,125,375,1750,1875};

	for(i = 0;i < 11;i++)
	{
		int *p = (int *)malloc(sizeof(int));
        *p = arry[i];
		c_bs_tree_insert(data_sets,(void*)p,NULL);
	}
    
    c_bs_tree_preorder(data_sets);
    c_bs_tree_inorder(data_sets);
    c_bs_tree_postorder(data_sets);

    //remove 10000
    int key = 1000;
    int *rkey = NULL;
    c_bs_tree_remove(data_sets,(void *)&key,(void **)&rkey,NULL);
    if (rkey != NULL) {
        free(rkey);
    }
    c_bs_tree_preorder(data_sets);
    c_bs_tree_inorder(data_sets);
    c_bs_tree_postorder(data_sets);
    
    c_bs_tree_destroy(data_sets,1,0);
	
	return 0;

}
