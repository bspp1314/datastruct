#include<stdio.h>
/* 分解：将n个元素分成各含n/2个元素的子序列
 * 解决：用合并排序法对两个子序列递归地排序
 * 合并：合并两个已排序的子序列以得到排序结果
 * 时间复杂度O(n*log2(n))
 */
static void  
merge_array(int *array,int *result,int start,int end)
{
	if(start >= end)
		return;
 
	int len = end -start;
	int mid = (len >> 1) + start;
	int start1 = start;
	int end1 = mid;
	int start2 = mid+1;
	int end2 = end;


	int i = start;

	merge_array(array,result,start1,end1);
	merge_array(array,result,start2,end2);

	while(start1 <= end1 && start2 <= end2)
	{
		result[i++] = array[start1] > array[start2] 
			? array[start1++] : array[start2++];
	}

	while(start1 <= end1)
		result[i++] = array[start1++];

	while(start2 <= end2)
		result[i++] = array[start2++];

	for(i = start;i <= end;i++)
		array[i] = result[i]; 
}

void merge_sort(int *array,int len)
{
		int result[len];
		merge_array(array,result,0,len);
}


int main(){

	int array[10] = {87,45,34,23,34,5,4,3,2,1};
	merge_sort(array,10);
	for(int i = 0;i < 10 ; i++)
		printf("array[%d] = %d\n",i,array[i]);
	
}
