#include <cstdio>

#define MAXN 505

int N;
int A[MAXN][MAXN];

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */
struct {
    int data[MAXN * MAXN];
    int len;
} ans;

void Add(int i, int j) {
    ans.data[ans.len++] = A[i][j];
}

void Solve() {
    int i = 0;
    int j = 0;

    Add(i, j);
    ++j;
    while (i < N && j < N) {
        // 向左下角走。
        while (i < N && j >= 0) {
            Add(i, j);
            i++;
            j--;
        }
        // 注意，此时i或j已经越界，要拉回去。
        // 基于刚走完的最后一个元素来调整方向。
        --i;
        ++j;
        // 如果能向下则向下，否则向右。
        if (i < N - 1) {
            i++;
        } else {
            j++;
        }
        // 向右上角走。
        while (i >= 0 && j < N) {
            Add(i, j);
            i--;
            j++;
        }
        ++i;
        --j;
        // 如果能向右则向右，否则向下。
        /*
        注意有下一个的条件，是i比最后一个合法位置(N-1)要小。
        而不是i是合法位置。
        */
        if (j < N - 1) {
            j++;
        } else {
            i++;
        }
    }
}

int main(int argc, char** argv) {
    scanf("%d", &N);
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            scanf("%d", &A[i][j]);
        }
    }
    Solve();
    for (int i = 0; i < ans.len; ++i) {
        printf("%d%s", ans.data[i], i == ans.len - 1 ? "\n" : " ");
    }
    return 0;
}
