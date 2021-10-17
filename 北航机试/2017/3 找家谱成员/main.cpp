#include <algorithm>
#include <cstdio>
#include <iostream>
#include <map>
#include <string>
#include <vector>
using namespace std;

#define MAXN 505  // 最大节点数。

map<string, int> mp1;
string mp2[MAXN];
int index;

// 两个路径。
vector<int> P1, P2;
int Root;
// 记录父节点，不存在为-1.
int father[MAXN];
// 记录节点是深度。
int depth[MAXN];

// 字符串转编号。
int Map(string& str) {
    if (mp1.count(str)) {
        return mp1[str];
    } else {
        mp1[str] = index;
        mp2[index] = str;
        return index++;
    }
}

// 获取从根节点到v的路径。
void GetPath(int v, vector<int>& p) {
    while (v != -1) {
        p.push_back(v);
        v = father[v];
    }
    // 从根节点开始。
    reverse(p.begin(), p.end());
}

/*
高效解法：不用跳到根，跳到LCA即可。
两个节点，先跳到同一层上（如果a的层次较大就a向上跳，
否则b向上跳，可以在输入时记录各个节点的深度），然后一起往上跳，直到跳到同一个节点。
这样当ab都比较深，但是ab比较接近时更快。事实上，复杂度等于ab的LCA的高度，而与深度无关。
*/
void Solve2(int a, int b) {
    // 层次差。
    int diff = abs(depth[a] - depth[b]);
    while (depth[a] > depth[b]) {
        a = father[a];
    }
    while (depth[b] > depth[a]) {
        b = father[b];
    }
    while (a != b) {
        a = father[a];
        b = father[b];
    }
    int lca = a;
    printf("%s %d\n", mp2[lca].c_str(), diff);
}

/*
给定一棵树，树上两个节点，求他们的LCA，即最近的公共祖先，并求节点的层次差。
思路：记录父节点，然后找到两个节点，往上跳，跳到根为止，记录两个节点到根节点的路径。
以根节点为起点的这两个路径序列的公共前缀Q求出来，则LCA就是Q的最后一个元素。
路径的长度恰好是该节点的层次，两个路径长度相减即可（应该不用取绝对值）。

算法的复杂度：是两个节点的深度之和的线性函数。
*/
void Solve(int a, int b) {
    GetPath(a, P1);
    GetPath(b, P2);
    // 找两个路径的公共前缀。
    int i = 0;
    while (i < P1.size() && i < P2.size() && P1[i] == P2[i]) {
        ++i;
    }
    int lca = P1[i - 1];
    int diff = P1.size() - P2.size();
    // 好像有绝对值的味道。。
    printf("%s %d\n", mp2[lca].c_str(), abs(diff));
}

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

int main(int argc, char** argv) {
    fill(father, father + MAXN, -1);
    fill(depth, depth + MAXN, 0);

    /*
    输入没有N进行提示，只能每次输入2个字符串，然后判断是否能
    连续输入三个。
    这个输入方式用C也是一样的，一次输入两个字符串scanf("%s%s")，然后看看是否能输入
    第三个字符串。
    */
    string s1, s2, s3;
    int a, b;
    while (cin >> s1 >> s2) {
        if (cin >> s3) {
            // 有第三个字符串说明三个一组，这是树的输入。
            int fa = Map(s1);
            int u = Map(s2);
            int v = Map(s3);
            father[u] = father[v] = fa;
            depth[u] = depth[v] = depth[fa] + 1;
        } else {
            // 查询的输入。
            a = Map(s1);
            b = Map(s2);
        }
    }
    Solve2(a, b);

    return 0;
}
