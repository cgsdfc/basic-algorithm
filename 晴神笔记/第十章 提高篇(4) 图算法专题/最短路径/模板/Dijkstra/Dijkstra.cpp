/*
迪杰斯特拉算法

计算源点s到所有节点的最短距离，单源最短路。

适用于：
        非负边权的最短路

时间复杂度：
        邻接矩阵：O(V^2)
        邻接表：O(V^2 + E)

堆优化：
        O(VlogV+E)

数据结构：
        1. 距离数组d，记录源点到所有节点的最短距离。
        2. 标记数组vis，记录某节点是否已访问，作用是：
                1. 已访问的节点，最短距离已经确定，不可以再优化。
                2. 优化距离时，只考虑未访问的节点。
*/

#include <algorithm> // fill
#include <cstdio>
#include <queue> // pq
#include <vector>
using namespace std;

#define MAXN 1000 // 节点数上限，注意节点从0--N-1 。

int N; // 节点数。

int d[MAXN];    // 距离数组，初始化为 INF
bool vis[MAXN]; // 标记数组，初始化为 false
const int INF = 1e9;

// 表示一条带权边。
struct Node {
  int v;    // 终点。
  int dist; // 边权。
  Node(int v_, int dist_) {
    v = v_;
    dist = dist_;
  }
};

// 注意邻接表要带上边权。
vector<Node> Adj[MAXN]; // 邻接表。

/*
邻接表版本迪杰斯特拉
距离数组即为输出。该算法能处理有向图，无向图也可以通过“重边法”转换为有向图。
s：源点。
*/

void Dijkstra(int s) {
  // 初始化。
  fill(d, d + N, INF);       // 距离无穷大。
  fill(vis, vis + N, false); // 节点未访问。
  d[s] = 0; // 注意，这个容易漏掉！！没有这个循环只进行一步。

  for (int i = 0; i < N; ++i) { // 循环N轮，每轮解决一个节点。
    // 查找当前最优节点。
    int u = -1;
    int MIN = INF;
    // 线性扫描，如果查找不到小于INF的节点，则说明剩下节点全部不可达。
    for (int j = 0; j < N; ++j) {
      if (!vis[j] && d[j] < MIN) {
        // 注意已访问节点不要考虑。
        u = j;
        MIN = d[j];
      }
    }
    if (u == -1) {
      // 不存在比INF更优的节点，所以不可能继续优化。
      return;
    }
    // 找到当前最优节点u，根据贪心策略，u就是全局最优解。
    vis[u] = true;
    // 根据u进行优化，即通过u为中间节点，优化其他未访问节点的d。
    // 实际上要处理的节点就是u的邻居。即遍历u的邻居。
    for (int j = 0; j < N; ++j) {
      int v = Adj[u][j].v;
      int dist = Adj[u][j].dist;
      if (!vis[v] && d[u] + dist < d[v]) {
        // 存在更优解。
        d[v] = d[u] + dist;
      }
    }
  }
}

// 邻接矩阵，保存边权，或者INF，如果边不存在。
// 注意建图时，要使边不存在的矩阵元素为INF，用fill。
int G[MAXN][MAXN];

/*
邻接矩阵的Dijkstra。
唯一的区别是优化操作的遍历邻居部分。
*/
void Dijkstra2(int s) {
  fill(d, d + N, INF);
  fill(vis, vis + N, false);
  d[s] = 0;
  for (int i = 0; i < N; ++i) {
    int u = -1;
    int MIN = INF;
    for (int j = 0; j < N; ++j) {
      if (!vis[j] && d[j] < MIN) {
        u = j;
        MIN = d[j];
      }
    }
    if (u == -1) {
      return;
    }
    // u的最短距离在前几轮产生，只是在这一轮才能确定u的最短距离不会再变化了。
    // 也就是说，每轮的最短距离的最小值，不可能再更优了，因此就定下来了。
    vis[u] = true;
    for (int v = 0; v < N; ++v) {
      if (!vis[v] && G[u][v] != INF && G[u][v] + d[u] < d[v]) {
        d[v] = G[u][v] + d[u];
      }
    }
  }
}

