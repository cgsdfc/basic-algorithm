#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

int main(int argc, char* argv[]) {
    int n;
    while (scanf("%d", &n) != EOF) {
        while (n--) {
            int a;
            scanf("%d", &a);
            if (a & 1) {
                // odd
                puts("0 0");
                continue;
            }
            /*
            ���ֵ����2�����ࡣ
            ��Сֵ����4�����ࡣ
            */
            if (a % 4 == 0) {
                // ��Сֵ�����ֵ��
                printf("%d %d\n", a / 4, a / 2);
            } else {
                /*
                ע�⣬2�ı�������4�ı�����ģ4���ó�һ����2.
                ˵�����һ�����������2�ȡ�
                */
                printf("%d %d\n", a / 4 + 1, a / 2);
            }
        }
    }
    return 0;
}
