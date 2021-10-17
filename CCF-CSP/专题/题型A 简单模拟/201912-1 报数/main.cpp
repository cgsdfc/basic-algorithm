#include <cstdio>

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */
int N;  // ������������

// �����Ĺ���
bool Judge(int a) {
    if (a % 7 == 0) return true;
    while (a) {
        if (a % 10 == 7) return true;
        a /= 10;
    }
    return false;
}

int ans[4];

int main(int argc, char** argv) {
    scanf("%d", &N);

    int i = 1;  // ������ǰ������
    int j = 0;  // ��ǰ����Ч������
    while (j < N) {
        int now = (i - 1) % 4;  // ��ǰ�������ˡ�
        if (Judge(i)) {
            // ������
            ++ans[now];
        } else {
            ++j;
        }
        ++i;
    }
    for (int i = 0; i < 4; ++i) {
        printf("%d\n", ans[i]);
    }
    return 0;
}
