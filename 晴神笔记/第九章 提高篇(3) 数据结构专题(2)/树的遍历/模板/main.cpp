#include <vector>
using namespace std;

/*
一般树的模板。
这里的一般树有两大特征：
1. 子节点个数不限。
2. 子节点没有先后次序。

实现方式：（静态写法）
1. vector 法，用vector 保存所有子节点的下标。
2. 数组法，事先知道子节点的上限，然后开一个数组，再加一个len。
3. 左孩子右兄弟法，左指针指向第一个孩子，右指针指向下一个兄弟。
适合没有C++，并且数组法空间不足的情况。
4. 父亲法，开一个数组father，大小为节点数，记录每一个孩子的父节点，
再记录根节点root，则可以方便的遍历从某节点一直到根的所有组先，
如果再记录leaf，即某节点是否为叶子，则可以方便遍历所有叶子到根的路径。
缺点是对于一个节点，要找到它的所有孩子是O(N)的复杂度。

对于静态写法而言，上述结构体Node都要保存在一个数组中，数组上限是节点数上限。
然后节点的编号和数组下标对应。
如果题目没有给出节点的编号（比方说只给了数据域）， 那么必须实现 newNode
函数，在保存数据域的同时为节点生成编号。
如果题目直接给出了编号，那么可以直接用题目给的编号索引节点数组。

在所有表示法中，-1表示NULL。
*/

#define MAXN 100 // 这是节点数上限。

struct Node {
  int data;
  vector<int> child;
};

int index;
Node node[MAXN]; // 静态的节点数组。

int NewNode(int v) {
  node[index].data = v;
  node[index].child.clear(); // 空的child表示没有孩子，不需要-1了。
  return index++;
}

void AddChild(int root, int i) {
  // vector 直接尾插。
  node[root].child.push_back(i);
}

#define MAXC 10 // 已知的，子节点的最大数量。
struct Node2 {
  int data;
  int child[MAXC];
  int len; // len=0表示没有孩子。
};

Node2 node2[MAXN];

int NewNode2(int v) {
  node2[index].data = v;
  node2[index].len = 0;
  return index++;
}

void AddChild2(int root, int i) {
  // 尾插。
  node2[root].child[node2[root].len++] = i;
}

// 孩子-兄弟 表示法
struct Node3 {
  int data;
  int child; // 第一个孩子。
  int next;  // 下一个兄弟。
};

Node3 node3[MAXN];

int NewNode3(int v) {
  node3[index].data = v;
  node3[index].child = node3[index].next = -1;
  return index++;
}

/*
注意对于一般树的DFS，是没有显式的边界判定的。
因为：
1. 保证最开始时root非空。
2. 每次对合法的，存在的孩子进行递归，不可能混入空节点。

本质上：
1. 一般树不保存空的孩子，只保存实际存在的孩子。
2. 二叉树的写法决定了左右两个指针可能为空，所以保存了空节点。
*/
void PreOrder3(int root) {
  printf("%d ", node3[root].data);
  // 要遍历root的所有孩子，就是遍历它的第一个孩子，以及所有的兄弟。
  for (int i = node3[root].child; i != -1; i = node3[i].next) {
    PreOrder3(i);
  }
}

// 为root节点添加一个孩子，实际上是链表头插法，注意链表操作。
void AddChild3(int root, int i) {
  // 注意头插法是不用特判的。
  node3[i].next = node3[root].child;
  node3[root].child = i;
}

/*
如果有C++, 则使用vector法，最方便。
如果没有C++，但是最大孩子数已知，并且不大，可能是固定的（多叉树），
则用数组法；
如果孩子数不确定并且可能很大，就用孩子-兄弟法。
*/

/*
对于DFS，BFS，多叉树和二叉树的最大不同在于如何遍历所有孩子，
因为二者都涉及遍历所有孩子的操作：
1. DFS，对所有孩子进行递归。
2. BFS，把所有孩子入队。

所以它们的模板就不再累述了。
*/

/*
用 DFS 求每一个节点的层次（深度）。
层次又称为深度，或者高度。
树的高度/深度等于最大的节点高度，即从根到叶子的最长的路径长度。

节点的层次的定义如下：
1. 根节点层次为0 （可以为1，视要求而定）。
2. 设一节点P的层次为H，则P的孩子（如果有）的层次为 H+1。

一般而言，用BFS求层次比较直观，因为BFS就是层序遍历；
但是用DFS也可以求层次，并且不需要STL的queue。
*/

/*
root是当前访问的子树的根，deep是对应的层次值。
访问root的同时得到了它的层次deep，所以此模板可以遍历所有节点
和对应的层次值。

应用有：
1. 求树的高度，或者最大的层次值，只需对所有节点的层次取 max。
2. 求所有叶子节点的最大/最小层次值，只需对当前节点判定为叶子，然后取 max/min。
3. 计算层次相同的所有节点的某些性质，比如：
        1. 计数某一层次的节点数；
        2. 计数某一层次的叶节点数；
只需对层次值进行散列，用散列表保存某层次值对应的数据即可，层次的最大值可以在
DFS 中求出，层次最大值的上界为节点数 （成链），开数组用。

应用的具体代码见《实战指南》，它用的都是DFS，而我写的代码都是BFS。

DFS 写法的优点：
1. 不需要STL的queue，适合纯C。
2. 比BFS来的简洁。
*/
void DFS(int root, int deep) {
  printf("%d deep %d\n", root, deep);
  for (int i = 0; i < node[root].child.size(); ++i) {
    DFS(node[root].child[i], deep + 1);
  }
}

/*
DFS 枚举路径
这里说的路径是从根到叶子的路径。注意点有：
1. 路径保存在数组里，新路径覆盖旧路径，如果要对全部路径做进一步处理，
可以考虑全部保存。
2. 如果题目要求路径的输出按照字典序，则可以对所有child向量进行排序，
使得遍历路径的顺序就是题目要求的顺序，而不必等生成全部路径后再排序。
比如题目要求路径按节点权值的字典序输出，即路径是由节点权重构成，路径本身作为
序列按字典序排列，则可以对child 按照节点权值排序。
*/

struct {
  int data[MAXN];
  int len;
} path;

void DFS2(int root) {
  // 把 root加入当前路径。
  // 注意在多叉树的写法中，root不会有非法值如-1.
  path.data[path.len++] = root;
  // 检查是否到达叶子，即边界。
  if (node[root].child.empty()) {
    // 得到一条完整的路径，输出。
    // 也检查路径是否满足题目条件。
    for (int i = 0; i < path.len; ++i) {
      printf("%d%s", path.data[i], i == path.len - 1 ? "\n" : " ");
    }
    // 还不能返回，因为要恢复path。
  } else {
    // 继续访问子节点。
    for (int i = 0; i < node[root].child.size(); ++i) {
      DFS2(node[root].child[i]);
    }
  }
  // DFS 对全局状态做的变化，在返回前一定要恢复。
  --path.len;
}

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

int main(int argc, char **argv) { return 0; }
