#ifndef GRAPH_H
#define GRAPH_H
struct Vex {
	int num;    //������
	char name[20];   //��������
	char infor[1024];  //�������
	/*����==�����
	bool operator==(const Vex &t) {
		return num==t.num;
	}
	*/
};
struct Edge {
	int vex1, vex2;
	int weight; //Ȩֵ
};
struct Graph {
	int map[20][20];   //�ڽӾ���
	Vex vexs[20];  //��������
	int VexNum;   //�������
};
struct Path {
	int vexs[20];  //����һ��·��
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
