#include "Graph.h"
#include "stdlib.h"
#include "stack"
#include<iostream>
Graph graph;
Path PathList;
bool bVisited[20];
using namespace std;
void Init() {
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 20; j++) {
			if (i == j) graph.map[i][j] = 0;
			else graph.map[i][j] = 0xffff;
		}
	}
	graph.VexNum = 0;
}
int InsertVex(Vex sVex) {
	if (graph.VexNum >= 20) return 0;
	graph.vexs[graph.VexNum] = sVex;
	graph.VexNum++;
	return 1;
}
int InsertEdge(Edge sEdge) {
	int num1 = sEdge.vex1;
	int num2 = sEdge.vex2;
	if (num1 != num2) {
		graph.map[num1][num2] = sEdge.weight;
		graph.map[num2][num1] = sEdge.weight;
		return 1;
	}
	else return 0;
}
Vex getVeX(int nVex) {
	return graph.vexs[nVex];
}
int FindEdge(int nVex, Edge aEdge[]) {
	int k = 0;
	for (int i = 0; i < graph.VexNum; i++) {
		if (graph.map[i][nVex] > 0 && graph.map[i][nVex] < 0xffff) {
			aEdge[k].vex1 = nVex;
			aEdge[k].vex2 = i;
			aEdge[k].weight = graph.map[i][nVex];
			k++;
		}
	}
	return k;
}
int GetVexnum() {
	return graph.VexNum;
}
void DFS(int s, int nVex, int& nIndex, int& width) {
	if (width == graph.VexNum) {
		cout << "Â·Ïß" << nIndex++ << ":";
		for (int j = 0; j < graph.VexNum; j++) {
			if (j == graph.VexNum - 1) {
				cout << graph.vexs[PathList.vexs[j]].name << endl;
			}
			else {
				cout << " " << graph.vexs[PathList.vexs[j]].name << " -> ";
			}
		}
	}
	else {
		for (int i = 0; i < graph.VexNum; i++) {
			if (graph.map[nVex][i] > 0 && graph.map[nVex][i] != 0xffff && bVisited[i] == false) {
				bVisited[i] = true;
				PathList.vexs[width++] = i;
				DFS(s, i, nIndex, width);
				bVisited[i] = false;
				width--;
			}
		}
	}
}
void Floyd() {
	for (int k = 0; k < graph.VexNum; k++) {
		for (int i = 0; i < graph.VexNum; i++) {
			for (int j = 0; j < graph.VexNum; j++) {
				if (graph.map[i][k] + graph.map[k][j] < graph.map[i][j]) {
					graph.map[i][j] = graph.map[i][k] + graph.map[k][j];
				}
			}
		}
	}
}
int FindShortPath(int nVexStart, int nVexEnd, int pre[]) {
	int d[20];
	bool visited[20] = { false };
	fill(d, d + 20, 0xffff);
	d[nVexStart] = 0;
	for (int i = 0; i < graph.VexNum; i++) {
		int u = -1, minx = 0xffff;
		for (int j = 0; j < graph.VexNum; j++) {
			if (visited[j] == false && d[j] < minx) {
				u = j;
				minx = d[j];
			}
		}
		if (u == -1) return -1;
		visited[u] = true;
		for (int v = 0; v < graph.VexNum; v++) {
			if (visited[v] == false && graph.map[u][v] != 0xffff && d[u] + graph.map[u][v] < d[v]) {
				d[v] = d[u] + graph.map[u][v];
				pre[v] = u;
			}
		}
	}
	return d[nVexEnd];
}
void DFS(int nVexStart, int nVexEnd, int pre[]) {
	int nextd[20];
	for (int i = 0; i < 20; i++) {
		nextd[i] = -1;
	}
	int t;
	int end = nVexEnd;
	while (nVexStart != end) {
		t = pre[end];
		nextd[t] = end;
		end = t;
	}
	while (nVexStart != nVexEnd) {
		cout << graph.vexs[nVexStart].name << "->";
		nVexStart = nextd[nVexStart];
	}
	cout << graph.vexs[nVexEnd].name << endl;
}
int FindMinTree() {
	int d[20] = { 0 };
	//bool flag = false;
	d[0] = 0;
	int ans = 0;
	int path[20];
	memset(path, 0, sizeof(path));
	for (int i = 0; i < graph.VexNum; i++) {
		d[i] = graph.map[0][i];
		path[i] = 0;
	}
	path[0] = -1;
	for (int i = 0; i < graph.VexNum; i++) {
		int u = -1, minx = 0xffff;
		for (int j = 0; j < graph.VexNum; j++) {
			if (path[j] != -1 && d[j] < minx) {
				u = j;
				minx = d[j];
			}
		}
		if (u != -1) {
			if (minx == 0) {
				path[u] = -1;
			}
			else {
				cout << graph.vexs[path[u]].name << " - " << graph.vexs[u].name << "  " << minx << "m" << endl;
				ans += minx;
				//flag = 1;
				path[u] = -1;
			}
		}
		for (int v = 0; v < graph.VexNum; v++) {
			if (path[v] != -1 && graph.map[u][v] != 0xffff && graph.map[u][v] < d[v]) {
				d[v] = graph.map[u][v];
				path[v] = u;
			}
		}
	}
	return ans;
}
