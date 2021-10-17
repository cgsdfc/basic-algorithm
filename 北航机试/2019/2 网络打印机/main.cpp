#include <algorithm>
#include <cassert>
#include <cstdio>
#include <vector>
using namespace std;

/*
��ǰ���������Ϊÿ���ڵ����ţ�Ȼ��DFS�����·����ʵ���Ǽ�·������
����·����̺�ǰ�������С��ԭ����£�ͬʱ��¼·����
���Ӷ��Ǳ���ͼ����O(V+E)��

�����ӡ���ı�ź͵��Ե���ӡ����·����
*/

// �����ͣ�0��ʾ��������1��ʾ�������2��ʾ��ӡ����
enum {
    SW,
    COM,
    PRI,
};

#define MAXP 10  // �˿ں�

struct Node {
    int type;
    int ord;  // ǰ����š�
    int fa;
    int child[MAXP];

    Node() {
        fa = -1;
        fill(child, child + MAXP, -1);
    }
};

#define MAXN 505

Node node[MAXN];
bool vis[MAXN];
int N;  // �ڵ���1--N��0��ʾû�и��ڵ㡣

void PreOrder(int root, int& index) {
    if (root != -1) {
        node[root].ord = index++;
        for (int i = 0; i < MAXP; ++i) {
            PreOrder(node[root].child[i], index);
        }
    }
}

vector<int> Path, tempPath;

// ��Դ������ҵ�ÿһ̨��ӡ����
void DFS(int v) {
    vis[v] = true;
    tempPath.push_back(v);
    if (node[v].type == PRI) {
        // �ҵ�һ̨��ӡ����
        if (Path.empty() || (tempPath.size() < Path.size()) ||
            (tempPath.size() == Path.size() && node[v].ord < node[Path.back()].ord)) {
            Path = tempPath;  // ע�����������
        }
    } else {
        // ��Ϊ������ͼ���Ӹ��ڵ�ͺ��ӽڵ����������
        int u = node[v].fa;
        if (u != -1 && !vis[u]) { DFS(u); }
        for (int i = 0; i < MAXP; ++i) {
            int u = node[v].child[i];
            if (u != -1 && !vis[u]) { DFS(u); }
        }
    }
    vis[v] = false;
    tempPath.pop_back();
}

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */
int Root;
int S;  // Դ�㡣

int main(int argc, char** argv) {
    scanf("%d", &N);
    fill(node, node + MAXN, Node());
    fill(vis, vis + MAXN, false);

    for (int i = 0; i < N; ++i) {
        int id, type, fa, port;
        // ע�⣬�˿ں������������ӽڵ�����ġ�
        scanf("%d%d%d%d", &id, &type, &fa, &port);
        node[id].type = type;
        if (!fa) {
            Root = id;
        } else {
            node[id].fa = fa;
            node[fa].child[port] = id;
        }
    }
    scanf("%d", &S);
    int index = 0;
    PreOrder(Root, index);
    DFS(S);
    int v = Path.back();  // ��ӡ���ı�š�
    assert(node[v].type == PRI);
    printf("%d\n", v);

    for (int i = 0; i < Path.size(); ++i) {
        printf("%d%s", Path[i], i == Path.size() - 1 ? "\n" : " ");
    }

    return 0;
}
