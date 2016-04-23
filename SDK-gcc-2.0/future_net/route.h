#ifndef __ROUTE_H__
#define __ROUTE_H__

#define HANDLE_CYCLE	//是否处理环？当然
//#define PRINT_PAHT	//是否能够打印路径

#include <memory.h>
#include <limits.h>
#include <time.h>
#include <assert.h>

#include <iostream>
#include <queue>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <set>
#include <stack>
#include <bitset>
using namespace std;

void search_route(char *graph[5000], int edge_num, char *condition);

const int maxn = 2000;	//最大节点数目

//边
class Edge {
public:
	int dist;
	unsigned short num, from, to;
	Edge();
	Edge(unsigned short index, unsigned short u, unsigned short v, int d) : num(index), from(u), to(v), dist(d) {}
};

//路径
class Path {
public:
	int cost;
	unsigned short start, target;
	vector<unsigned short> edges;
	bitset<maxn> visited;
	unsigned short i, j, k;
	unsigned short spNum;

	Path &operator=(const Path &rhs);
	Path operator+(const Path &rhs);
	void handleCycle(Path &rhs, class Dijkstra &work, bool judgeCycle);
	void printPath(class Dijkstra &work);
};

//Dijkstra
class HeapNode {
public:
	int d, u;	//d:节点u的最短路径估计 u:节点号
	HeapNode(int a, int b) : d(a), u(b) {}
	bool operator < (const HeapNode& rhs) const {
		return d > rhs.d;
	}
};

class Dijkstra {
public:
	int n, m;			//n:节点数目 m:边的数目
	bitset<maxn> done;	//节点是否已永久标号

	int p[maxn];		//最短路中的上一条弧
	int d[maxn];		//s到各个点的距离
	vector<int> includingSet;
	bitset<maxn> isIncludingSet;
	int start, target;
	
	vector<int> G[maxn];//图G:下标表示节点，vector<int>中存的是，edges中的下标集合。-1表示此边已经被排除·

	void init(char *topo[5000], int edge_num, char *demand);
	void AddEdge(int index, int from, int to, int dist);
	void dijkstra(int s, const bitset<maxn> rmNodes);
	void BuildPath(int vi, int vl, Path& path);
};
#endif
