#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

/*
N�ʺ�����
ÿһ���ʺ���ڲ�ͬ�У���ͬ�У���˷���N���󣬼��ÿ���ʺ�
�Ƿ���������һ���Խ��ߡ�
����ö��ȫ���еķ������Ѿ������˲���ͬһ�С�ͬһ�е�Ҫ��ʣ�µ�
��һ�ַŷ��������ֵ������ö�٣�����ö��1--N��ȫ���С�
��ȫ���еĻ������ж����Ƿ�����Խ���ԭ��
*/

#define MAXN 15
int N;
int ans[MAXN];
int hashtable[MAXN];
int has;  // �Ƿ��н⡣

/*
��鵱ǰ�����Ƿ�����Խ���ԭ��
*/
int OK(void) {
    int i;
    for (i = 0; i < N - 1; ++i) {
        int j;
        for (j = i + 1; j < N; ++j) {
            /*
            �������к�֮��ľ���ֵ�����к�֮��ľ���ֵ��
            �������ʺ���һ���Խ��ߡ�
            */
            if (abs(i - j) == abs(ans[i] - ans[j])) return 0;
        }
    }
    return 1;
}

// ��ӡ��ģΪN��N�ʺ󷽰����Լ��Ƿ����һ��������
void DFS(int index) {
    int i;
    if (index == N && OK()) {
        for (i = 0; i < N; ++i) {
            printf("%d%s", ans[i], i == N - 1 ? "\n" : " ");
        }
        has = 1;
        return;
    }
    if (index == N) { return; }
    // ʣ�¾���ȫ���е��߼��ˡ�
    for (i = 1; i <= N; ++i) {
        /*
        �ҵ���ǰû�ù�����С����
        */
        if (!hashtable[i]) {
            /*
            ���һ�·�i�Ƿ���֮ǰ�Ļʺ���ڶԽ��ߵĳ�ͻ������֦��
            */
            int ok = 1;
            int j;
            for (j = 0; j < index; ++j) {
                // index�ǵ�ǰ���У�i�ǵ�ǰ���У�j��֮ǰ���У�ans[j]��֮ǰ���С�
                if (abs(index - j) == abs(i - ans[j])) {
                    ok = 0;
                    break;
                }
            }
            if (ok) {
                hashtable[i] = 1;
                ans[index] = i;
                DFS(index + 1);
                hashtable[i] = 0;
            }
        }
    }
}

int main(int argc, char* argv[]) {
    while (scanf("%d", &N) != EOF) {
        has = 0;
        DFS(0);
        if (!has) { puts("no solute!"); }
    }
    return 0;
}
