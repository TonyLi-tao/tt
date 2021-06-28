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
	cout << "������Ŀ:" << n << endl;
	cout << "----- ���� -----" << endl;
	for (int i = 0; i < n; i++) {
		Vex vex;
		is >> vex.num >> vex.name >> vex.infor;
		cout << vex.num << "-" << vex.name << endl;
		if (InsertVex(vex) == 0) {
			cout << "��ȡ�ļ���Ϣʧ�ܣ�" << endl;
			break;
		}
	}
	is.close();
	is.open("Edge.txt");
	Edge edges[190];
	int k = 0;
	cout << "----- �� -----" << endl;
	while (is >> edges[k].vex1 >> edges[k].vex2 >> edges[k].weight) {
		cout << "<v" << edges[k].vex1 << ",v" << edges[k].vex2 << "> " << edges[k].weight << endl;
		if (InsertEdge(edges[k]) == 0) {
			cout << "��ȡ�ļ���Ϣʧ�ܣ�" << endl;
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
	cout << "===== ��ѯ������Ϣ =====" << endl;
	for (int i = 0; i < graph.VexNum; i++) {
		cout << graph.vexs[i].num << "-" << graph.vexs[i].name << endl;
	}
	cout << "��������Ҫ��ѯ�ľ����ţ�";
	int k;
	cin >> k;
	for (int i = 0; i < graph.VexNum; i++) {
		if (graph.vexs[i].num == k) {
			cout << graph.vexs[i].name << endl;
			cout << graph.vexs[i].infor << endl;
			break;
		}
	}
	cout << "----- �ܱ߾��� -----" << endl;
	Edge aEdges[180];
	int m = FindEdge(k, aEdges);
	cout << m << endl;
	for (int i = 0; i < m; i++) {
		cout << graph.vexs[aEdges[i].vex1].name << "->" << graph.vexs[aEdges[i].vex2].name << " " << aEdges[i].weight << "m" << endl;
	}
}
void menu() {
	cout << "===== ������Ϣ����ϵͳ =====" << endl;
	cout << "1.������������ͼ" << endl;
	cout << "2.��ѯ������Ϣ" << endl;
	cout << "3.���ξ��㵼��" << endl;
	cout << "4.�������·��" << endl;
	cout << "5.�����·�滮" << endl;
	cout << "0.�˳�" << endl;
	cout << "������������(0��5):";
	int i;
	cin >> i;
	switch (i) {
	case 0:exit(0); break;
	case 1: {
		CreateGraph();
		cout << "��������ͼ������ɣ�" << endl;
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
		cout << "����������0��5������!" << endl;
		menu();
		break;
	}
	}
}
void TravelPath() {
	cout << "===== ���ξ��㵼�� =====" << endl;
	for (int i = 0; i < graph.VexNum; i++) {
		cout << graph.vexs[i].num << "-" << graph.vexs[i].name << endl;
	}
	cout << "��������Ҫ��ѯ�ľ����ţ�";
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
	cout << "����·��Ϊ��" << endl;
	//Floyd();
	DFS(k, k, depth, width);
}
void ShortestPath() {
	cout << "===== �������·�� =====" << endl;
	for (int i = 0; i < graph.VexNum; i++) {
		cout << graph.vexs[i].num << "-" << graph.vexs[i].name << endl;
	}
	int nStart, nEnd;
	cout << "���������ı�ţ�";
	cin >> nStart;
	cout << "�������յ�ı�ţ�";
	cin >> nEnd;
	int pre[20];
	for (int i = 0; i < 20; i++) pre[i] = -1;
	int dis = FindShortPath(nStart, nEnd, pre);
	if (dis != -1) {
		cout << "���·��Ϊ��";
		DFS(nStart, nEnd, pre);
		cout << "��̾���Ϊ��" << dis << endl;
	}
	else {
		cout << "��" << graph.vexs[nStart].name << "��" << graph.vexs[nEnd].name << "֮��û��ͨ·" << endl;
	}
}
void DesignPath() {
	cout << "===== �����·�滮 =====" << endl;
	cout << "��������������֮�������·��" << endl;
	int dis = FindMinTree();
	if (dis == -1) {
		cout << "�о���֮�䲻��ͨ�޷������·��" << endl;
	}
	else {
		cout << "�����·���ܳ���Ϊ��" << dis << endl;
	}
}
