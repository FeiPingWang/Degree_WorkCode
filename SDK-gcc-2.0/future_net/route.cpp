#include "route.h"
#include "lib_record.h"
#include <stdio.h>
using namespace std;

vector<Edge> allEdges;		//边的集合

Path &Path::operator=(const Path &rhs)
{
	cost = rhs.cost;
	visited = rhs.visited;
	start = rhs.start;
	target = rhs.target;
	edges = rhs.edges;
	spNum = rhs.spNum;
	i = rhs.i;
	j = rhs.j;
	k = rhs.k;
	return *this;
}

Path Path::operator+(const Path &rhs)
{
	Path sum = *this;
	sum.cost = this->cost + rhs.cost;
	sum.visited = rhs.visited;
	sum.spNum += rhs.spNum - 1;

	for(unsigned int i = 0; i < sum.edges.size(); i++) {
		if(i == 0) sum.visited.set(allEdges[sum.edges[i]].to);
		sum.visited.set(allEdges[sum.edges[i]].from);
	}
	return sum;
}

void Path::handleCycle(Path &rhs, Dijkstra &work, bool judgeCycle)
{
	bool hasCycle = false;	
	if(this->target == rhs.start) {	
		for(unsigned int i = 0; i < this->edges.size(); i++) {
			if(rhs.visited[allEdges[this->edges[i]].from] == true) {
				hasCycle = true;
				break;
			}
		}
	}
	else if(this->start == rhs.target) {
		for(unsigned int i = 0; i < this->edges.size(); i++) {
			if(rhs.visited[allEdges[this->edges[i]].to] == true) {
				hasCycle = true;
				break;
			}
		}
	}
	if(hasCycle == false) return;

	bitset<maxn> rmNodes;
	rmNodes = rhs.visited;

	if(this->target == rhs.start) {
		assert(rmNodes[this->target] == true);
		rmNodes[this->target] = false;
	}
	else if(this->start == rhs.target) {
		assert(rmNodes[this->start] == true);
		rmNodes[this->start] = false;
	}
	if(this->start != work.start) rmNodes[work.start] = true;
	if(this->target != work.target) rmNodes[work.target] = true;
	work.dijkstra(this->start, rmNodes);
	work.BuildPath(this->start, this->target, *this);
}

void Dijkstra::init(char *topo[5000], int edge_num, char *demand) {	//用节点数目初始化
	m = edge_num;
	n = 0;

	for (int i = 0; i < maxn; i++) G[i].clear();
	allEdges.clear();

	int index, from, to, dist;
	char tmp;
	for(int i = 0; i < edge_num; i++){
		stringstream ss;
		ss << topo[i];
	    	ss >> index >> tmp >> from >> tmp >> to >> tmp >> dist;
		this->AddEdge(index, from, to, dist);	
	}

	stringstream ss;
	ss << demand;
	ss >> this->start >> tmp >> this->target >> tmp;
	do{
		ss >> from;
		includingSet.push_back(from);
		isIncludingSet.set(from);
	}while(ss >> tmp);
}

void Dijkstra::AddEdge(int index, int from, int to, int dist) {	//添加一条边
	//只添加一个删除旧边的操作
	if(G[from].size() != 0) { //此起点已经有边存在
		for(int i = 0; i < (int)G[from].size(); i++) {
			if(allEdges[G[from][i]].to == to && allEdges[G[from][i]].dist > dist) {
				G[from][i] = -1; //删除旧边
			}
		}
	}

	while(1) {
		if((int)allEdges.size() >= index) {
			allEdges.push_back(Edge(index, from, to, dist));	//此处假设边的读入顺序和index相同。否则需要事先设计allEdges的大小。
			break;
		}
		else allEdges.push_back(Edge(-1, -1, -1, -1));
	}
	int tmp = max(from, to);
	this->n = max(this->n, tmp + 1);
	G[from].push_back(index);
}

