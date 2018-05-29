#include<stdio.h>
/*
 *
 *希尔排序通过将比较的全部元素分为几个区域来提升插入排序的性能。
 *这样可以让一个元素可以一次性地朝最终位置前进一大步。
 *然后算法再取越来越小的步长进行排序，
 *算法的最后一步就是普通的插入排序，但是到了这步，需排序的数据几乎是已排好的了
 */

/* 步长为（n/2) 平方*/
void shell_sort(int *array,int len)
{
	int i;
	int j;
	int temp;
	int grap;

	for(grap = len >> 1; grap > 0; grap = grap >> 1)
	{
		for(i = grap ;i < len; i++)
		{
			temp = array[grap];
			for(j = i-grap; j >= 0 && array[j] > temp; j-=grap)
				array[j+grap] = array[j];
			array[j+grap] = temp;
		}
	}
}

int main()
{
	int array[10] = {87,45,34,23,34,5,4,3,2,1};
	shell_sort(array,10);
	for(int i = 0;i < 10 ; i++)
		printf("array[%d] = %d\n",i,array[i]);
	return 0;
}
