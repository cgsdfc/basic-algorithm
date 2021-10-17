#include <algorithm>
#include <cassert>
#include <cstdio>
#include <vector>
using namespace std;

/*
先前序遍历树，为每个节点标序号，然后DFS找最短路（其实就是简单路径），
按照路径最短和前序序号最小的原则更新，同时记录路径。
复杂度是遍历图，即O(V+E)。

输出打印机的编号和电脑到打印机的路径。
*/

// （类型：0表示交换机，1表示计算机，2表示打印机）
enum {
    SW,
    COM,
    PRI,
};

#define MAXP 10  // 端口号

struct Node {
    int type;
    int ord;  // 前序序号。
    int fa;
    int child[MAXP];

    Node() {
        fa = -1;
        fill(child, child + MAXP, -1);
    }
};

#define MAXN 505

Node node[MAXN];
bool vis[MAXN];
int N;  // 节点编号1--N，0表示没有父节点。

void PreOrder(int root, int& index) {
    if (root != -1) {
        node[root].ord = index++;
        for (int i = 0; i < MAXP; ++i) {
            PreOrder(node[root].child[i], index);
        }
    }
}

vector<int> Path, tempPath;

// 从源点出发找到每一台打印机。
void DFS(int v) {
    vis[v] = true;
    tempPath.push_back(v);
    if (node[v].type == PRI) {
        // 找到一台打印机。
        if (Path.empty() || (tempPath.size() < Path.size()) ||
            (tempPath.size() == Path.size() && node[v].ord < node[Path.back()].ord)) {
            Path = tempPath;  // 注意更新条件。
        }
    } else {
        // 因为是无向图，从父节点和孩子节点出发遍历。
        int u = node[v].fa;
        if (u != -1 && !vis[u]) { DFS(u); }
        for (int i = 0; i < MAXP; ++i) {
            int u = node[v].child[i];
            if (u != -1 && !vis[u]) { DFS(u); }
        }
    }
    vis[v] = false;
    tempPath.pop_back();
}

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */
int Root;
int S;  // 源点。

int main(int argc, char** argv) {
    scanf("%d", &N);
    fill(node, node + MAXN, Node());
    fill(vis, vis + MAXN, false);

    for (int i = 0; i < N; ++i) {
        int id, type, fa, port;
        // 注意，端口号是用来给孩子节点排序的。
        scanf("%d%d%d%d", &id, &type, &fa, &port);
        node[id].type = type;
        if (!fa) {
            Root = id;
        } else {
            node[id].fa = fa;
            node[fa].child[port] = id;
        }
    }
    scanf("%d", &S);
    int index = 0;
    PreOrder(Root, index);
    DFS(S);
    int v = Path.back();  // 打印机的编号。
    assert(node[v].type == PRI);
    printf("%d\n", v);

    for (int i = 0; i < Path.size(); ++i) {
        printf("%d%s", Path[i], i == Path.size() - 1 ? "\n" : " ");
    }

    return 0;
}
