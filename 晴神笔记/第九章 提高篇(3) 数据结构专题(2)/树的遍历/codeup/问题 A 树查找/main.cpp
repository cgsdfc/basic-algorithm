#include <algorithm>
#include <cstdio>
using namespace std;

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

#define MAXN 1005
int N;
int data[MAXN];  // 完全二叉树。
int D;           // 查询的层次。

int main(int argc, char** argv) {
    while (scanf("%d", &N) != EOF && N != 0) {
        for (int i = 1; i <= N; ++i) {
            scanf("%d", &data[i]);
        }
        scanf("%d", &D);
        // 第D层的第一个节点是2^d-1 ，若第一个不存在，则此层不存在。
        int first = 1 << (D - 1);
        if (first > N) {
            printf("EMPTY\n");
        } else {
            /*
            第D层满的时候，恰有first个节点，
            但是不能超过first到N的总节点数。
            */
            int n = min(first, N - first + 1);
            for (int i = 0; i < n; ++i) {
                printf("%d%s", data[first + i], i == n - 1 ? "\n" : " ");
            }
        }
    }
    return 0;
}
