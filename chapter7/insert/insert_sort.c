#include<stdio.h>


/*
 * 从第一个元素开始，该元素可以认为已经被排序
 * 取出下一个元素，在已经排序的元素序列中从后向前扫描
 * 如果该元素（已排序）大于新元素，将该元素移到下一位置
 * 重复步骤3，直到找到已排序的元素小于或者等于新元素的位置
 * 将新元素插入到该位置后
 * 最优的时间O(n)
 * 最坏的时间O(n2)
 * 平均的时间O(n2)
 */
void insert_sort(int *array,int len)
{
	int i = 0 ;
	int j = 0 ;
	int temp = 0;
	for(i = 1; i < len;i++)
	{
		temp = array[i];
		for(j = i;j > 0 && array[j-1] > temp;j--)
			array[j] = array[j-1]; 
		array[j] = temp;
	}
}

int main(){

	int array[10] = {87,45,34,23,34,5,4,3,2,1};
	insert_sort(array,10);
	for(int i = 0;i < 10 ; i++)
		printf("array[%d] = %d\n",i,array[i]);
	
}
