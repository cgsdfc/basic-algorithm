#include <algorithm>
#include <cstdio>
#include <vector>  // 多叉树必备
using namespace std;

#define MAXN 105

struct Node {
    int weight;         // 点权。
    vector<int> child;  // 按递减排列。
} node[MAXN];

/*
注意排序是按照节点a的权重大的在全面，
即先考虑权重大的子节点。
*/
bool cmp(int a, int b) {
    return node[a].weight > node[b].weight;
}

struct {
    int data[MAXN];
    int len;
} ans;

const int Root = 0;
int S;  // 目标和。
int N, M;

/*
此函数本质上遍历了所有的根到叶子的路径，
可作为模板。
*/
void DFS(int root, int nowS) {
    /*
    考虑当前节点。
    */
    nowS += node[root].weight;
    // 注意输出的是权重。
    ans.data[ans.len++] = node[root].weight;

    // 多叉树不会遇到空树，只会遇到子节点。
    if (node[root].child.empty()) {
        // 递归边界。
        if (nowS == S) {
            // 得到一个解。
            for (int i = 0; i < ans.len; ++i) {
                printf("%d%s", ans.data[i], i == ans.len - 1 ? "\n" : " ");
            }
        }
    } else {
        for (int i = 0; i < node[root].child.size(); ++i) {
            int p = node[root].child[i];
            DFS(p, nowS);
        }
    }
    ans.len--;
}

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

int main(int argc, char** argv) {
    scanf("%d%d%d", &N, &M, &S);
    for (int i = 0; i < N; ++i) {
        scanf("%d", &node[i].weight);
    }
    for (int i = 0; i < M; ++i) {
        int id, k;
        scanf("%d%d", &id, &k);
        while (k--) {
            int c;
            scanf("%d", &c);
            node[id].child.push_back(c);
        }
        sort(node[id].child.begin(), node[id].child.end(), cmp);
    }
    DFS(Root, 0);

    return 0;
}
