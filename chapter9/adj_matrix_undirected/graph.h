#ifndef GRAPH_H
#define GRAPH

#define MAX 2000
/*   A----------B---------D
 *   | \
 *   |   \
 *   E----F-------C
 *   |
 *   |
 *   G
 *
 *
 *      A  B  C  D  E  F  G
 * ******************************    
 *  A   0  1  0  0  1  1  0
 *  B   1  0  0  1  0  0  0
 *  C   0  0  0  0  0  1  0 
 *  D   0  1  0  0  0  0  0
 *  E   1  0  0  0  0  1  1
 *  F   1  0  1  0  1  0  0
 *  G
 */
typedef struct graph
{
	char vexs[MAX];//顶点集
	int vex_num;//顶点数
	int edg_num;//边数
	int matrix[MAX][MAX];//邻接矩阵
}graph_t;

#endif
