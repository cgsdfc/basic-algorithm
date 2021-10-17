#include <algorithm>
#include <cstdio>
#include <map>
using namespace std;

/*
����һ����������������࣬�����󣬲���ǰ��������ȱ������Ľڵ㣬
�Լ�ǰ���������š�

ǰ������������֧����������Ľڵ㡣ע�⣬����ǴӸ��ڵ�����ģ��߶��Ǵ�
Ҷ�ӽڵ�����ģ����ڵ�߶�������Ϊ0��Ҷ�������󣬸߶�Ϊ0.

����Ľڵ�id��������������-1��ʾû�к��ӡ�
*/

int N;  // ������ע�ⲻ�����нڵ㶼���Լ���һ�У����Խڵ������Ϊ 4*N ��

const int MAXN = 1e4 + 5;
const int MAXV = 4 * MAXN;  // �ڵ�����

const int MAXC = 3;  // ��������

struct Node {
    int data;  // ��������֡�
    int fa;    // �Ҹ���
    int child[MAXC];
    int num;  // ���Ӹ�����

    Node() {
        fa = -1;
        num = 0;
        fill(child, child + MAXC, -1);
    }
} node[MAXV];

int index;

map<int, int> mp;
bool IsCh[MAXV];

int Map(int data) {
    if (mp.count(data)) {
        return mp[data];
    } else {
        mp[data] = index;
        node[index].data = data;
        return index++;
    }
}

struct State {
    // ��Ӧ�ڵ㡣
    int v;
    int index;  // �������������š�
    // ��ǰ��Ⱥͺ�������
    int depth;
    int num;

    State(int vv, int ii, int dd, int nn): v(vv), index(ii), depth(dd), num(nn) {}
    friend bool operator<(State& a, State& b) {
        if (a.num != b.num) return a.num < b.num;
        return a.depth < b.depth;
    }
};

int PreOrderIndex = 1;

void DFS(int v, int depth, State& maxS) {
    // ���������
    State now(v, PreOrderIndex, depth, node[v].num);
    ++PreOrderIndex;
    if (maxS < now) { maxS = now; }
    for (int i = 0; i < MAXC; ++i) {
        int u = node[v].child[i];
        if (u != -1) { DFS(u, depth + 1, maxS); }
    }
}

int FindRoot() {
    // ��Ŀû˵���ڵ���һ��ʼ������
    for (int i = 0; i < index; ++i) {
        if (-1 == node[i].fa) { return i; }
    }
    return -1;
}

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

int main(int argc, char** argv) {
    scanf("%d", &N);
    while (N--) {
        int u;
        scanf("%d", &u);
        u = Map(u);
        for (int i = 0; i < MAXC; ++i) {
            int v;
            scanf("%d", &v);
            if (v != -1) {
                v = Map(v);
                node[u].child[i] = v;
                node[u].num++;
                node[v].fa = u;
            }
        }
    }
    int root = FindRoot();
    State maxS(-1, -1, -1, -1);
    DFS(root, 0, maxS);
    printf("%d %d", node[maxS.v].data, maxS.index);

    return 0;
}
