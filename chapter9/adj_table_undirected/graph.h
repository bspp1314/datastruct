#ifndef GRAPH_H
#define GRAPH_H
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
typedef struct e_node
{
	int ivex;//边所指向的顶点位置
	struct e_node *next;//指向下一条弧的指针
}e_node_t;

typedef struct v_node
{
	char data;//顶点信息
	e_node_t *root;//指向第一条依附该顶点的弧
}v_node_t;

typedef struct talbe_graph{
	int vex_num;//顶点数
	int edg_num;//边数
	v_node_t vexs[MAX_NODE];
}talbe_graph_t;



#endif
