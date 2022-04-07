#include <algorithm>
#include <cassert>
#include <cstdio>

using namespace std;

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

/*
����һ����ͨ����ͼ��ɾȥ����һ���㣬����Ҫ�Ӷ��ٱ߲���ʹ��ʣ�µĵ�������ͨͼ��
ֻ�м���ɾ����ͼ�ж�����ͨ�������ɣ���ΪC�������ӱ���E=C-1.
��ʹC���ڵ���ͨ����С����ΪC-1��
*/

/*
��ΪҪ֧�ֿ���ɾ�ߺͼӱߣ�����N�������ڽӾ��󼴿ɡ�
ɾ����һ��hash�����ʾĳ�㱻ɾ�ˡ�
*/

int N, M, K;  // �ڵ�����������ɾ������

#define MAXN 1005  // �ڵ��±�1--N��

bool G[MAXN][MAXN];
bool vis[MAXN];  // DFS�ر���
// bool Del[MAXN];
int Del;

// ����ͨ������DFS���ɡ�

void DFS(int u) {
    vis[u] = true;
    for (int v = 1; v <= N; ++v) {
        if (!vis[v] && G[u][v] && v != Del) { DFS(v); }
    }
}

// ɾ��Q�㣬������Ҫ��ӵı�����
int DFSTrave() {
    int ans = 0;  // ��ͨ��������
    // BUG�㣺
    // ע���±�1-N��fill��Ӱ�죡
    // ʵ����Ҫ��[1--N]����Ϊfalse.
    fill(vis + 1, vis + N + 1, false);

    for (int v = 1; v <= N; ++v) {
        if (!vis[v] && v != Del) {
            // �Ȳ��������㣬Ҳ���ظ����ʡ�
            ++ans; // ͳ����ͨ����������
            DFS(v);
        }
    }
    assert(ans >= 0);
    return ans - 1;
}

/*
ʱ�临�Ӷȣ�ɾ��K�Σ�ÿ�α���ȫͼ����
O(KV)
*/

int main(int argc, char** argv) {
    scanf("%d%d%d", &N, &M, &K);
    while (M--) {
        int i, j;
        scanf("%d%d", &i, &j);
        G[i][j] = G[j][i] = true;
    }
    while (K--) {
        // ��ѯ��ÿ��ֻɾ��һ���㡣
        scanf("%d", &Del);
        int ans = DFSTrave();
        printf("%d\n", ans);
    }
    return 0;
}
