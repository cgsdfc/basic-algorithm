#include <algorithm>
#include <cstdio>
#include <map>
using namespace std;

/*
给定一棵三叉树，求孩子最多，深度最大，并且前序遍历最先遍历到的节点，
以及前序遍历的序号。

前序遍历树，求分支最多和深度最大的节点。注意，深度是从根节点算起的，高度是从
叶子节点算起的，根节点高度最大，深度为0，叶子深度最大，高度为0.

输入的节点id不是连续整数，-1表示没有孩子。
*/

int N;  // 行数，注意不是所有节点都有自己的一行，所以节点数最多为 4*N 。

const int MAXN = 1e4 + 5;
const int MAXV = 4 * MAXN;  // 节点数。

const int MAXC = 3;  // 三叉树。

struct Node {
    int data;  // 输入的数字。
    int fa;    // 找根。
    int child[MAXC];
    int num;  // 孩子个数。

    Node() {
        fa = -1;
        num = 0;
        fill(child, child + MAXC, -1);
    }
} node[MAXV];

int index;

map<int, int> mp;
bool IsCh[MAXV];

int Map(int data) {
    if (mp.count(data)) {
        return mp[data];
    } else {
        mp[data] = index;
        node[index].data = data;
        return index++;
    }
}

struct State {
    // 对应节点。
    int v;
    int index;  // 在先序遍历的序号。
    // 当前深度和孩子数。
    int depth;
    int num;

    State(int vv, int ii, int dd, int nn): v(vv), index(ii), depth(dd), num(nn) {}
    friend bool operator<(State& a, State& b) {
        if (a.num != b.num) return a.num < b.num;
        return a.depth < b.depth;
    }
};

int PreOrderIndex = 1;

void DFS(int v, int depth, State& maxS) {
    // 先序遍历。
    State now(v, PreOrderIndex, depth, node[v].num);
    ++PreOrderIndex;
    if (maxS < now) { maxS = now; }
    for (int i = 0; i < MAXC; ++i) {
        int u = node[v].child[i];
        if (u != -1) { DFS(u, depth + 1, maxS); }
    }
}

int FindRoot() {
    // 题目没说根节点在一开始给出。
    for (int i = 0; i < index; ++i) {
        if (-1 == node[i].fa) { return i; }
    }
    return -1;
}

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

int main(int argc, char** argv) {
    scanf("%d", &N);
    while (N--) {
        int u;
        scanf("%d", &u);
        u = Map(u);
        for (int i = 0; i < MAXC; ++i) {
            int v;
            scanf("%d", &v);
            if (v != -1) {
                v = Map(v);
                node[u].child[i] = v;
                node[u].num++;
                node[v].fa = u;
            }
        }
    }
    int root = FindRoot();
    State maxS(-1, -1, -1, -1);
    DFS(root, 0, maxS);
    printf("%d %d", node[maxS.v].data, maxS.index);

    return 0;
}
