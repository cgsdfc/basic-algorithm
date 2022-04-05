#include <iostream>

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

/*
二叉树的查找/插入/删除/最大/最小 操作的纯C实现，
可以参考《数据结构》 目录下的代码。
纯C实现的一个特点就是用返回值来代替C++的引用传参。
*/

/*
鉴于二叉查找树一般给出键值，而不是编号，静态写法的一大优势就没有了，
当然静态写法没有内存泄漏。
*/

/*
静态写法。和普通的二叉树差不多，但是必备newNode函数，
因为节点是根据键值分配的。
*/
#define MAXN 100

int index; // Index 比较好，index与STL重名。

struct Node {
    int data;  // 键值。
    int lchild;
    int rchild;
} node[MAXN];

// 节点分配函数，也是初始化函数。
/*
注意，节点删除后是无法再次利用的，如果一道题目要求
先删除节点，然后又插入节点，反复多次，可能导致节点耗尽，
即 index 到达 MAXN。所以如果题目要求的二叉树存在这种情况，
就要考虑动态写法了。如果题目只有插入和查找操作，那么静态写法完全
可以应付。
*/
int NewNode(int data) {
    node[index].data = data;
    node[index].lchild = node[index].rchild = -1;
    return index++;
}

/*
在root中查找x，返回节点编号。递归写法。
*/
int search(int root, int x) {
    if (root == -1) {
        // 空树说明查找失败。
        return -1;
    }
    if (node[root].data == x) {
        // 查找成功。
        return root;
    }
    // 往左子树或者右子树递归。
    if (x < node[root].data) {
        // data相当于一个路标，data比x小就走左边，否则走右边。
        return search(node[root].lchild, x);
    } else {
        return search(node[root].rchild, x);
    }
}

/*
插入和删除算法和查找都有联系，因为插入要找到元素不存在的位置进行插入，
删除要找到元素所在的位置进行删除。
所以插入和删除都有查找的框架。

同时，因为插入和删除都是对树的结构做修改，所以root要传引用。
*/

/*
插入x。插入成功返回true，插入失败（元素已存在）返回false。
如果不需要处理插入失败的情况，可以返回void。
*/
bool insert(int& root, int x) {
    if (root == -1) {
        // 查找失败就是插入的位置。
        root = NewNode(x);
        return true;
    }
    if (node[root].data == x) {
        // 元素已存在。
        return false;
    }
    // 查找。
    if (x < node[root].data) {
        return insert(node[root].lchild, x);
    } else {
        return insert(node[root].rchild, x);
    }
}

/*
删除元素x。如果元素不存在返回false，否则返回true。
删除操作比较复杂。

删除的要领在于：被删除元素x的前驱和后继，即
1. x的前驱即小于x的最大元素，即x的左子树的最大值。
2. x的后继即大于x的最小元素，即x的右子树的最小值。
x的前驱和后继（如果存在），都可以代替x的位置而维持BST的性质。

算法：
1. 先找到x所在的节点。
2. 如果x是叶子，直接置空。
3. 如果x存在前驱（后继），找到前驱，用前驱的值覆盖x，然后递归删除前驱。
*/

/*
找最大值，一直往右。
找最小值，一直往左。
*/
int findMax(int root) {
    while (node[root].rchild != -1) {
        root = node[root].rchild;
    }
    return root;
}

bool deleteNode(int& root, int x) {
    if (root == -1) {
        // 元素不存在。
        return false;
    }
    if (node[root].data < x) { return deleteNode(node[root].lchild, x); }
    if (node[root].data > x) { return deleteNode(node[root].rchild, x); }
    // 找到了x。
    if (node[root].lchild == -1 && node[root].rchild == -1) {
        // 我是叶子。
        root = -1;  // 直接删除。
        return true;
    }
    if (node[root].lchild != -1 && node[root].rchild != -1) {
        // 两个孩子都有，必须用前驱/后继代替。
        // 可以交替删除前驱/后继。
        // 找前驱。
        int pre = findMax(node[root].lchild);
        // 前驱的数据覆盖x元素。
        node[root].data = node[pre].data;
        // 删前驱。
        return deleteNode(node[root].lchild, node[pre].data);
    }
    if (node[root].lchild != -1) {
        // 只有左孩子。用左孩子代替root。
        root = node[root].lchild;
    } else {
        // 只有右孩子。
        root = node[root].rchild;
    }
    return true;
}

int main(int argc, char** argv) {
    return 0;
}
