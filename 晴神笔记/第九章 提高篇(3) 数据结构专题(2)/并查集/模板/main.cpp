#include <iostream>

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

/*
并查集，支持以下操作：
1. 给定一个元素x，查找它属于哪个集合（即找到它所在的集合的代表元/根节点）。
2. 合并两个集合。

用树表示一个集合，用森林（树的集合）表示若干集合，
对于每一个集合，所有元素都在一个一般树上，每个元素记录其父节点，
而根节点就代表这个集合，用于判断两个集合是否为同一个。
根节点的父亲设置为自己，即根节点成环，这只是为了区分根节点和非根节点，
并不是说树上有环。

集合的标号一般从1开始。
*/

// 最多100个元素。
#define MAXN 105

// Union-Find Set
struct UFS {
    int father[MAXN];
    int N;  // N个元素，1--N。

    UFS() {
        // 初始化，每一个元素都是根节点，形成N个一元集合。
        // 然后通过合并形成题目要求的集合关系。
        for (int i = 1; i <= N; ++i) {
            // 设置每一个元素的父节点为自己。
            father[i] = i;
        }
    }
    // Naive查找，复杂度为O(h)，h是树的高度，可能退化至N.
    // 找一个元素所在的集合的根节点，即一个元素属于哪个集合。
    int Find(int x) {
        while (x != father[x]) {  // x不是根。
            x = father[x];        // 往上跳。
        }
        return x;
    }
    // 合并两个元素所在的集合。
    // 注意，这本质上是合并两个集合，但是集合是由其根元素指出的，
    // 所以要从其中的某元素（即ab）找到根节点，然后注意，不要合并相同的集合，
    // 否则会成环。例如 father[2]=4, father[4]=2，这样就会卡死Find。
    void Union(int a, int b) {
        int faA = Find(a);  // 先找ab的根节点。
        int faB = Find(b);
        if (faA != faB) {
            // ab所指的集合不是同一个，才合并。
            father[faA] = faB;  // 合并两个集合，就是对根节点进行操作，使一个树成为另一个树的子树。
        }
    }
    // 带路径压缩的查找，平摊复杂度O(1)。
    int Find2(int x) {
        // 注意，在一次查找中把路径上的节点的父节点全部改为根。
        // 而不是只把x的父节点改为根。这样可以快些。
        // 先保存x，后面要再走一次路径。
        int a = x;
        // 先找到根，因为x的父节点是不是根，不知道。
        while (x != father[x]) {
            x = father[x];
        }
        // x为根。进行路径压缩。
        // 完成了压缩后的x，再进入Find就是O(1)操作。
        while (a != father[a]) {
            int temp = father[a];  // 先保存旧的父节点.
            father[a] = x;         // 父节点改为根。
            a = temp;              // 继续遍历。
        }
    }
};

int main(int argc, char** argv) {
    return 0;
}
