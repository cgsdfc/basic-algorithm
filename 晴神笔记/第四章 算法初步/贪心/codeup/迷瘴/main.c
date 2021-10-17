#include <math.h>
#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

#define MAXN 105

int P[MAXN];

/*
������N��Ũ��P[1]..P[n]����Һ���������V��
���Ϻ����ΪnV��Ũ��Ϊ����Ũ�ȵ�����ƽ��ֵ��

̰�Ĳ��ԣ�
V�����ֵΪȫ����Һ��ϣ���nV����СֵΪ0�����޽⡣
��Ũ�ȴ�С����������һ����һ����Һ���뵱ǰ��Һ��
ֱ����ǰŨ�ȴ���W����õ�����������Ӧ��Ũ�ȡ�

�����ԣ�
Ũ��С�ڵ���W����Һ��ϣ������Ũ�Ȳ��ᳬ��W����˶�����ƣ�
Ũ�ȴ���W����Һ�����ܱ���Ũ�ȵ�������Һ������С��W�����Ҳ���Լ��롣
�����Ũ�ȴ���W����Һ���࣬�����ᳬ��W��
��˿�����ҺʱӦ�ð���Ũ�ȴ�С�����˳��
*/

int CMP(const void* _a, const void* _b) {
    return *(int*) _a - *(int*) _b;
}

int main(int argc, char* argv[]) {
    int C;

    freopen("./in.txt", "r", stdin);

    scanf("%d", &C);
    while (C--) {
        int n, V, W;
        int i;
        double p;
        int v;

        scanf("%d%d%d", &n, &V, &W);
        for (i = 0; i < n; ++i) {
            scanf("%d", &P[i]);
        }
        qsort(P, n, sizeof(int), CMP);
        /*
        �޽⣺��С��Ũ�ȶ�����W�����޽⡣
        ����һ���н⡣
        */
        if (P[0] > W) {
            puts("0 0.00");
            continue;
        }

        p = P[0];
        v = 1;
        for (i = 1; i < n; ++i) {
            /*
            ע����Ũ������Ƿ�����Ӧ�ø��¡�
            */
            double newp = (i * p + P[i]) / (double) (i + 1);
            if (newp <= W) {
                p = newp;
                ++v;
            } else {
                break;
            }
        }
        /*
        �ٷ���������λС�������100�󣬼�����������
        */
        p = round(p);
        printf("%d %.2f\n", v * V, p / 100);
    }

    return 0;
}
