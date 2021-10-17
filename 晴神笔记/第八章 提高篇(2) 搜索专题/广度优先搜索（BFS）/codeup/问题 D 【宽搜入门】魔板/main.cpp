#include <cassert>
#include <cstdio>
#include <cstring>
#include <queue>
#include <string>  // op是逆序产生的。
using namespace std;

const int N = 2;
const int M = 4;

struct Node {
    int A[2][4];
    string ops;  // 得到此节点的操作序列。
    int hash;

    bool operator==(const Node& p) {
        return hash == p.hash;
    }
    int ComputeHash() {
        int ans = 0;
        // 注意要转为8进制数。
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < M; ++j) {
                ans = ans * 8 + (A[i][j] - 1);
            }
        }
        return ans;
    }
    int Hash() {
        return hash;
    }
    int Read() {
        for (int i = 0; i < M; ++i) {
            if (scanf("%d", &A[0][i]) == EOF) return EOF;
        }
        for (int i = M - 1; i >= 0; --i) {
            if (scanf("%d", &A[1][i]) == EOF) return EOF;
        }
        hash = ComputeHash();
        return 0;
    }
    void Print() {
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < M; ++j) {
                printf("%d ", A[i][j]);
            }
            printf("\n");
        }
        printf("\n");
    }

    Node Next(char _op) {
        Node ans = *this;
        ans.ops.push_back(_op);
        int i;
        int j;
        switch (_op) {
            case 'A':
                for (i = 0; i < M; ++i) {
                    swap(ans.A[0][i], ans.A[1][i]);
                }
                break;
            case 'B':
                // B操作是列循环右移1位。
                for (i = 0; i < N; ++i) {
                    for (j = 0; j < M; ++j) {
                        ans.A[i][j] = j == 0 ? A[i][3] : A[i][j - 1];
                    }
                }
                break;
            case 'C':
                ans.A[0][1] = A[1][1];
                ans.A[0][2] = A[0][1];
                ans.A[1][2] = A[0][2];
                ans.A[1][1] = A[1][2];
                break;
            default: assert(false);
        }
        ans.hash = ans.ComputeHash();
        return ans;
    }
};

Node init = {{{1, 2, 3, 4}, {8, 7, 6, 5}}};
Node target;

#define MAXH (16777216 + 5)
/*
本题如果不用散列，用map会超时，
但是用散列，如果散列表空间太大，会超内存。
所以：
1. 散列表元素为bool，仅实现判断是否入队的功能。
2. 准确估计数组大小，用8位8进制数的最大值，即8的8次方。

这样一来就无法保存Node了，从而就无法保存前驱指针，
但是仔细一想，可以直接把操作序列保存在Node，而不会占很大空间。
*/

bool inq[MAXH];

const char Ops[] = "ABC";

void BFS() {
    queue<Node> q;
    q.push(init);
    inq[init.Hash()] = true;

    while (!q.empty()) {
        Node p = q.front();
        q.pop();

        if (p == target) {
            string& ops = p.ops;
            printf("%d\n", ops.size());
            for (int i = 0; i < ops.size(); ++i) {
                printf("%c", ops[i]);
                if ((i + 1) % 60 == 0 || i == ops.size() - 1) { printf("\n"); }
            }
            return;
        }

        for (int i = 0; i < 3; ++i) {
            char op = Ops[i];
            Node v = p.Next(op);
            if (!inq[v.Hash()]) {
                inq[v.Hash()] = true;
                q.push(v);
            }
        }
    }
    assert(false);  // 题目保证有解。
}

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

void Clear() {
    memset(inq, 0, sizeof(inq));
}

int main(int argc, char** argv) {
#ifndef ONLINE_JUDGE
    freopen("./in.txt", "r", stdin);
#endif
    init.hash = init.ComputeHash();

    while (target.Read() != EOF) {
        Clear();
        BFS();
    }

    return 0;
}