void Dijkstra::dijkstra(int s, const bitset<maxn> rmNodes) {	//计算起点到各个点的最短路径
	
	for (int i = 0; i < n; i++) d[i] = INT_MAX;	//初始化d数组
	d[s] = 0;

	done.reset();	//初始化done数组
	done = rmNodes;
		
	memset(p, -1, sizeof(p));	//-1表示没有这条边
	priority_queue<HeapNode> Q;
	Q.push(HeapNode(0, s));	//把起点加入队列

	while (!Q.empty()) {
		HeapNode x = Q.top(); Q.pop();
		int u = x.u;
		if (done[u]) continue;
		done[u] = true;
		for (unsigned int i = 0; i < G[u].size() && G[u][i] != -1; i++) {	//	遍历节点u的所有边, 删除的边不遍历
			Edge& e = allEdges[G[u][i]];
			if (d[e.to] > d[u] + e.dist) {
				d[e.to] = d[u] + e.dist;
				p[e.to] = G[u][i];
				Q.push(HeapNode(d[e.to], e.to));
			}
		}
	}
}

void Dijkstra::BuildPath(int vi, int vl, Path& path)
{
	path.cost = this->d[vl];
	path.start = vi;
	path.target = vl;
	path.edges.clear();
	path.visited.reset();
	path.spNum = 0;
	for(int i = vl; ; ){	//从终点开始
		if(find(this->includingSet.begin(), this->includingSet.end(), i) != this->includingSet.end())
			path.spNum++;
		path.visited.set(i);

		if(this->p[i] == -1) {
			path.cost = -1;
			break;	//不存在这条路径
		}
		path.edges.push_back(this->p[i]);	//找到一条边
		if((i = allEdges[this->p[i]].from) != vi) continue;
		else{
			if(i != this->start && i != this->target) path.spNum++;
			path.visited.set(i);
			break;
		}
	}
}

void Path::printPath(class Dijkstra &work)
{
#ifdef PRINT_PAHT
	cout << "Path:" << start << "->" << target;
	cout << "cost:" << cost << endl;
	cout << "spNum:" << spNum << endl;
	cout << "Nodes:";
	for(int in = edges.size() - 1; in >= 0; in--) {
		if(in == (int)edges.size() - 1) cout << allEdges[edges[in]].from << "->" << allEdges[edges[in]].to;
		else cout << "->" << allEdges[edges[in]].to;
	}
	cout << endl;
	cout << "pre: " << i << ' ' << j << ' ' << k << endl; 
	cout << endl;
#endif
}

