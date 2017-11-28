/*
 *
 *
 * 一些初级的散列函数
 * * *****************************************************************************/

#include<stdio.h>
#include"hash_fun.h"

/*如果table_size 过大的话，函数不能均匀的散列。
	*ex：当表长为10007,且假定key值得长度固定为8，那么hashVal最大值为8 * 127 = 1016。
	*/
long hash1(const char *key,int table_size)
{
	int hash_val = 0;
	
	if(table_size <= 0)
		return -1;

	while(*key != '\0')
		hash_val += *key++;

	return (long)(hash_val % table_size);
}

/*由于英文文字不是随机,三个字母实际的组合只有2851，会导致不均匀分配。
	*即使是随机的，也不过只有表的28%被真正散列到（但是是均匀的）。
	*/
long hash2(const char *key,int table_size)
{
	int hash_val = 0;

	if(table_size <= 0)
		return -1;

	if(key[0] == '\0' || key[1] == '\0')
		return 0;

	return (key[0] + 27 * key[1] + 27 * 27 * key[2]) % table_size;
}
/**
 * ---KeySize-1
 * \                                 i
 * /            Key[KeySize-i-1] * 32
 * ------i = 0
 */
long hash3(const char *key,int table_size)
{
	long hash_val = 0;

	if(table_size <= 0)
		return -1;

	while(*key != '\0')
		hash_val += (hash_val << 5) + *key++;

	return hash_val % table_size;
}
int main(void)
{
	return 0;
}
