#include <cassert>
#include <cstdio>
#include <cstring>
#include <stack>  // ����ģ�⡣
using namespace std;

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

/*
�۲췢�֣�
Push���о����������У�
Pop���о����������У�
���Ǿͽ�����Ȼ����������
*/

#define MAXN 35

int N;  // �ڵ�������
int pre[MAXN], in[MAXN];
int preLen, inLen;

struct Node {
    int data;
    Node* lchild;
    Node* rchild;
    Node(int v) {
        data = v;
        lchild = rchild = NULL;
    }
};

Node* Create(int inL, int inR, int preL, int preR) {
    if (inL > inR) { return NULL; }
    Node* root = new Node(pre[preL]);
    int k;
    for (k = inL; k <= inR; ++k) {
        if (in[k] == root->data) { break; }
    }
    // k��λ���Ǹ���
    int numL = k - inL;
    root->lchild = Create(inL, k - 1, preL + 1, preL + numL);
    root->rchild = Create(k + 1, inR, preL + numL + 1, preR);
    return root;
}

int i;
void PostOrder(Node* root) {
    if (root) {
        PostOrder(root->lchild);
        PostOrder(root->rchild);
        printf("%d%s", root->data, i == N - 1 ? "\n" : " ");
        ++i;
    }
}

int main(int argc, char** argv) {
    scanf("%d", &N);
    char str[10];  // ����ָ�
    stack<int> s;
    int M = 2 * N;

    while (M--) {
        scanf("%s", str);
        if (!strcmp(str, "Push")) {
            int x;
            scanf("%d", &x);
            pre[preLen++] = x;
            s.push(x);
        } else {
            // Pop
            int x;
            assert(!s.empty());
            assert(!strcmp(str, "Pop"));
            x = s.top();
            s.pop();
            in[inLen++] = x;
        }
    }
    Node* root = Create(0, N - 1, 0, N - 1);
    PostOrder(root);

    return 0;
}
