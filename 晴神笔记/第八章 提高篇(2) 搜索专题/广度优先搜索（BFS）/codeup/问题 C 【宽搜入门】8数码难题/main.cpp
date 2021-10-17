#include <cassert>
#include <cstdio>
#include <map>
#include <queue>
using namespace std;

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

const int N = 3;

/*
对当前的空格元素作上下左右移动（如果可以），
按照BFS的顺序去遍历这些状态，并且记录步数。
*/

struct Node {
    int A[N][N];
    int step;  // 最少需要几步到达此状态。
    int x, y;  // 0 的位置。
               //	int pre; // 前一个节点。

    bool operator==(const Node& p) {
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                if (A[i][j] != p.A[i][j]) return false;
            }
        }
        return true;
    }

    int Hash() {
        int ans = 0;
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                ans = ans * 10 + A[i][j];
            }
        }
        return ans;
    }

    void Read() {
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                scanf("%d", &A[i][j]);
                if (A[i][j] == 0) {
                    x = i;
                    y = j;
                }
            }
        }
    }
    void Print() {
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                printf("%d ", A[i][j]);
            }
            putchar('\n');
        }
    }
};

map<int, Node> inq;
Node target, init;
const int X[] = {0, 0, -1, 1};
const int Y[] = {-1, 1, 0, 0};

int BFS() {
    queue<int> q;
    init.step = 1;
    //	init.pre=-1;
    q.push(init.Hash());
    inq[init.Hash()] = init;

    while (!q.empty()) {
        int h = q.front();
        Node p = inq[h];

        q.pop();
        if (p == target) {
            // 打印路径。
            //			do {
            //				p.Print();
            //				printf("\n");
            //				p=inq[p.pre];
            //			} while (p.pre != -1);
            return p.step;
        }

        for (int i = 0; i < 4; ++i) {
            Node v = p;
            v.x += X[i];
            v.y += Y[i];
            if (0 <= v.x && v.x < N && 0 <= v.y && v.y < N) {
                assert(v.A[v.x][v.y] != 0);
                assert(v.A[p.x][p.y] == 0);

                swap(v.A[v.x][v.y], v.A[p.x][p.y]);
                if (inq.find(v.Hash()) == inq.end()) {
                    v.step = p.step + 1;
                    //					v.pre=p.Hash();
                    inq[v.Hash()] = v;
                    q.push(v.Hash());
                }
            }
        }
    }
    return -1;
}

int main(int argc, char** argv) {
#ifndef ONLINE_JUDGE
    freopen("./in.txt", "r", stdin);
#endif

    init.Read();
    target.Read();
    int ans = BFS();
    printf("%d\n", ans);

    return 0;
}
