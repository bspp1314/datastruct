#include<stdio.h>

static void swap(int *a,int *b)
{
	int index = *a;
	*a = *b;
	*b = index;
}
/* 从下而上构建堆,默认其左右子树是已经构建完的二叉堆 */
void max_heapify(int array[], int start, int end) 
{
	int parent = start;
	int child = parent * 2 + 1;

	while(child <= end)
	{
		if(child + 1 <= end && array[child] < array[child+1])
			child++;
		if(array[parent] > array[child])
			return;
		else{
			swap(&array[parent],&array[child]);
			parent = child;
			child = (parent << 1) + 1;
		}
	}
}
void heap_sort(int array[],int len)
{
	
	/* 初始化，i从最后一个父节点开始调整 */
	for(int i = len/2-1;i >= 0; i--)
		max_heapify(array,i,len-1);

	for(int i = len -1;i >= 0;i--)
	{
	  //将第一个元素和已经排好元素前一位做交换，再重新排序
		swap(&array[0],&array[i]);
		max_heapify(array, 0, i - 1);
	}
}





int main()
{
	int array[] = {3,1,2,5,6,7,8};

	for(int i = 0;i < 7;i++)
		printf("array[%d] = %d ",i,array[i]);
	printf("\n");

	heap_sort(array,6);

	for(int i = 0;i < 7;i++)
		printf("array[%d] = %d ",i,array[i]);
	printf("\n");
}