/*
堆优化的Dijkstra，邻接表版本

注意堆优化对原来版本的修改：
1. 堆的元素类型，必须建立节点和其最短距离的联系，即用Node。
2. 堆的比较函数，使小的距离先出队。
3. 优化操作时对堆的操作。
*/

struct cmp {
  bool operator()(Node a, Node b) {
    return a.dist > b.dist; // 小顶堆。
  }
};

typedef priority_queue<Node, vector<Node>, cmp> PQueue;

/*
注意堆的处理。
*/
void Dijkstra3(int s) {
  PQueue Q;
  fill(vis, vis + N, false);
  fill(d, d + N, INF);
  d[s] = 0;
  Q.push(Node(s, 0));

  // 用类似BFS的写法，更顺手。
  while (!Q.empty()) {
    Node top = Q.top();
    Q.pop();
    if (vis[top.v]) {
      continue;
      // 是个冗余元素，因为更优的距离被发现了，并标记为已访问，而旧的解无法从堆中删除。
      // 注意，这种冗余元素是无法避免的。
    }
    // 如果Q变为空都找不到v，则算法结束，不需要特判。
    int v = top.v;
    vis[v] = true;
    // 优化操作，被优化的节点要插入堆（否则不会被算法考虑）。
    for (int i = 0; i < Adj[v].size(); ++i) {
      int u = Adj[v][i].v;
      int dist = Adj[v][i].dist;
      // 经过v的路径更近。
      if (!vis[u] && d[v] + dist < d[u]) {
        d[u] = d[v] + dist;
        // 注意，把更优的距离直接加入堆，当最优解出队后，
        // vis设为true，则其他相同节点的距离的节点，就会被忽略掉。
        Q.push(Node(u, d[u]));
      }
    }
  }
}

/*
堆优化，邻接矩阵。
*/
void Dijkstra4(int s) {
  // 初始化。
  fill(vis, vis + N, false);
  fill(d, d + N, INF);
  PQueue Q;
  Q.push(Node(s, 0));
  d[s] = 0;

  while (!Q.empty()) {
    Node top = Q.top();
    if (vis[top.v]) {
      continue;
    }
    int u = top.v;
    vis[u] = true;
    for (int v = 0; v < N; ++v) {
      // 特判一下INF，可以防止溢出。
      if (!vis[v] && G[u][v] != INF && G[u][v] + d[u] < d[v]) {
        d[v] = G[u][v] + d[u];
        Q.push(Node(v, d[v]));
      }
    }
  }
}

/*
记录最短路径。

某个节点可能存在多条最短路径，
方法1：每个节点记录其在最短路径的前驱，即维护int数组pre，
整个pre数组组成一棵最短路径树（最小生成树？）。此法只能得到其中一条
最短路径。

方法2：可以得到全部的最短路径，即每个节点记录其在多条最短路径的前驱，即维护vector<int>数组pre，
本质上是最短路径图（最短路径图就是包括了所有节点的最短路径的图，必然是无环的，如果有环，则
走环的路径必然更长，不可能是最短路径）。

以堆优化的邻接矩阵版本为例子，实际上，只需要在优化操作里面维护pre数组即可。
方法1，2维护的方法不同。
*/

/*
计算每个节点的某条最短路径。
*/
int pre[MAXN];

void Dijkstra5(int s) {
  // 初始化。
  fill(vis, vis + N, false);
  fill(d, d + N, INF);
  /*
  pre的初始化，令各个元素为i，表示每个前驱为点自身。
  如果图是联通图，则最后pre是一颗树，s是唯一的根，只有s使得
  pre[s]=s。这在打印路径有用。
  */
  for (int i = 0; i < N; ++i) {
    pre[i] = i;
  }

  PQueue Q;
  Q.push(Node(s, 0));
  d[s] = 0;

  while (!Q.empty()) {
    Node top = Q.top();
    if (vis[top.v]) {
      continue;
    }
    int u = top.v;
    vis[u] = true;
    for (int v = 0; v < N; ++v) {
      // 特判一下INF，可以防止溢出。
      if (!vis[v] && G[u][v] != INF && G[u][v] + d[u] < d[v]) {
        d[v] = G[u][v] + d[u];
        Q.push(Node(v, d[v]));
        /*
        pre的更新。
        */
        pre[v] = u; // 被优化的v的前驱是当前最优解u。
      }
    }
  }
}

