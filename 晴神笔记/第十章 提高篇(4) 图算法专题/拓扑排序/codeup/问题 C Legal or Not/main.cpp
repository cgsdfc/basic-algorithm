#include <algorithm>
#include <cstdio>
#include <queue>
using namespace std;

/*
����ͼ�л������ַ�����
1. ���������л���
2. DFS�л���������Ҳ����������
*/

int N, M;
#define MAXN 105

bool G[MAXN][MAXN];
int In[MAXN];

bool TopoSort() {
    queue<int> Q;
    for (int v = 0; v < N; ++v) {
        if (!In[v]) { Q.push(v); }
    }
    int num = 0;
    while (!Q.empty()) {
        int u = Q.front();
        Q.pop();
        ++num;
        for (int v = 0; v < N; ++v) {
            if (G[u][v]) {
                --In[v];
                if (!In[v]) { Q.push(v); }
            }
        }
    }
    return N == num;
}

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

int main(int argc, char** argv) {
    while (scanf("%d%d", &N, &M), N) {
        fill(G[0], G[0] + MAXN * MAXN, false);
        fill(In, In + MAXN, 0);
        while (M--) {
            int a, b;
            scanf("%d%d", &a, &b);  // ����һ���� a->b
            /*
            ע�⣬�ڽӾ�����رߵĴ����³���
            ��ʵ���ڽӾ����ǲ�֧���رߵģ���ΪG[a][b]ֻ��һ��Ԫ�أ����ұ���a���ھ�ʱ��
            ��ȫ���ڵ�ÿ��ֻ����һ�Σ��൱�ڰ��ر߸�ȥ���ˣ�ֻ������һ���ߣ���
            �����Ŀ������ر�û�б������ڽӾ����У����ǻ������In���������ͼ����ȾͲ�һ���ˣ��ͳ����ˡ�

            ���ڽӱ��û��������⣬��Ϊ�����رߣ�u->v����u��������ᱣ�����v�ĸ���������u���ھ�ʱ��
            v�����ʶ�Σ���ʹv�������Ӧ�ļ��ٶ�Σ����ͼ�����һ�£�û�����⡣

            �����Ҫʹ���ڽӾ��󣬾ͱ���������ʱ����رߣ�������Ƚ��д���������˵���ر߱���һ�����ɣ�����
            �������ҲҪȥ�ء������ڽӾ�����Կ��ٲ�ѯĳ���Ƿ���ڣ������������Ҳ�ܿ졣

            codeup��Щ��Ŀ���رߣ����뿼���ڽӱ���ڽӾ��������Ȼ����ȷ����
            */
            if (!G[a][b]) {
                // ���ڱ�ab��ֻ���һ�Ρ�
                G[a][b] = true;
                ++In[b];
            }
        }
        bool ans = TopoSort();
        puts(ans ? "YES" : "NO");
    }

    return 0;
}
