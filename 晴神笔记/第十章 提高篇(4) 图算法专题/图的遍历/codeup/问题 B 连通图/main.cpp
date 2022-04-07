#include <cstdio>
#include <queue>
#include <vector>
using namespace std;

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

int N, M;

/*
���������һ��BFS������нڵ�ķ��ʣ���ͼ������ͨ�ġ�
��bfs�ж�ͼ����ͨ�ԡ�
*/

#define MAXN 1005

bool inq[MAXN];
vector<int> Adj[MAXN];

int BFS(int s) {
    int ans = 0;  // ���η��ʵĽڵ�������
    queue<int> Q;
    Q.push(s);
    inq[s] = true;
    while (!Q.empty()) {
        // bfs���ʵĽ�㶼Ҫ�������
        ++ans;
        int v = Q.front();
        Q.pop();
        for (int i = 0; i < Adj[v].size(); ++i) {
            int u = Adj[v][i];
            if (!inq[u]) {
                inq[u] = true;
                Q.push(u);
            }
        }
    }
    return ans;
}

bool Judge() {
    // ���߿��Կ�һ��bfs�ܷ��inqȫ����Ϊtrue��
    fill(inq, inq + N + 1, false);
    int n = BFS(1);
    return n == N;
}

int main(int argc, char** argv) {
    while (scanf("%d", &N), N) {
        scanf("%d", &M);

        while (M--) {
            int x, y;
            scanf("%d%d", &x, &y);
            // ����ͼ��
            Adj[x].push_back(y);
            Adj[y].push_back(x);
        }
        bool ans = Judge();
        puts(ans ? "YES" : "NO");
        for (int i = 1; i <= N; ++i) {
            Adj[i].clear();
        }
    }

    return 0;
}
