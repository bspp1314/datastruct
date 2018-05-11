#include<stdio.h>
#include<malloc.h>
#include"graph.h"
/*  邻接表无向图
 *   A----------B---------D
 *   | \
 *   |   \
 *   E----F-------C
 *   |
 *   |
 *   G
 *
 *
 * ******************************    
 * 0   A--->1--->4--->5  
 * 1   B--->0--->3
 * 2   C--->5  
 * 3   D--->1   
 * 4   E--->0--->5--->6  
 * 5   F--->0--->2--->4   
 * 6   G--->4
 */

#define MAX_NODE 1000
static void free_graph(talbe_graph_t *table)
{
	if(table == NULL)
		return NULL;
}
int main()
{
	char vexs[] = {'A','B','C','D','E','F','G'};
	char edges[][2] = {
		{'A','C'},
		{'A','D'},
		{'A','F'},
		{'B','C'},
		{'C','D'},
		{'E','G'},
		{'F','G'},
	};
	int v_num = 7;
	int e_num = 7;
	int p1 = 0;
	int p2 = 0;
	char c1;
	char c2;
	talbe_graph_t *graph = NULL; 
	graph = (talbe_graph_t *)malloc(sizeof(talbe_graph_t));
	if(graph == NULL)
	{
		printf("graph malloc failed \n");
		return 0;
	}
	

	/* 初始化"顶点数和边数"*/
	graph->vex_num = v_num;
	graph->edg_num = e_num;

	/*初始化“邻接表的顶点”*/
	for(int  i = 0;i < v_num;i++)
	{
		graph->vexs[i].data = vexs[i];
		graph->vexs[i].root = NULL;
	}
	for(int i = 0;i < v_num;i++)
	{
		c1 = edges[i][0];
		c2 = edges[i][1];

		
	}




	return 0;
}
