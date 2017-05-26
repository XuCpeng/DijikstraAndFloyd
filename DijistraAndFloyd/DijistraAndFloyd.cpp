// DijistraAndFloyd.cpp : 定义控制台应用程序的入口点。
//Dijikstra+Floyd

#include "stdafx.h"
#include <iostream>
#include "string"
using namespace std;
const int MaxSize = 100;
const int Maxcost = 99999;
static int visited[MaxSize] = { 0 };
//辅助数组
struct ShortEdge
{
	char adjvex;
	int lowcost;
};

template <class DataType>
class MGraph
{
public:
	MGraph(DataType a[], int n, int e);
	~MGraph() {}
	friend void Dijikstra(MGraph<char> G, int v);
	friend void Floyd(MGraph<char> G);
private:
	DataType vertex[MaxSize];
	int arc[MaxSize][MaxSize];
	int vertexNum, arcNum;
};
//构造函数
template<class DataType>
MGraph<DataType>::MGraph(DataType a[], int n, int e)
{
	vertexNum = n;
	arcNum = e;
	for (int i = 0; i<n; i++)
	{
		vertex[i] = a[i];
		for (int j = 0; j<n; j++)
		{
			if (i == j)
				arc[i][j] = 0;
			else
				arc[i][j] = Maxcost;
		}
	}
	cout << "请输入边依附的顶点编号及权值（Bianhaojiquanzhi:）：" << endl;
	for (int k = 0; k<e; k++)
	{
		int i, j, p;
		cin >> i >> j >> p;
		arc[i][j] = p;
	}
}

//最短路径Dijistra算法
void Dijikstra(MGraph<char> G, int v)
{
	int dist[MaxSize];
	string path[MaxSize];

	int i, k;
	for (i = 0; i < G.vertexNum; i++)
	{
		dist[i] = G.arc[v][i];
		if (dist[i] != Maxcost)
		{
			path[i] = "" + G.vertex[v] + G.vertex[i];
			cout << path[i];
		}
		else
		{
			path[i] = "";
		}
	}
	int S[MaxSize];
	S[0] = v;
	dist[v] = 0;
	int num = 1;
	while (num < G.vertexNum)
	{
		for (k = 0, i = 0; i < G.vertexNum; i++)
		{
			if ((dist[i] != 0) && (dist[i] < dist[k]))
			{
				k = i;
			}
			cout << dist[k] << path[k];
			S[num++] = k;
			for (int i = 0; i < G.vertexNum; i++)
			{
				if (dist[i] > dist[k] + G.arc[k][i])
				{
					dist[i] = dist[k] + G.arc[k][i];
					path[i] = path[i] + G.vertex[i];
				}
				dist[k] = 0;
			}
		}
	}
}

//最短路径Floyd算法
void Floyd(MGraph<char> G)
{
	int dist[MaxSize][MaxSize];
	string path[MaxSize][MaxSize];
	
	for (int i = 0; i < G.vertexNum; i++)
	{
		for (int j = 0; j < G.vertexNum; j++)
		{
			dist[i][j] = G.arc[i][j];
			if (dist[i][j] != Maxcost)
				path[i][j] = ""+G.vertex[i] + G.vertex[j];
			else
				path[i][j] = "";
		}
	}
	for (int k = 0; k < G.vertexNum; k++)
	{
		for (int m = 0; m < G.vertexNum; m++)
		{
			for (int n = 0; n < G.vertexNum; n++)
			{
				if (dist[m][k] + dist[k][n] < dist[m][n])
				{
					dist[m][n] = dist[m][k] + dist[k][n];
					path[m][n] = path[m][k] + path[k][n];
				}
			}
		}
	}
}

int main()
{
	int n, e;
	char a[MaxSize];
	cout << "请输入顶点个数（Dingdiangeshu:）：";
	cin >> n;
	cout << "\n请输入边的条数（Bian:）：";
	cin >> e;
	cout << "\n请输入顶点，空格隔开（Dingdian:）：";
	for (int i = 0; i < n; i++)
	{
		cin >> a[i];
	}

	MGraph<char> m1(a, n, e);
	cout << "最短路径Dijikstra算法：";
	Dijikstra(m1, 0);
	cout << "\n最短路径Floyd算法：";
	Floyd(m1);
	return 0;
}