/*
递归打印最短路径。
s：源点。
v：终点。（当前节点）
*/
void PrintPath(int s, int v) {
  if (s == v) {
    printf("%d\n", s);
    return;
  }
  // 先打印父节点的路径。
  PrintPath(s, pre[v]);
  printf("%d\n", v);
}

/*
计算每个节点的全部最短路径。
pre2的元素存放的是某节点的全部前驱。
*/
vector<int> pre2[MAXN];

void Dijkstra6(int s) {
  // 初始化。
  fill(vis, vis + N, false);
  fill(d, d + N, INF);
  /*
  注意，无需初始化，vector自动初始化为空。
  */

  PQueue Q;
  Q.push(Node(s, 0));
  d[s] = 0;

  while (!Q.empty()) {
    Node top = Q.top();
    if (vis[top.v]) {
      continue;
    }
    int u = top.v;
    vis[u] = true;
    for (int v = 0; v < N; ++v) {
      // 特判一下INF，可以防止溢出。
      if (!vis[v] && G[u][v] != INF) {
        // 注意，加入pre后，等于当前最优解的情况也要处理。
        if (G[u][v] + d[u] < d[v]) {
          d[v] = G[u][v] + d[u];
          Q.push(Node(v, d[v]));
          // 当前是更优解，之前收集的前驱没用了。
          pre2[v].clear();
          // 这里的逻辑，就是一边计算最大值，一边记录达到最大值的原像的逻辑。
          pre2[v].push_back(u);
        } else if (G[u][v] + d[u] == d[v]) {
          // 相同长度的路径又多了一条，要增加一个前驱。
          pre2[v].push_back(u);
        }
      }
    }
  }
}

vector<int> tempPath;

/*
递归打印路径。
如果对路径的输出有排序的要求，可以对pre的每一个vector进行排序，而不必
把全部路径存储起来排序。每个路径的输出格式是从源点到终点的节点序列，空格分隔。
*/
void PrintPath2(int s, int v) {
  if (s == v) {
    // s为起点，到达了递归边界。
    tempPath.push_back(s);
    // 打印路径。注意，tempPath逆序保存路径，要逆序输出。
    for (int i = tempPath.size() - 1; i >= 0; --i) {
      printf("%d%s", tempPath[i], i == 0 ? "\n" : " ");
    }
    tempPath.pop_back();
    return;
  }
  tempPath.push_back(v);
  for (int i = 0; i < pre2[v].size(); ++i) {
    PrintPath2(s, pre2[v][i]);
  }
  tempPath.pop_back();
}

/*
第二标尺问题。

距离最短的路径往往有多条，故要使答案唯一，题目往往加入第二标尺，有以下几种：
1. 新增边权，要求路径的边权和最小。
2. 新增点权，要求路径的点权和最小。
3. 统计最短路径的条数（如果不需要输出具体路径的话，是不需要使用vector的。
*/

/*
新增边权。

注意到最短路径问题本身就是求边权和最小的路径，所以增加新的一组边权是完全类似的。
首先，需要记录题目输入的边权，即三元组(u,v,c)，点u到点v的边，及其边权c。可以用二维矩阵cost表示。
然后，类比距离数组d，新增代价数组c，表示源点到u的路径的最小边权和。
最后，是对算法的修改：
1. 初始化新增的数据结构。
2. 修改优化操作的逻辑，同步更新数组c。
*/

int cost[MAXN][MAXN]; // 题目输入数据，cost[u][v] 代表边 u->v 的边权。
int c[MAXN]; // 代表源点到u的最小花费（边权和），随d数组一起更新。

