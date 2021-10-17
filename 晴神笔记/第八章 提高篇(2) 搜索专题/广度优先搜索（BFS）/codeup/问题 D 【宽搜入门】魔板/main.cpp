#include <cassert>
#include <cstdio>
#include <cstring>
#include <queue>
#include <string>  // op����������ġ�
using namespace std;

const int N = 2;
const int M = 4;

struct Node {
    int A[2][4];
    string ops;  // �õ��˽ڵ�Ĳ������С�
    int hash;

    bool operator==(const Node& p) {
        return hash == p.hash;
    }
    int ComputeHash() {
        int ans = 0;
        // ע��ҪתΪ8��������
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
                // B��������ѭ������1λ��
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
�����������ɢ�У���map�ᳬʱ��
������ɢ�У����ɢ�б�ռ�̫�󣬻ᳬ�ڴ档
���ԣ�
1. ɢ�б�Ԫ��Ϊbool����ʵ���ж��Ƿ���ӵĹ��ܡ�
2. ׼ȷ���������С����8λ8�����������ֵ����8��8�η���

����һ�����޷�����Node�ˣ��Ӷ����޷�����ǰ��ָ�룬
������ϸһ�룬����ֱ�ӰѲ������б�����Node��������ռ�ܴ�ռ䡣
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
    assert(false);  // ��Ŀ��֤�н⡣
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
