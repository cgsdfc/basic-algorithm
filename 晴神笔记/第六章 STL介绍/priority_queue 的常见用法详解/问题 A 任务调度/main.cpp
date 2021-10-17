#include <cctype>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <queue>
using namespace std;

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

#define MAXN (100000 + 5)

// i号节点的父亲的下标，0表示没有父亲。节点编号从1开始。
int Parent[MAXN];

/*
返回a是否为b的组先。
*/
bool IsAncestor(int a, int b) {
    while (b) {
        if (Parent[b] == a) { return true; }
        b = Parent[b];
    }
    return false;
}

void Print(int N) {
    for (int i = 1; i <= N; ++i) {
        printf("%d p %d\n", i - 1, Parent[i] - 1);
    }
}

struct cmp {
    // 两个节点的小于函数。
    bool operator()(int a, int b) {
        if (a == b) return false;
        if (!Parent[a]) {
            // a是根，优先级最高。
            return false;
        }
        if (!Parent[b]) {
            // b是根。
            return true;
        }
        if (IsAncestor(a, b)) {
            // a是组先，a>b
            return false;
        }
        if (IsAncestor(b, a)) {
            // b是组先，b>a
            return true;
        }
        // 二者没有组先关系，按字典序。
        // 编号小的任务先开始，则小的优先级高。
        return a > b;
    }
};

/*
复杂度：
建堆：NlogN，N为任务数（节点数），每次比较操作，复杂度是任务数的高度，即logN，
故建堆复杂度为 N*logN*logN。
排序复杂度和建堆一样（堆排序），故总的复杂度就是：

        N*(logN)^2
*/

int main(int argc, char** argv) {
    freopen("./in.txt", "r", stdin);

    int N;
    while (scanf("%d", &N) != EOF) {
        getchar();
        //		printf("N %d\n", N);

        priority_queue<int, vector<int>, cmp> q;
        memset(Parent, 0, sizeof(Parent));

        for (int i = 0; i < N; ++i) {
            int p;  // 父亲任务。
            scanf("Task%d", &p);
            //			printf("p %d\n", p);

            ++p;  // 0=>1.

            string str;
            getline(cin, str);
            //			printf("%s\n", str.c_str());

            if (str == "(NULL)") {
                //  没有孩子。
            } else {
                // 找出所有孩子任务（后续任务），就是找所有连续的数字串。
                int j = 0;
                while (j < str.size()) {
                    while (j < str.size() && !isdigit(str[j])) {
                        ++j;
                    }
                    if (j == str.size()) break;
                    int num = 0;
                    while (j < str.size() && isdigit(str[j])) {
                        num = num * 10 + (str[j] - '0');
                        ++j;
                    }
                    ++num;
                    Parent[num] = p;
                    //					printf("p %d num %d\n", p, num);
                }
            }
            /*
            因为有N个任务，并且有N行，同一个任务不可能出现两次，并且不可能有任务不出现，故每行的父亲任务
            必定不同。
            */
            // 任务入队。
            q.push(p);
        }

        //		Print(N);

        // 所有任务已经入队，出队即可。
        while (!q.empty()) {
            int x = q.top();
            q.pop();
            printf("Task%d%s", x - 1, q.empty() ? "\n" : " ");
        }
    }

    return 0;
}
