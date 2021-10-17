#include <cstdio>

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

int N, K;  // N��С���ѣ�K�ǳ�������

bool Judge(int n) {
    // K�ı��������߸�λ��ΪK��
    return n % K == 0 || n % 10 == K;
}

#define MAXN 1005

// �Ƿ���֡�
bool out[MAXN];

int main(int argc, char** argv) {
    scanf("%d%d", &N, &K);
    int i = 1;  // �������С�
    int M = N;  // ʣ�¶����ˡ�
    int next = 0;

    while (M != 1) {
        int k = 0;  // ������N�Ρ�
        while (out[next] && k < N) {
            next = (next + 1) % N;
            ++k;
        }
        if (Judge(i)) {
            out[next] = true;
            --M;
        } else {
            next = (next + 1) % N;
        }
        ++i;
    }
    for (int i = 0; i < N; ++i) {
        if (!out[i]) {
            printf("%d\n", i + 1);
            break;
        }
    }
    return 0;
}
