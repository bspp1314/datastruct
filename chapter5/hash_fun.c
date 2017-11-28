#include<stdio.h>
#include"hash_fun.h"
//如果table_size 过大的话，函数不能均匀的散列。
//ex：当表长为10007,且假定key值得长度固定为8，那么hashVal最大值为8 * 127 = 1016。
long hash1(const char *key,int table_size)
{
	int hash_val = 0;
	char *lkey  = key;

	while(*lkey != '\0')
	{
		hash_val += (int)lkey;
		lkey++;
	}

	return (long)(hashVal % table_size);
}

//由于英文文字不是随机,三个字母实际的组合只有2851，会导致不均匀分配。
//即使是随机的，也不过只有表的28%被真正散列到（但是是均匀的）。
long hash2(const char *key,int table_size)
{
	int hash_val = 0;
	char *lkey = key;

	if(lkey[0] == '\0' || lkey[1] == '\0')
		return 0;

	return (lkey[0] + 27 * lkey[1] + 27 * 27 * lkey[2]) % table_size;
}
int main(void)
{
	return 0;
}