// 这里假设要最小化新边权cost。
void Dijkstra7(int s) {
  // 初始化。
  fill(vis, vis + N, false);
  fill(d, d + N, INF);
  fill(c, c + N, INF);
  PQueue Q;
  Q.push(Node(s, 0));
  d[s] = 0;
  c[s] = 0;

  while (!Q.empty()) {
    Node top = Q.top();
    if (vis[top.v]) {
      continue;
    }
    int u = top.v;
    vis[u] = true;
    for (int v = 0; v < N; ++v) {
      if (!vis[v] && G[u][v] != INF) {
        // 当第一标尺出现更优时，同时更新两个标尺的当前最优，即d和c。
        if (G[u][v] + d[u] < d[v]) {
          d[v] = G[u][v] + d[u];
          c[v] = cost[u][v] + c[u];
          // 注意d和c的更新是完全类似的。
          Q.push(Node(v, d[v]));
          // 当第一标尺和当前最优相同时，考虑第二标尺并更新。
        } else if (G[u][v] + d[u] == d[v] && cost[u][v] + c[u] < c[v]) {
          // 此时只需更新第二标尺。
          c[v] = cost[u][v] + c[u];
        }
      }
    }
  }
}

/*
新增点权。

假设题目要求在最短路径的基础上，要求路径的节点点权和最大（比如说每个城市有些物资，要使得收集的
物质最大）。点权由题目输入，记录在数组weight中，新增数组w，表示源点s到节点u的路径的最大点权和，
更新规则与新增边权是类似的，即先考虑第一标尺（距离），然后考虑第二标尺。注意新增点权的写法略有不同。
*/
int weight[MAXN]; // 题目输入。
int w[MAXN]; // 源点s到节点u的路径的最大点权和。即当前s到u的最大点权和。

void Dijkstra8(int s) {
  // 初始化。
  fill(vis, vis + N, false);
  fill(d, d + N, INF);
  fill(w, w + N,
       0); // 求最小时，初始时为INF，求最大时，初始时为0（非负数的最大最小）。

  PQueue Q;
  Q.push(Node(s, 0));
  d[s] = 0;
  w[s] = weight[s];

  while (!Q.empty()) {
    Node top = Q.top();
    if (vis[top.v]) {
      continue;
    }
    int u = top.v;
    vis[u] = true;
    for (int v = 0; v < N; ++v) {
      if (!vis[v] && G[u][v] != INF) {
        if (G[u][v] + d[u] < d[v]) {
          d[v] = G[u][v] + d[u];
          // s->u, u->v = s->v
          w[v] = weight[v] + w[u];

          Q.push(Node(v, d[v]));
          // 当第一标尺和当前最优相同时，考虑第二标尺并更新。
        } else if (G[u][v] + d[u] == d[v] && weight[v] + w[u] > w[v]) {
          // 此时只需更新第二标尺。
          w[v] = weight[v] + w[u];
        }
      }
    }
  }
}

/*
求最短路径条数。
设置num数组，表示s到u的最短路径条数，更新规则和求全部最短路径类似。
*/
int num[MAXN];

void Dijkstra9(int s) {
  // 初始化。
  fill(vis, vis + N, false);
  fill(d, d + N, INF);
  fill(num, num + N, 0);

  PQueue Q;
  Q.push(Node(s, 0));
  d[s] = 0;
  num[s] = 1; // 注意，到源点s的最短路有且仅有一条。

  while (!Q.empty()) {
    Node top = Q.top();
    if (vis[top.v]) {
      continue;
    }
    int u = top.v;
    vis[u] = true;
    for (int v = 0; v < N; ++v) {
      if (!vis[v] && G[u][v] != INF) {
        if (G[u][v] + d[u] < d[v]) {
          d[v] = G[u][v] + d[u];
          num[v] = num[u]; // 因为经过u的路径更短，所以之前求出的v的最短路
                           // 不再是最短了，数量必须改。
        } else if (G[u][v] + d[u] == d[v]) {
          // 经过u的路径和v的当前最短路径一样长，所以累加。
          num[v] += num[u];
        }
      }
    }
  }
}
