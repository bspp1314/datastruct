#include<stdio.h>

static void swap(int *a,int *b)
{
	int index = *a;
	*a = *b;
	*b = index;
}
static int median3(int *array,int left,int right)
{
	int center = (left + right) >> 1;
	
	if(array[left] > array[center])
		swap(&array[left],&array[center]);

	if(array[left] > array[right])
		swap(&array[left],&array[right]);

	if(array[center] > array[right])
		swap(&array[center],&array[right]);

	/* array[left] < array[center] < array[right]*/
	return array[center];
}

static void quick_array(int *array,int left,int right)
{
	int i;
	int j;
	int privot;
	int center;

	if((right-left) >= 2)
	{
		privot = median3(array,left,right);
	  center = (left + right) >> 1;
		swap(&array[center],&array[right-1]);

		i = left;
		j = right - 1;
		for(;;)
		{
			while(array[++i] < privot);
			while(array[--j] > privot);
			if(i < j)
				swap(&array[i],&array[j]);
			else
				break;
		}
		swap(&array[i],&array[right-1]);
		quick_array(array,left,i-1);
		quick_array(array,i+1,right);
	}else{
		if((right-left) == 0)
			return;
		else if((right-left) == 1)
		{
			if(array[left] > array[right])
				swap(&array[left],&array[right]);
		}
	}
}
void quick_sort(int *array,int len)
{
	quick_array(array,0,len-1);
}

int main(){
	int array[12] = {87,45,34,23,35,5,4,3,2,1,100,101};
	quick_sort(array,10);
	for(int i = 0;i < 12 ; i++)
		printf("array[%d] = %d\n",i,array[i]);
	
	return 0;
}
