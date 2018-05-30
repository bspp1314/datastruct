#include<stdio.h>

#define max  10001
int set[max];
int rank[max];

void make_set(int i)
{
	// 初始化的时候，一个集合的parent都是这个集合自己的标号。
	// 没有跟它同类的集合，那么这个集合的源头只能是自己了。
	set[i] = i;
	rank[i] = 0;
}


int find_set(int x)
{
	if(set[x] != x)
		set[x] = find_set(set[x]);
	return set[x];
}

void union_set(int i,int j)
{
	i = find_set(i);
	j = find_set(j);

	if(rank[i] > rank[j])
		set[j] = i;//j parent is i
	else{
		if(rank[i] == rank[j]) 
			rank[j]++;
		set[i] = j;
	}

}

int main()
{
	for(int i = 0;i < 1000;i++)
		make_set(i);

	union_set(1,2);
	union_set(2,3);

	union_set(22,1);
	union_set(11,8);
	union_set(33,23);
	union_set(55,78);
	union_set(4,5);
	int count = 0;
	for(int i = 0; i < 1000 ;i++)
	{
		if(i == find_set(i) && rank[i] != 0)
		{
			printf("i value is %d\n",i);
			count++;
		}
	}

	printf("count is %d\n",count);

}
