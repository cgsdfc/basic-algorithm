#include <cassert>
#include <cstdio>
#include <map>
#include <set>
#include <vector>
using namespace std;

/*
用map实现的邻接表，过了。
*/
// 节省内存。
struct Node {
  bool vis;
  vector<int> list;
  Node() { vis = false; }
  void push_back(int u) { list.push_back(u); }
};

map<int, Node> Adj;
typedef map<int, Node>::iterator It;

void DFS(int u) {
  Node &p = Adj[u];
  p.vis = true;
  for (int i = 0; i < p.list.size(); ++i) {
    int v = p.list[i];
    if (!Adj[v].vis) {
      DFS(v);
    }
  }
}

void DFSTrave() {
  int ans = 0;
  for (It it = Adj.begin(); it != Adj.end(); ++it) {
    int u = it->first;
    if (!it->second.vis) {
      ++ans;
      DFS(u);
    }
  }
  printf("%d\n", ans);
}

int main(int argc, char **argv) {
  int a, b;
  while (scanf("%d%d", &a, &b) != EOF) {
    Adj[a].push_back(b);
    Adj[b].push_back(a);
  }
  DFSTrave();

  return 0;
}
