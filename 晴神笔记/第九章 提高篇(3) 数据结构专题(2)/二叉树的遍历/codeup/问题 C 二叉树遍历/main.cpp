#include <cstdio>
#include <cstring>
/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

#define MAXN 30
char pre[MAXN], in[MAXN];

struct Node {
    char data;
    Node* lchild;
    Node* rchild;
};

/*
典型题目：前序中序建树，后序输出。
*/
Node* Build(int preL, int preR, int inL, int inR) {
    if (preL > preR) return NULL;
    Node* root = new Node;
    root->data = pre[preL];
    int i;
    for (i = inL; i <= inR; ++i) {
        if (in[i] == pre[preL]) { break; }
    }
    int numL = i - inL;
    root->lchild = Build(preL + 1, preL + numL, inL, i - 1);
    root->rchild = Build(preL + numL + 1, preR, i + 1, inR);
    return root;
}

void PostOrder(Node* root) {
    if (root) {
        PostOrder(root->lchild);
        PostOrder(root->rchild);
        printf("%c", root->data);
    }
}

int main(int argc, char** argv) {
    while (scanf("%s%s", pre, in) != EOF) {
        int N = strlen(pre);
        Node* root = Build(0, N - 1, 0, N - 1);
        PostOrder(root);
        printf("\n");
    }
    return 0;
}
