#include <algorithm>
#include <cassert>
#include <cstdio>
using namespace std;

#define MAXN 105

int N;
int G[MAXN][MAXN];
const int INF = 1e9;
bool vis[MAXN];
int d[MAXN];

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

/*
Ҫ�󱣳�ͼ����ͨ�ԣ��ұ�Ȩ����С����ͼ��
ֵ��ע����ǣ����и�Ȩ��ͼ���ⲻ��������С����������Ϊ��Ȩ��Խ��Խ�ã����Ǹ�Ȩ��Խ��Խ�õģ�
��ǡ��Υ������������ʹ��ͼ������ͨ�ı����ٵ���ͼ��
������һ����Ȩ�ߣ�ɾ�����߱���������Ӱ����ͨ�ԣ����Ǽ��������߻�ʹ��Ȩ�͸�С������Ҫ��������
��ʹΥ���������ʡ�

��������֪����С���������⣬ʵ���ϵȼ�����Ǹ���Ȩͼ�ı���ͼ����ͨ�Եı�Ȩ����С����ͼ��
���ǲ��ȼ�����һ��ͼ�ı�����ͨ�Եı�Ȩ����С����ͼ����Ϊ���ߵĽṹ��������
*/

/*
�����ͼ����ȫͼ��������ͼ���ʺ�Prim���������٣��ʺ��ڽӾ���
��֤Ϊ��ͨͼ������Ҫ��⡣
*/

int Prim(int s) {
    fill(vis, vis + MAXN, false);
    fill(d, d + MAXN, INF);
    d[s] = 0;
    int ans = 0;
    for (int i = 0; i < N; ++i) {
        int u = -1;
        int MIN = INF;
        for (int j = 1; j <= N; ++j) {
            if (!vis[j] && d[j] < MIN) {
                MIN = d[j];
                u = j;
            }
        }
        assert(u != -1);
        vis[u] = true;
        ans += d[u];
        for (int j = 1; j <= N; ++j) {
            if (!vis[j] && G[u][j] != INF && G[u][j] < d[j]) { d[j] = G[u][j]; }
        }
    }
    return ans;
}

int main(int argc, char** argv) {
    while (scanf("%d", &N), N) {
        int M = N * (N - 1) / 2;
        fill(G[0], G[0] + MAXN * MAXN, INF);
        while (M--) {
            int u, v, d;
            scanf("%d%d%d", &u, &v, &d);
            G[u][v] = G[v][u] = d;
        }
        int ans = Prim(1);
        printf("%d\n", ans);
    }

    return 0;
}
