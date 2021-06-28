#ifndef GRAPH_H
#define GRAPH_H
struct Vex {
	int num;    //景点编号
	char name[20];   //景点名字
	char infor[1024];  //景点介绍
	/*重载==运算符
	bool operator==(const Vex &t) {
		return num==t.num;
	}
	*/
};
struct Edge {
	int vex1, vex2;
	int weight; //权值
};
struct Graph {
	int map[20][20];   //邻接矩阵
	Vex vexs[20];  //顶点数组
	int VexNum;   //顶点个数
};
struct Path {
	int vexs[20];  //保存一条路径
};
void Init();
int InsertVex(Vex sVex);
int InsertEdge(Edge sEdge);
Vex getVeX(int nVex);
int FindEdge(int nVex, Edge aEdge[]);
int GetVexnum();
void DFS(int s, int nVex, int& nIndex, int& width);
void Floyd();
int FindShortPath(int nVexStart, int nVexEnd, int pre[]);
void DFS(int nVexStart, int nVexEnd, int pre[]);
int FindMinTree();
#endif 