//你要完成的功能总入口
void search_route(char *topo[5000], int edge_num, char *demand)
{
	clock_t start = clock();
	clock_t end = 0;

	unsigned int seed = 9999999;	
	srand(seed);

	bool fmin = true; 
	bool cut = false; //是否剪枝

	bool hasPath = false; 	 	//当前迭代结束，是否还有有效路径
	bool notChangeD = true; 	//处理环时，是否改变D
	bool judgeCycle = true; 	// 判断环，true:无环则不处理 false:

	double uptime; //上限时间
	if(edge_num <= 1500) uptime = 8.8;
	else uptime = 7.8;
	uptime = 0;
	int speedtest = 0;

	Path outPath; //输出路径
	outPath.cost = INT_MAX;

/*SK**************************************************************************************************/
	Dijkstra work;
	work.init(topo, edge_num, demand);

	const int spNodesNum = work.includingSet.size();

	//这个D只能包好必须经过的节点和起点and终点。这里面的点的下标和includingSet中的下标必须一致，起点放最后一行，终点放最后一列。
	Path D[spNodesNum + 1][spNodesNum + 1];	//i:表示起点编号 j:表示终点编号;两点之间的最短路径矩阵,

	Path f[spNodesNum][spNodesNum][spNodesNum];	//路径经过哪些边的矩阵。

	memset(D, 0, sizeof(D)); //初始化矩阵D
	//Dijkstra构造两两之间的最短路径，若路径不存在其权重为-1
	bitset<maxn> rmNodes;
	
	for(int i = 0; i < spNodesNum; i++) {	//在special nodes中遍历起点
		rmNodes.reset();
		rmNodes.set(work.start);
		rmNodes.set(work.target);	
		work.dijkstra(work.includingSet[i], rmNodes);	//移除起点和终点进行计算
		for(int j = 0; j < spNodesNum; j++){
			if(i == j) continue;
			work.BuildPath(work.includingSet[i], work.includingSet[j], D[i][j]);
			D[i][j].printPath(work);
		}

		rmNodes.reset();
		rmNodes.set(work.start);	//只移除起点进行计算
		work.dijkstra(work.includingSet[i], rmNodes);

		work.BuildPath(work.includingSet[i], work.target, D[i][spNodesNum]);
		D[i][spNodesNum].printPath(work);
	}
	rmNodes.reset();
	rmNodes.set(work.target);	//只移除终点进行计算
	work.dijkstra(work.start, rmNodes);	
	for(int j = 0; j < spNodesNum; j++){
		work.BuildPath(work.start, work.includingSet[j], D[spNodesNum][j]);
		D[spNodesNum][j].printPath(work);
	}

	cout << "begin sk" << endl;
	//SK迭代中的变量定义
	int min, addl;
	int ll, rd;
	vector<int> vecaddl;

	int addj;

beginSK: //SK迭代
	speedtest++;
	memset(f, 0, sizeof(f));

	for(int i = 0; i < spNodesNum; i++) {	//i:只表示需要循环的次数
		//cout << "SK迭代i=" << i << endl;
		if(i == 0) {
			for(int j = 0; j < spNodesNum; j++) {	//j:遍历起点--vi
				for(int k = 0; k < spNodesNum; k++) {	//k:遍历终点--vl
					if(j == k) continue;
					if(D[j][k].cost > 0 && D[k][spNodesNum].cost > 0) {
						Path tmp = D[j][k];
						Path tmp2 = D[k][spNodesNum];
						D[j][k].handleCycle(D[k][spNodesNum], work, judgeCycle);
						if(D[j][k].cost > 0) {
							f[0][j][k] = D[j][k] + D[k][spNodesNum];
							f[0][j][k].i = k;
							f[0][j][k].j = spNodesNum;
							f[0][j][k].k = -1;
 						}
						else {
							D[j][k] = tmp;
							D[k][spNodesNum].handleCycle(D[j][k], work, judgeCycle);
							if(D[k][spNodesNum].cost > 0) {
								f[0][j][k] = D[j][k] + D[k][spNodesNum];
								f[0][j][k].i = j;
								f[0][j][k].j = k;
								f[0][j][k].k = -1;
							}
							else f[0][j][k].cost = -1;		
						}
						if(notChangeD) {
							D[j][k] = tmp;
							D[k][spNodesNum] = tmp2;
						}
					}
					else {
						cout << "f[0][j][k].cost = -1" << endl;
						f[0][j][k].cost = -1;	//这次迭代不存在这条路径
					}
					if(cut && f[0][j][k].cost != -1 && f[0][j][k].cost >= outPath.cost) f[0][j][k].cost = -1; //cut
				}	
			}
		}
		else {
			for(int j = 0; j < spNodesNum; j++) {	//j:遍历起点
				for(int k = 0; k < spNodesNum; k++) {	//k:遍历终点
					if(j == k) continue;
					if(D[j][k].cost <= 0) {
						f[i][j][k].cost = -1;
						continue;
					}
					min = INT_MAX;
					addl = -1;							
					vecaddl.clear();
					for(int l = 0; l < spNodesNum; l++) {
						if(k == l || j == l) continue;	//跳过起点和终点相同，或者出现环。
						if(f[i - 1][k][l].cost > 0) {
							vecaddl.push_back(l);
							if(D[j][k].cost + f[i - 1][k][l].cost < min) {
								min = D[j][k].cost + f[i - 1][k][l].cost;
								addl = l;
							}
						}	
					}

					if(addl != -1) {	//找到一条路径（若addl==-1则之前也不可能有这条路径）
						Path tmp = D[j][k];
						if(fmin) {
							D[j][k].handleCycle(f[i - 1][k][addl], work, judgeCycle);
							if(D[j][k].cost != -1) {
								f[i][j][k] = D[j][k] + f[i - 1][k][addl];
								f[0][j][k].i = i - 1;
								f[0][j][k].j = k;
								f[0][j][k].k = addl;
							}
							else f[i][j][k].cost = -1;
						}
						else {
							rd = rand() % vecaddl.size(); 
							ll = vecaddl[rd];
							D[j][k].handleCycle(f[i - 1][k][ll], work, judgeCycle);
							if(D[j][k].cost != -1) {
								f[i][j][k] = D[j][k] + f[i - 1][k][ll];
								f[0][j][k].i = i - 1;
								f[0][j][k].j = k;
								f[0][j][k].k = ll;
							}
							else f[i][j][k].cost = -1;
						}
						if(notChangeD) D[j][k] = tmp;	
					
						//SK--(2)--(3)
						if(f[i][j][k].cost < 0 && (int)f[i - 1][j][k].spNum >= i + 1) {
							f[i][j][k] = f[i - 1][j][k];
						}
						if((int)f[i][j][k].spNum >= i + 1 &&\
					           f[i - 1][j][k].spNum == f[i][j][k].spNum &&\
						   f[i - 1][j][k].cost < f[i][j][k].cost) {
							f[i][j][k] = f[i - 1][j][k];
						}
					}
					else if((int)f[i - 1][j][k].spNum >= i + 1) {
						f[i][j][k] = f[i - 1][j][k];				
					}
					else f[i][j][k].cost = -1;	//此条路径终结
					//cut
					if(cut && f[i][j][k].cost != -1 && f[i][j][k].cost >= outPath.cost) f[i][j][k].cost = -1;
				}	
			}
		} //迭代结束
		
		hasPath = false; //判断是否存在有效路径
		for(int j = 0; j < spNodesNum; j++) {		
			for(int k = 0; k < spNodesNum; k++) {
				if(j != k && f[i][j][k].cost > 0) {
					hasPath = true;
					break;
				}
			}
			if(hasPath) break;
		}

		if(hasPath == true) continue;
		else break;	
	}//迭代循环
	
	//vi = work.start;
	for(int i = 0; hasPath && i < spNodesNum; i++) {	//遍历D中的终点，也就是f中的起点
		min = INT_MAX;
		addj = -1;

		for(int j = 0; j < spNodesNum; j++) {	//遍历f中的终点
			if(i == j) continue;
			if(D[spNodesNum][i].cost > 0 && f[spNodesNum - 1][i][j].cost > 0 && \
			   D[spNodesNum][i].cost + f[spNodesNum - 1][i][j].cost < min) {
					min = D[spNodesNum][i].cost + f[spNodesNum - 1][i][j].cost;
					addj = j;
			}
		}

		if(addj != -1) {
			Path tmp = D[spNodesNum][i];

			D[spNodesNum][i].handleCycle(f[spNodesNum - 1][i][addj], work, judgeCycle);	
			if(D[spNodesNum][i].cost != -1 && D[spNodesNum][i].cost + f[spNodesNum - 1][i][addj].cost < outPath.cost) {
				outPath = D[spNodesNum][i] + f[spNodesNum - 1][i][addj];
				cout << "outPath.cost:" << outPath.cost << endl;	
			}

			if(notChangeD) D[spNodesNum][i] = tmp;
			
		}
	}

 	end = clock();
	if((end - start)/CLOCKS_PER_SEC > uptime && outPath.cost != INT_MAX) {
		for(int i = (int)outPath.edges.size() - 1; i >= 0; i--)
			record_result(outPath.edges[i]);

		cout << "speedtest:" << speedtest << endl;
		return;
	}
	else {
		if(fmin) fmin = false;
		goto beginSK;
	}
}
