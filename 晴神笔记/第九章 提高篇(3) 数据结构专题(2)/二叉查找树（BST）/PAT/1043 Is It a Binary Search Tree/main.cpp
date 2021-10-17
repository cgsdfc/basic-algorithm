#include <iostream>

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

/*
�������������Ƿ�ΪBST���߷�תBST������
����������������
���ҵ�����Ȼ��ȸ�С������Ԫ�������������������ĺ�������������
��������������ڵ��ڸ���
*/

#define MAXN 1005

struct Node {
    int data;
    int lchild, rchild;
};

Node node[MAXN];
int pre[MAXN];
int index;
bool ans;  // �Ƿ�ɹ���
int N;

int newNode(int v) {
    node[index].data = v;
    node[index].lchild = node[index].rchild = -1;
    return index++;
}

int Create(int preL, int preR, bool (*cmp)(int, int)) {
    if (!ans || preL > preR) {
        // �Ѿ���鲻�ɹ��ˡ�
        return -1;
    }

    int x = pre[preL];  // ����
    int root = newNode(x);

    int k = preL + 1;
    // ǰ���Ӧ������cmp
    while (cmp(pre[k], x) && k <= preR) {
        ++k;
    }
    // �������Ƿ�����!cmp.
    int j = k;
    while (j <= preR) {
        if (cmp(pre[j], x)) {
            ans = false;
            return -1;
        }
        ++j;
    }
    node[root].lchild = Create(preL + 1, k - 1, cmp);
    node[root].rchild = Create(k, preR, cmp);
    return root;
}

// ������������
void Print(int root, int& i) {
    if (root != -1) {
        Print(node[root].lchild, i);
        Print(node[root].rchild, i);
        printf("%d%s", node[root].data, i == N - 1 ? "\n" : " ");
        ++i;
    }
}

// ������������
bool Less(int a, int b) {
    return a < b;
}
// ��ת�������İ汾��
bool NotLess(int a, int b) {
    return !Less(a, b);
}

int main(int argc, char** argv) {
    scanf("%d", &N);
    for (int i = 0; i < N; ++i) {
        scanf("%d", &pre[i]);
    }

    ans = true;
    int root = Create(0, N - 1, Less);
    if (!ans) {
        index = 0;  // ���·��䣬���򲻹��á�
        ans = true;
        root = Create(0, N - 1, NotLess);
    }
    if (ans) {
        puts("YES");
        int i = 0;
        Print(root, i);
    } else {
        puts("NO");
    }
    return 0;
}
