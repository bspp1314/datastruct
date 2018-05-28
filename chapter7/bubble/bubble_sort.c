#include<stdio.h>


/*
 * 比较相邻的元素。如果第一个比第二个大，就交换他们两个。  
 * 对每一对相邻元素作同样的工作，从开始第一对到结尾的最后一对。这步做完后，最后的元素会是最大的数
 * 针对所有的元素重复以上的步骤，除了最后一个。
 * 最优的时间O(n)
 * 最坏的时间O(n2)
 * 平均的时间O(n2)
 */
void insert_sort(int *array,int len)
{
	int i = 0 ;
	int j = 0 ;
	int temp = 0;
	for(i = len; i > 0;i--)
	{
		for(j = 1;j < i;j++)
		{
			if(array[j-1] > array[j])
			{
				temp = array[j];
				array[j] = array[j-1];
				array[j-1] = temp;
			}
		}
	}
}

int main(){

	int array[10] = {87,45,34,23,34,5,4,3,2,1};
	insert_sort(array,10);
	for(int i = 0;i < 10 ; i++)
		printf("array[%d] = %d\n",i,array[i]);
	
}
