#include <iostream>

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

/*
检查给定的先序是否为BST或者反转BST的先序，
如果是则输出后续。
先找到根，然后比根小的连续元素是左子树，左子树的后面是右子树，
而右子树必须大于等于根。
*/

#define MAXN 1005

struct Node {
    int data;
    int lchild, rchild;
};

Node node[MAXN];
int pre[MAXN];
int index;
bool ans;  // 是否成功。
int N;

int newNode(int v) {
    node[index].data = v;
    node[index].lchild = node[index].rchild = -1;
    return index++;
}

int Create(int preL, int preR, bool (*cmp)(int, int)) {
    if (!ans || preL > preR) {
        // 已经检查不成功了。
        return -1;
    }

    int x = pre[preL];  // 根。
    int root = newNode(x);

    int k = preL + 1;
    // 前半段应该满足cmp
    while (cmp(pre[k], x) && k <= preR) {
        ++k;
    }
    // 检查后半段是否满足!cmp.
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

// 后序遍历输出。
void Print(int root, int& i) {
    if (root != -1) {
        Print(node[root].lchild, i);
        Print(node[root].rchild, i);
        printf("%d%s", node[root].data, i == N - 1 ? "\n" : " ");
        ++i;
    }
}

// 正常二叉树。
bool Less(int a, int b) {
    return a < b;
}
// 反转二叉树的版本。
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
        index = 0;  // 重新分配，否则不够用。
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
