#include <algorithm>
#include <cstdio>
#include <queue>
#include <vector>

using namespace std;

// 用于邻接矩阵标记边不存在。
// G[i][j]=INF 表示 i到j没有边。
const int INF = 1000000000;

/*
图DFS遍历模板。
一些大模拟，比如《点亮数字人生》，可以套用DFS模板，来确保
一个器件的输入端都计算好了。DFS还可以判断图是否有环。
*/

#define MAXN 100

int N; // 节点数。

// 节点的编号可以是题目给出，也可以是自己转换而来，比如题目给的是字符串，用map
// 转换为int。下标可能从0或者1开始。
bool vis[MAXN];

int G[MAXN][MAXN]; // 邻接矩阵。

// 访问u所在的联通块的所有节点（无向图的联通分量，有向图的弱联通分量）。
void DFS(int u, int depth) {
  vis[u] = true; // 标记为已访问。
  // 枚举u的邻居，即从u出发可以达到的节点。
  // 节点编号从0--N-1.

  // 对节点进行操作。

  // 枚举下一个节点。
  for (int v = 0; v < N; ++v) {
    if (!vis[v] && G[u][v] != INF) {
      // u可达，并且未访问。
      DFS(v, depth + 1);
    }
  }
  // 注意，和回溯法的DFS不同，这里不需要恢复vis的值，因为我们不是
  // 在枚举全部的路径（即根到叶子的路径），而是访问全部节点。
  // 如果是枚举全部路径，则一个节点会被访问多次（因为一个节点可以出现
  // 在多个路径）。如果是访问全部节点，则一个节点只应该被访问一次。

  // 而且注意，回溯法解题时，遍历的一般是树（无环，层次结构，有根）；
  // 而DFS遍历图时，遍历的图可能是有环的。所以回溯法不需要vis数组 （因为无环），
  // 但DFS遍历图需要。
}

// 访问整个图（可能包含多个联通块）。
void DFSTrave() {
  // 先初始化。一次遍历后vis数组全部为true。
  fill(vis, vis + N, false);
  for (int v = 0; v < N; ++v) {
    if (!vis[v]) {
      // 一个新的联通分量。
      DFS(v, 1);
    }
  }
}

/*
邻接表的DFS。
*/

vector<int> Adj[MAXN];

/*
和 邻接矩阵 的版本基本上一致，除了枚举u的可达节点的部分。
*/
void DFS2(int u, int depth) {
  vis[u] = true;
  for (int i = 0; i < Adj[u].size(); ++i) {
    // 遍历u的邻接表。
    int v = Adj[u][i];
    if (!vis[v]) {
      DFS2(v, depth + 1);
    }
  }
}

void DFSTrave2() {
  // 和DFSTrave是一样的，除了调用DFS2.
  for (int v = 0; v < N; ++v) {
    if (!vis[v]) {
      DFS2(v, 1); // 初始深度为1.
    }
  }
}

/*
BFS 模板
BFS需要一个inq数组，作用与DFS的vis数组类似，标志一个节点是否加入过队列。
1. 每个节点仅入队一次，仅出队一次。
2. 一个节点仅在inq=false时加入队列。
3. 一个节点加入队列后，应立刻设置inq=true。
4. 一次BFS调用，能把u所在的联通块的所有节点的inq设为true，如果图不是联通图，
则要对所有inq=false的节点各调用一次BFS，每次都处理一个联通块。
*/

bool inq[MAXN];

void BFS(int u) {
  queue<int> Q;
  Q.push(u);
  inq[u] = true;
  while (!Q.empty()) {
    int u = Q.front();
    Q.pop();
    for (int v = 0; v < N; ++v) {
      if (!inq[v] && G[u][v] != INF) {
        // v是u的邻居，并且v未曾入队。
        Q.push(v);
        inq[v] = true;
      }
    }
  }
}

// 全图BFS。
void BFSTrave() {
  fill(inq, inq + N, false); // 标记全部节点未入队。
  for (int u = 0; u < N; ++u) {
    if (!inq[u]) { // 这里和DFSTrave是类似的。
      BFS(u);
    }
  }
}

// 邻接表的BFS完全类似，不再重复。

/*
给定源点s，求BFS过程中各节点的层号。
*/
struct Node {
  int v;     // 节点。
  int layer; // 层号
};

/*
Node 保存了求解出来的层号。
可能需要后续处理。
*/
vector<Node> Adj2[MAXN];

void BFS2(int s) { // BFS树的根，即源点。
  queue<Node> Q;
  // 源点层号设为0，源点入队。
  Node start;
  start.v = s;
  start.layer = 0;
  Q.push(start);
  inq[start.v] = true;
  while (!Q.empty()) {
    Node topNode = Q.front();
    Q.pop();
    int u = topNode.v;
    for (int i = 0; i < Adj2[u].size(); ++i) {
      Node next = Adj2[u][i];
      next.layer = topNode.layer +
                   1; // 注意，next可能inq=true，但是没关系，因为不会访问了。
      if (!inq[next.v]) {
        // 得出了next的层号。
        inq[next.v] = true;
        Q.push(next);
      }
    }
  }
}

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

int main(int argc, char **argv) { return 0; }
