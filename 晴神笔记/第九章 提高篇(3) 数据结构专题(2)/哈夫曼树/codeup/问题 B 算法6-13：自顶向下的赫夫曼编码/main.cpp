#include <cassert>
#include <climits>
#include <cstdio>
#include <queue>
#include <string>
using namespace std;

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

// ��Ҷ�ӽڵ�����
#define MAXN 105
// �����������ܽڵ���������Ҷ�ӽڵ���ȷ����
#define MAXV (2 * MAXN - 1)

struct Node {
    int lchild, rchild;  // �Զ�������Ҫ��¼����ָ�롣
    int weight;          // Ȩ�ء�
    /*
    ��Ŀ�����㷨��û���öѣ����Ե�������ͬ��Ȩ��ʱ��
    ������ѡ�������������濼ǰ��Ԫ�أ�Ҳ����������ɨ����
    ����Сֵ���������ö�ģ�⣬���뻹ԭ�������ȼ�������
    �õ�һ���Ĵ𰸡�
    */
    int id;
} node[MAXV];

// ���� 0--N-1 �����ڵ�ı��롣
string code[MAXN];

int index = 0;

int NewNode() {
    return index++;
}

struct cmp {
    // ע�⣺��ͬ��Ȩ�أ�idС���ȳ��֣���ΪҪģ������ɨ������ԡ�
    bool operator()(int a, int b) {
        // weight С���ȳ��ӡ�
        if (node[a].weight != node[b].weight) { return node[a].weight > node[b].weight; }
        // idС���ȳ��ӡ�
        return node[a].id > node[b].id;
    }
};

// �����������������ظ��ڵ㡣
int Build(int N) {
    // ע�����������ر�С���ѣ���greater��
    priority_queue<int, vector<int>, cmp> Q;
    // ����N��Ȩ�أ�������Ҷ�ӽڵ㡣
    int id = 0;
    while (N--) {
        int w;
        scanf("%d", &w);
        int p = NewNode();
        node[p].weight = w;
        node[p].lchild = node[p].rchild = -1;  // һ��ʼ���Ǹ��ڵ㣬Ҳ��Ҷ�ڵ㡣
        node[p].id = id++;
        Q.push(p);
    }
    // �����ɵĽڵ㣬��idҪ������š�
    while (Q.size() > 1) {
        int a = Q.top();
        Q.pop();
        int b = Q.top();
        Q.pop();
        /*
        ע�⣬������СԪ����id��˳����֡�
        */
        if (node[a].id > node[b].id) { swap(a, b); }

        //		printf("%d %d\n", node[a].weight, node[b].weight);

        int root = NewNode();
        node[root].weight = node[a].weight + node[b].weight;
        node[root].id = id++;
        node[root].lchild = a;
        node[root].rchild = b;
        Q.push(root);
    }
    return Q.top();
}

void PopBack(string& s) {
    s.erase(s.end() - 1);
}

// �������˹��������Ļ����ϣ����Զ����µķ������ɱ��롣
// ��������˳����ϴ�һ�����ǴӸ���Ҷ�ӵ�·����˳��
void DFS(int root, string& now) {
    if (root == -1) return;
    if (node[root].lchild != -1) {
        // �����������ӡ�
        assert(node[root].rchild != -1);

        now.push_back('0');
        DFS(node[root].lchild, now);
        /*
        string.pop_back �� C++11 ���ԡ�
        */
        PopBack(now);
        //		now.pop_back();

        now.push_back('1');
        DFS(node[root].rchild, now);
        //		now.pop_back();
        PopBack(now);
    } else {
        // Ҷ�ӣ������code����ΪDFS���ɱ����˳���Ҷ�ӽڵ������˳��һ�£�
        // �����ȱ����������
        code[root] = now;
    }
}

/*
���ɹ��������롣
ע�⣺
1. �������Ľڵ�Ȩ�ش󣬿���Ҷ�ӵĽڵ�Ȩ��С����ˣ�
Ҫ��С���ѣ�ÿ��ѡ��Ȩ����С�������ڵ���кϲ���
*/
int main(int argc, char** argv) {
    int N;
    while (scanf("%d", &N) != EOF) {
        index = 0;
        int root = Build(N);
        // ע�⣬0--N-1��Ҷ�ӡ�
        string str;
        DFS(root, str);
        for (int i = 0; i < N; ++i) {
            puts(code[i].c_str());
        }
    }
    return 0;
}
