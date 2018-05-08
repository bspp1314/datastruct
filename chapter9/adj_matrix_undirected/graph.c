#include<stdio.h>
#include<string.h>
#include<malloc.h>
#include"graph.h"

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

	graph_t *graph = NULL;
	graph = (graph_t *)malloc(sizeof(graph_t));
	if(graph == NULL)
	{
		printf("malloc graph failed\n");
		return -1;
	}
  
	memset(graph,0,sizeof(graph_t));
	graph->vex_num = v_num;
	graph->edg_num = e_num;
	//初始化顶点
	for(int i = 0; i < graph->vex_num; i++)
		graph->vexs[i] = vexs[i];

	//初始化边
	for(int i = 0;i < graph->edg_num;i++)
	{
		p1 = edges[i][0] - 'A';
		p2 = edges[i][1] - 'A';

		graph->matrix[p1][p2] = 1;
		graph->matrix[p2][p1] = 1;
	}

	for(int i = 0; i < graph->vex_num;i++){
		for(int j = 0;j < graph->vex_num;j++)
			printf("%d",graph->matrix[i][j]);
		printf("\n");
	}		

	free(graph);
	return 0;

}


