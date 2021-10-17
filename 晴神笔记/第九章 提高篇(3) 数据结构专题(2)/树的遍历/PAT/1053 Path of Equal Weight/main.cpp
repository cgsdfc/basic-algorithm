#include <algorithm>
#include <cstdio>
#include <vector>  // ������ر�
using namespace std;

#define MAXN 105

struct Node {
    int weight;         // ��Ȩ��
    vector<int> child;  // ���ݼ����С�
} node[MAXN];

/*
ע�������ǰ��սڵ�a��Ȩ�ش����ȫ�棬
���ȿ���Ȩ�ش���ӽڵ㡣
*/
bool cmp(int a, int b) {
    return node[a].weight > node[b].weight;
}

struct {
    int data[MAXN];
    int len;
} ans;

const int Root = 0;
int S;  // Ŀ��͡�
int N, M;

/*
�˺��������ϱ��������еĸ���Ҷ�ӵ�·����
����Ϊģ�塣
*/
void DFS(int root, int nowS) {
    /*
    ���ǵ�ǰ�ڵ㡣
    */
    nowS += node[root].weight;
    // ע���������Ȩ�ء�
    ans.data[ans.len++] = node[root].weight;

    // �������������������ֻ�������ӽڵ㡣
    if (node[root].child.empty()) {
        // �ݹ�߽硣
        if (nowS == S) {
            // �õ�һ���⡣
            for (int i = 0; i < ans.len; ++i) {
                printf("%d%s", ans.data[i], i == ans.len - 1 ? "\n" : " ");
            }
        }
    } else {
        for (int i = 0; i < node[root].child.size(); ++i) {
            int p = node[root].child[i];
            DFS(p, nowS);
        }
    }
    ans.len--;
}

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

int main(int argc, char** argv) {
    scanf("%d%d%d", &N, &M, &S);
    for (int i = 0; i < N; ++i) {
        scanf("%d", &node[i].weight);
    }
    for (int i = 0; i < M; ++i) {
        int id, k;
        scanf("%d%d", &id, &k);
        while (k--) {
            int c;
            scanf("%d", &c);
            node[id].child.push_back(c);
        }
        sort(node[id].child.begin(), node[id].child.end(), cmp);
    }
    DFS(Root, 0);

    return 0;
}
