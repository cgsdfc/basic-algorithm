#include <algorithm>
#include <cmath>
#include <cstdio>
#include <queue>
#include <vector>
using namespace std;

/*
求出所有叶子到根的路径长度，以及最大值，
然后求出最长路径对应的价钱。然后求出有多少最大路径的节点。
*/

#define MAXN (100000 + 5)

// int father[MAXN];
// bool leaf[MAXN];
int N;
double P, r;
int root;

struct Node {
  int deep; // 深度。
  vector<int> child;
};

Node node[MAXN];
// 所有叶节点的深度。
vector<int> leaf;

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

/*
从叶子到根，会导致某些顶层的路径被重复遍历很多次，所以复杂度不是N，
而是接近N平方。
而从根开始计算每一个节点的深度，虽然看似计算了非叶节点的深度（而只需要叶节点的
深度），但是复杂度却是N。这就是BFS，在BFS过程中，还可以计算最大的深度。
*/

int BFS() {
  queue<int> Q;
  Q.push(root);
  node[root].deep = 0;
  int ans = 0; // 初始化为根的深度。

  while (!Q.empty()) {
    int now = Q.front();
    Q.pop();
    if (node[now].child.empty()) {
      // 我是叶节点。
      leaf.push_back(node[now].deep);
    }

    for (int i = 0; i < node[now].child.size(); ++i) {
      int p = node[now].child[i];
      Q.push(p);
      node[p].deep = node[now].deep + 1;
      if (node[p].deep > ans) {
        ans = node[p].deep;
      }
      // 这样写不对，因为根有可能是叶节点，而这里只考虑了非根的叶节点。
      /*
      这样写的主要目的是以空间换时间，
      因为叶节点数量比全部节点数量少。
      但是优化的不对反而会造成错误。
      */
    }
  }
  return ans;
}

int main(int argc, char **argv) {
  scanf("%d%lf%lf", &N, &P, &r);

  for (int i = 0; i < N; ++i) {
    node[i].child.clear();
  }

  for (int i = 0; i < N; ++i) {
    // 输入父亲节点。
    int p;
    scanf("%d", &p);
    if (p == -1) {
      // 记录根节点。
      root = i;
    } else {
      node[p].child.push_back(i);
    }
  }

  int ans = BFS();
  double price = P * pow(1 + r / 100, ans);
  int num = 0;
  //	for (int i=0;i<N;++i) {
  //		if (node[i].deep==ans) {
  //			++num;
  //		}
  //	}
  for (vector<int>::iterator it = leaf.begin(); it != leaf.end(); ++it) {
    if (ans == *it) {
      ++num;
    }
  }
  //	printf("root %d ans %d\n", root, ans);

  printf("%.2f %d\n", price, num);

  return 0;
}
