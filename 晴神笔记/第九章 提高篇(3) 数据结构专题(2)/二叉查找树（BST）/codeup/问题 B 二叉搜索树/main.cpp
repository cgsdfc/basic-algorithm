#include <cstdio>
#include <cstring>
/*
去掉这句，C的东西还是可以不加前缀的引用的。
*/
using namespace std;
/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

#define MAXN 25

struct Node {
    int data;
    /*
    flag 表示这个元素已经被第二个序列的元素插入过了。
    一次合法的插入是，路径上所有元素都被插入过了，而待插入元素没有被插入过。
    如果第二个序列的全部元素的插入都是合法的，那么第二个序列和第一个序列形成相同的
    BST。
    判定之前要把flag全部false掉。
    */
    bool flag;
    int lchild, rchild;
} node[MAXN];

int N;
// index 是 strings.h 的库函数。
int Index;

int NewNode(int v) {
    node[Index].data = v;
    node[Index].lchild = node[Index].rchild = -1;
    node[Index].flag = false;
    return Index++;
}

void Reset(int root) {
    if (root != -1) {
        node[root].flag = false;
        Reset(node[root].lchild);
        Reset(node[root].rchild);
    }
}

// 建树必备。
void Insert(int& root, int x) {
    if (root == -1) {
        root = NewNode(x);
        return;
    }
    if (node[root].data == x) { return; }
    if (x < node[root].data) {
        Insert(node[root].lchild, x);
    } else {
        Insert(node[root].rchild, x);
    }
}

int Create() {
    char str[20];
    scanf("%s", str);
    int len = strlen(str);
    int root = -1;

    for (int i = 0; i < len; ++i) {
        Insert(root, str[i] - '0');
    }
    return root;
}

// 判定一次插入是否合法。
bool Check(int root, int x) {
    if (root == -1) {
        // 没有x的位置。
        return false;
    }
    if (node[root].data == x) {
        // 找到了x。
        if (node[root].flag) {
            // x出现了多次。
            return false;
        } else {
            node[root].flag = true;
            return true;
        }
    } else {
        // 还在沿途。
        if (!node[root].flag) {
            /*
            为什么沿途节点如果不是true就不行：
            如果沿途有一个false，即缺口，那么表示这个缺口的元素
            还没有出现，如果此时先插入x到正确位置，等后来再插入缺口的元素，
            就违反了BST插入的原则，因为按照正常的插入顺序，后面插入的节点不可能反过来
            成为前面插入的节点的父节点。而只能是作为孩子节点。
            所以如果出现了这种情况，说明在第二个序列实际重建二叉树的过程中，x是作为缺口的父节点，
            而不是孩子节点。

            换句话说，由于二叉树插入建树具有“先插入的为父亲，后插入为孩子”的特点，
            一个节点在插入之前，它的全部组先节点必须都已经插入了。
            */
            return false;
        }
        // 继续递归检查。
        if (x < node[root].data) {
            return Check(node[root].lchild, x);
        } else {
            return Check(node[root].rchild, x);
        }
    }
}

// 判定序列和BST是否对应。
bool Judge(int root, char str[], int len) {
    for (int i = 0; i < len; ++i) {
        if (!Check(root, str[i] - '0')) { return false; }
    }
    return true;
}

// 判断两个插入序列是否对应同一颗二叉搜索树。
// 可以建两棵树，然后判断，但更快的方法是建一棵树，然后用另一个序列来查询这棵树。
int main(int argc, char** argv) {
    int N;
    while (scanf("%d", &N), N) {
        Index = 0;
        int root = Create();
        while (N--) {
            char str[20];
            scanf("%s", str);
            bool ans = Judge(root, str, strlen(str));
            puts(ans ? "YES" : "NO");
            Reset(root);
        }
    }
    return 0;
}
