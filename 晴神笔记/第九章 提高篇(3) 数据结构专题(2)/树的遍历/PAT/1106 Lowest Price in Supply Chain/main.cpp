#include <cassert>
#include <cmath>
#include <cstdio>
#include <queue>
#include <vector>
using namespace std;

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

/*
�������С��Ҷ�ӽڵ����ȡ�
��ΪBFS�Ĺ����У������������ģ������ҵ���һ��Ҷ�ӽڵ�
�Ϳ����˳��ˡ�

������ĿҪ�����Ϊ��С��Ҷ�ӵ����������Ҫ������нڵ������ˣ�
���Բ�����ǰ�˳���

*/
#define MAXN (100000 + 5)

struct Node {
    int deep;
    vector<int> child;
} node[MAXN];

const int root = 0;
int N;
double P, r;

int BFS() {
    queue<int> Q;
    Q.push(root);
    node[root].deep = 0;
    bool flag = true;
    int ans = 0;

    while (!Q.empty()) {
        int now = Q.front();
        Q.pop();
        if (flag && node[now].child.empty()) {
            // ��һ��Ҷ�ڵ�����ˣ���Ϊ��С��ȡ�
            ans = node[now].deep;
            flag = false;
        }
        for (int i = 0; i < node[now].child.size(); ++i) {
            int p = node[now].child[i];
            node[p].deep = node[now].deep + 1;
            Q.push(p);
        }
    }
    return ans;
}

int main(int argc, char** argv) {
    scanf("%d%lf%lf", &N, &P, &r);
    for (int i = 0; i < N; ++i) {
        int n;  // �ӽڵ�����
        scanf("%d", &n);
        while (n--) {
            int c;  // ���ӡ�
            scanf("%d", &c);
            node[i].child.push_back(c);
        }
    }
    // ������ɡ�
    int ans = BFS();
    double rate = P * pow(1 + r / 100, ans);
    int num = 0;
    /*
    ������������˵������ֱ����ȫ���ڵ�����������Ϊ�ܴﵽ�����ȵĽڵ㣬
    �ض���Ҷ�ڵ㡣���Ƕ�����С�����˵��������Ҷ�ڵ���������Ȼ������Ҷ�ڵ㡣
    */
    for (int i = 0; i < N; ++i) {
        if (node[i].child.empty() && node[i].deep == ans) { ++num; }
    }

    printf("%.4f %d\n", rate, num);

    return 0;
}
