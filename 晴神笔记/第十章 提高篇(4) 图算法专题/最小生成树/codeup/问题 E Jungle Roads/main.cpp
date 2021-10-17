#include <algorithm>
#include <iostream>  // ��cin�����ַ��ȽϷ��㡣
using namespace std;

/*
�ߺ͵㶼���٣������㷨���ѡһ����
*/

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

int N;

#define MAXN 30
#define MAXM 100

int change(char v) {
    return v - 'A';
}

struct Edge {
    int u, v, cost;
    Edge() {}
    Edge(int uu, int vv, int cc): u(uu), v(vv), cost(cc) {}
    friend bool operator<(const Edge& a, const Edge& b) {
        return a.cost < b.cost;
    }
};

Edge E[MAXM];
int M;             // ������
int father[MAXN];  // ���鼯��

int Find(int x) {
    int a = x;
    while (x != father[x]) {
        x = father[x];
    }
    while (a != father[a]) {
        int temp = father[a];
        father[a] = x;
        a = temp;
    }
    return x;
}

// ��֤��ͨ��
int Kruskal() {
    for (int i = 0; i < N; ++i) {
        father[i] = i;
    }
    int ans = 0;
    int num = 0;
    sort(E, E + M);
    for (int i = 0; i < M; ++i) {
        int faU = Find(E[i].u);
        int faV = Find(E[i].v);
        if (faU != faV) {
            father[faU] = faV;
            ++num;
            ans += E[i].cost;
            if (num == N - 1) { break; }
        }
    }
    return ans;
}

int main(int argc, char** argv) {
    cin.sync_with_stdio(false);
    while (cin >> N, N) {
        M = 0;
        for (int i = 0; i < N - 1; ++i) {
            char u;
            int k;
            cin >> u >> k;
            while (k--) {
                char v;
                int cost;
                cin >> v >> cost;
                E[M++] = Edge(change(u), change(v), cost);
            }
        }
        int ans = Kruskal();
        printf("%d\n", ans);
    }
    return 0;
}
