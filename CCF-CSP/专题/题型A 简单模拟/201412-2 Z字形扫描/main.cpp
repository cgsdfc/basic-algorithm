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
        // �����½��ߡ�
        while (i < N && j >= 0) {
            Add(i, j);
            i++;
            j--;
        }
        // ע�⣬��ʱi��j�Ѿ�Խ�磬Ҫ����ȥ��
        // ���ڸ���������һ��Ԫ������������
        --i;
        ++j;
        // ��������������£��������ҡ�
        if (i < N - 1) {
            i++;
        } else {
            j++;
        }
        // �����Ͻ��ߡ�
        while (i >= 0 && j < N) {
            Add(i, j);
            i--;
            j++;
        }
        ++i;
        --j;
        // ��������������ң��������¡�
        /*
        ע������һ������������i�����һ���Ϸ�λ��(N-1)ҪС��
        ������i�ǺϷ�λ�á�
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
