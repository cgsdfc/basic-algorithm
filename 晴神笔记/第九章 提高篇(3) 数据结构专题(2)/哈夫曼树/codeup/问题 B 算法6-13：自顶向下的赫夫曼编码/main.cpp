#include <cassert>
#include <climits>
#include <cstdio>
#include <queue>
#include <string>
using namespace std;

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

// 总叶子节点数。
#define MAXN 105
// 哈夫曼树的总节点数，由总叶子节点数确定。
#define MAXV (2 * MAXN - 1)

struct Node {
    int lchild, rchild;  // 自顶向下需要记录孩子指针。
    int weight;          // 权重。
    /*
    题目给的算法，没有用堆，所以当遇到相同的权重时，
    它优先选择输入序列里面考前的元素（也就是用线性扫描来
    找最小值），我们用堆模拟，必须还原这种优先级，才能
    得到一样的答案。
    */
    int id;
} node[MAXV];

// 保存 0--N-1 各个节点的编码。
string code[MAXN];

int index = 0;

int NewNode() {
    return index++;
}

struct cmp {
    // 注意：相同的权重，id小的先出现，因为要模拟线性扫描的特性。
    bool operator()(int a, int b) {
        // weight 小的先出队。
        if (node[a].weight != node[b].weight) { return node[a].weight > node[b].weight; }
        // id小的先出队。
        return node[a].id > node[b].id;
    }
};

// 构建哈夫曼树，返回根节点。
int Build(int N) {
    // 注意哈夫曼编码必备小顶堆，即greater。
    priority_queue<int, vector<int>, cmp> Q;
    // 输入N个权重，构建成叶子节点。
    int id = 0;
    while (N--) {
        int w;
        scanf("%d", &w);
        int p = NewNode();
        node[p].weight = w;
        node[p].lchild = node[p].rchild = -1;  // 一开始既是根节点，也是叶节点。
        node[p].id = id++;
        Q.push(p);
    }
    // 新生成的节点，其id要继续编号。
    while (Q.size() > 1) {
        int a = Q.top();
        Q.pop();
        int b = Q.top();
        Q.pop();
        /*
        注意，两个最小元，以id的顺序出现。
        */
        if (node[a].id > node[b].id) { swap(a, b); }

        //		printf("%d %d\n", node[a].weight, node[b].weight);

        int root = NewNode();
        node[root].weight = node[a].weight + node[b].weight;
        node[root].id = id++;
        node[root].lchild = a;
        node[root].rchild = b;
        Q.push(root);
    }
    return Q.top();
}

void PopBack(string& s) {
    s.erase(s.end() - 1);
}

// 在生成了哈夫曼树的基础上，用自顶向下的方法生成编码。
// 编码的输出顺序和上次一样，是从根到叶子的路径的顺序。
void DFS(int root, string& now) {
    if (root == -1) return;
    if (node[root].lchild != -1) {
        // 必有两个孩子。
        assert(node[root].rchild != -1);

        now.push_back('0');
        DFS(node[root].lchild, now);
        /*
        string.pop_back 是 C++11 特性。
        */
        PopBack(now);
        //		now.pop_back();

        now.push_back('1');
        DFS(node[root].rchild, now);
        //		now.pop_back();
        PopBack(now);
    } else {
        // 叶子，输出到code，因为DFS生成编码的顺序和叶子节点的输入顺序不一致，
        // 必须先保存再输出。
        code[root] = now;
    }
}

/*
生成哈夫曼编码。
注意：
1. 靠近根的节点权重大，靠近叶子的节点权重小，因此，
要用小顶堆，每次选择权重最小的两个节点进行合并。
*/
int main(int argc, char** argv) {
    int N;
    while (scanf("%d", &N) != EOF) {
        index = 0;
        int root = Build(N);
        // 注意，0--N-1是叶子。
        string str;
        DFS(root, str);
        for (int i = 0; i < N; ++i) {
            puts(code[i].c_str());
        }
    }
    return 0;
}
