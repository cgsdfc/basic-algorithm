#include <algorithm>
#include <cassert>
#include <cstdio>
#include <map>
#include <set>
#include <vector>
using namespace std;

const int INF = 1000000000;

#define MAXN (10000 + 5)
int N;
vector<int> Adj[MAXN];
bool vis[MAXN];
// ��������Ľڵ�ԵĶ˵㡣
set<int> Ans;

void DFS(int u, int depth, int& hi) {
    vis[u] = true;
    if (depth > hi) { hi = depth; }
    for (int i = 0; i < Adj[u].size(); ++i) {
        int v = Adj[u][i];
        if (!vis[v]) { DFS(v, depth + 1, hi); }
    }
}

int TreeHi(int root) {
    // ����rootΪ�������ĸ߶ȡ�
    int ans = 0;
    fill(vis, vis + N + 1, false);
    DFS(root, 0, ans);
    return ans;
}

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

int father[MAXN];  // ���鼯�����ͨ�ԡ�
void Init() {
    for (int i = 1; i <= N; ++i) {
        father[i] = i;
    }
}
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
void Union(int a, int b) {
    int faA = Find(a);
    int faB = Find(b);

    if (faA != faB) { father[faA] = faB; }
}
void Print() {
    for (int i = 1; i <= N; ++i) {
        printf("%d: ", i);
        for (int j = 0; j < Adj[i].size(); ++j) {
            printf("%d ", Adj[i][j]);
        }
        printf("\n");
    }
}

// ��ͨ��������
int FindComp() {
    int ans = 0;
    for (int i = 1; i <= N; ++i) {
        // ����N���ڵ㣬�Ǹ��Ǹ���
        if (father[i] == i) { ++ans; }
    }
    assert(ans > 0);
    return ans;
}

/*
���O(VE+V^2)���㷨��Ȼ���ˣ�˵��PAT�Ĳ������ݱȽ�����
*/

/*
�ж���ӳֵĸ�Ч�㷨��
1. ѡ������ڵ���Ϊ��������DFS����ȡ������Ľڵ㼯�ϣ���ΪA��
2. ��ȡA��һ��Ԫ�أ��Դ�Ϊ��������DFS����������Ľڵ㼯�ϣ���ΪB��
3. �����������ڵ㼯�ϼ�Ϊ A �� B��

���Ӷȣ�O(V+E)����DFS�ĸ��Ӷȡ�
*/

/*
��ĳ���ڵ����DFS��������¼������Ľڵ㣬��¼��vi�С�
һ���������ȣ�һ��ͳ��������ĵ㣬�м��ɡ�
*/
void DFS2(int u, int depth, int& maxDepth, vector<int>& vi) {
    vis[u] = true;
    //	printf("u %d maxd %d\n", u, maxDepth);

    if (depth > maxDepth) {
        // ע�����ȫ�����ֵ��
        maxDepth = depth;
        vi.clear();
        vi.push_back(u);  // u����ȴﵽ�¸ߡ�
    } else if (depth == maxDepth) {
        // �ﵽ��ǰ�����ȡ�
        vi.push_back(u);
    }
    for (int i = 0; i < Adj[u].size(); ++i) {
        int v = Adj[u][i];
        if (!vis[v]) { DFS2(v, depth + 1, maxDepth, vi); }
    }
}

// ��ĳ�ڵ�Ϊ��������Ҷ�ڵ㼯�ϡ�
// ����ĳ�ڵ�Ϊ�����������Ϊ���ߵ�Ҷ�ڵ㼯�ϡ�
void FindDeep(int root, vector<int>& vi) {
    int deep = 0;
    fill(vis, vis + N + 1, false);
    DFS2(root, 0, deep, vi);
}

/*
�����������Deepest Roots�����ϡ�
ʹ�ö���İ汾��
*/
void Compute2() {
    vector<int> A, B;
    // ���㼯��A����ĳ�ڵ����������ڵ㼯�ϡ�
    FindDeep(1, A);

    assert(A.size());
    // ���㼯��B����A��ĳԪ�س���������ڵ㼯�ϡ�
    FindDeep(A.front(), B);

    // ����AB�Ĳ�����
    set<int> ans;
    vector<int>::iterator it;
    for (it = A.begin(); it != A.end(); ++it) {
        //		printf("%d\n", *it);
        ans.insert(*it);
    }
    //	puts("");
    for (it = B.begin(); it != B.end(); ++it) {
        //		printf("%d\n", *it);
        ans.insert(*it);
    }
    // ans ��Ϊ������ڵ㼯�ϣ���������
    for (set<int>::iterator it = ans.begin(); it != ans.end(); ++it) {
        printf("%d\n", *it);
    }
}

/*
�����汾��
*/
void Compute() {
    int ans = -1;
    for (int v = 1; v <= N; ++v) {
        // ������vΪ�������ߡ�
        int hi = TreeHi(v);
        // ����ȫ�����ֵ��
        if (hi > ans) {
            ans = hi;
            Ans.clear();
            Ans.insert(v);
        } else if (hi == ans) {
            Ans.insert(v);
        }
    }

    set<int>::iterator it;
    // ��С���������
    for (it = Ans.begin(); it != Ans.end(); ++it) {
        printf("%d\n", *it);
    }
}

int main(int argc, char** argv) {
    scanf("%d", &N);
    int M = N - 1;
    /*
    ע�⣬����һ����������E=V-1�Ѿ����㣬ֻ��Ҫ�����ͨ���Ƿ����㡣
    ��Ϊ��ͨ��E=V-1�ıض����������ü�黷�ˡ�
    */
    Init();  // ���鼯��ʼ����
    while (M--) {
        int a, b;
        scanf("%d%d", &a, &b);
        Adj[a].push_back(b);
        Adj[b].push_back(a);
        // ����ͼ��
        Union(a, b);
    }
    // �ò��鼯���Կ��ټ����ͨ�ԡ�
    int n = FindComp();
    if (n != 1) {
        // ������ͨͼ����������
        printf("Error: %d components\n", n);
    } else {
        Compute2();
    }
    return 0;
}
