#include <algorithm>  // find
#include <cstdio>
#include <vector>

using namespace std;

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

#define MAXN 1005
int N, M;

/*
N个学生，从1--N编号，进行M个操作。
用vector模拟，复杂度为O(MN)。
*/

// vector<int> vi;
// typedef vector<int>::iterator It;

int A[MAXN];

int Find(int x) {
    for (int i = 0; i < N; ++i) {
        if (x == A[i]) return i;
    }
    return -1;
}

void Insert(int x, int pos, int off) {
    /*
    找到x，把它的位置移动off。
    */
    if (off > 0) {
        // 向后移。
        while (off--) {
            A[pos] = A[pos + 1];
            pos++;
        }
    } else {
        // 向前移。
        while (off++) {
            A[pos] = A[pos - 1];
            --pos;
        }
    }
    A[pos] = x;
}

int main(int argc, char** argv) {
    scanf("%d%d", &N, &M);
    for (int i = 1; i <= N; ++i) {
        A[i - 1] = i;
    }
    while (M--) {
        int p, q;
        scanf("%d%d", &p, &q);
        // 学号为p。q是移动的位移量。
        int pos = Find(p);
        Insert(p, pos, q);
    }
    for (int i = 0; i < N; ++i) {
        printf("%d%s", A[i], i == N - 1 ? "\n" : " ");
    }

    return 0;
}
