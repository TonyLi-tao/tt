#include<iostream>
#include<fstream>
#include"Tourism.h"
#include"Graph.h"
using namespace std;
extern Graph graph;
extern Path PathList;
extern bool bVisited[20];
void CreateGraph() {
	ifstream is;
	Init();
	is.open("Vex.txt");
	int n;
	is >> n;
	cout << "顶点数目:" << n << endl;
	cout << "----- 顶点 -----" << endl;
	for (int i = 0; i < n; i++) {
		Vex vex;
		is >> vex.num >> vex.name >> vex.infor;
		cout << vex.num << "-" << vex.name << endl;
		if (InsertVex(vex) == 0) {
			cout << "读取文件信息失败！" << endl;
			break;
		}
	}
	is.close();
	is.open("Edge.txt");
	Edge edges[190];
	int k = 0;
	cout << "----- 边 -----" << endl;
	while (is >> edges[k].vex1 >> edges[k].vex2 >> edges[k].weight) {
		cout << "<v" << edges[k].vex1 << ",v" << edges[k].vex2 << "> " << edges[k].weight << endl;
		if (InsertEdge(edges[k]) == 0) {
			cout << "读取文件信息失败！" << endl;
			break;
		}
		k++;
	}
	for (int i = 0; i < k; i++) {
		int num1 = edges[i].vex1;
		int num2 = edges[i].vex2;
		int weight = edges[i].weight;
		graph.map[num1][num2] = weight;
		graph.map[num2][num1] = weight;
	}
	is.close();
}
void GetSpotInfo() {
	cout << "===== 查询景点信息 =====" << endl;
	for (int i = 0; i < graph.VexNum; i++) {
		cout << graph.vexs[i].num << "-" << graph.vexs[i].name << endl;
	}
	cout << "请输入想要查询的景点编号：";
	int k;
	cin >> k;
	for (int i = 0; i < graph.VexNum; i++) {
		if (graph.vexs[i].num == k) {
			cout << graph.vexs[i].name << endl;
			cout << graph.vexs[i].infor << endl;
			break;
		}
	}
	cout << "----- 周边景区 -----" << endl;
	Edge aEdges[180];
	int m = FindEdge(k, aEdges);
	cout << m << endl;
	for (int i = 0; i < m; i++) {
		cout << graph.vexs[aEdges[i].vex1].name << "->" << graph.vexs[aEdges[i].vex2].name << " " << aEdges[i].weight << "m" << endl;
	}
}
void menu() {
	cout << "===== 景区信息管理系统 =====" << endl;
	cout << "1.创建景区景点图" << endl;
	cout << "2.查询景点信息" << endl;
	cout << "3.旅游景点导航" << endl;
	cout << "4.搜索最短路径" << endl;
	cout << "5.铺设电路规划" << endl;
	cout << "0.退出" << endl;
	cout << "请输入操作编号(0～5):";
	int i;
	cin >> i;
	switch (i) {
	case 0:exit(0); break;
	case 1: {
		CreateGraph();
		cout << "景区景点图创建完成！" << endl;
		menu();
		break;
	}
	case 2: {
		GetSpotInfo();
		menu();
		break;
	}
	case 3: {
		TravelPath();
		menu();
		break;
	}
	case 4: {
		ShortestPath();
		menu();
	}
	case 5: {
		DesignPath();
		menu();
	}
	default: {
		cout << "请重新输入0～5的数字!" << endl;
		menu();
		break;
	}
	}
}
void TravelPath() {
	cout << "===== 旅游景点导航 =====" << endl;
	for (int i = 0; i < graph.VexNum; i++) {
		cout << graph.vexs[i].num << "-" << graph.vexs[i].name << endl;
	}
	cout << "请输入想要查询的景点编号：";
	int k;
	cin >> k;
	bVisited[0] = false;
	for (int i = 1; i < 20; i++) {
		PathList.vexs[i] = -1;
		bVisited[i] = false;
	}
	bVisited[k] = true;
	PathList.vexs[0] = k;
	int depth = 1, width = 1;
	cout << "导游路线为：" << endl;
	//Floyd();
	DFS(k, k, depth, width);
}
void ShortestPath() {
	cout << "===== 搜索最短路径 =====" << endl;
	for (int i = 0; i < graph.VexNum; i++) {
		cout << graph.vexs[i].num << "-" << graph.vexs[i].name << endl;
	}
	int nStart, nEnd;
	cout << "请输入起点的编号：";
	cin >> nStart;
	cout << "请输入终点的编号：";
	cin >> nEnd;
	int pre[20];
	for (int i = 0; i < 20; i++) pre[i] = -1;
	int dis = FindShortPath(nStart, nEnd, pre);
	if (dis != -1) {
		cout << "最短路线为：";
		DFS(nStart, nEnd, pre);
		cout << "最短距离为：" << dis << endl;
	}
	else {
		cout << "从" << graph.vexs[nStart].name << "到" << graph.vexs[nEnd].name << "之间没有通路" << endl;
	}
}
void DesignPath() {
	cout << "===== 铺设电路规划 =====" << endl;
	cout << "在以下两个景点之间铺设电路：" << endl;
	int dis = FindMinTree();
	if (dis == -1) {
		cout << "有景点之间不连通无法铺设电路！" << endl;
	}
	else {
		cout << "铺设电路的总长度为：" << dis << endl;
	}
}
