#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

const int Face[] = {50, 20, 10, 5, 1};
const int NF = 5;  // ������ֵ��

/*
̰�Ĳ��ԣ�������ֵ�Ӵ�С���ǣ�ÿ�ξ���ȡ����n/Fi��
ʵ���Ͼ��ǰ�n�ֽ��һ������Ľ������ĸ���λ��
*/

int main(int argc, char* argv[]) {
    int n;

    freopen("./in.txt", "r", stdin);

    while (scanf("%d", &n) != EOF) {
        int ans[10] = {};  // ÿ����ֵ�����š�
        int i;
        int flag = 1;  // �Ƿ�Ϊ��һ��Ԫ�ء�

        for (i = 0; i < 5; ++i) {
            if (n >= Face[i]) {
                ans[i] = n / Face[i];
                n %= Face[i];
            }
        }
        assert(n == 0);

        // ��������
        for (i = 0; i < 5; ++i) {
            if (!ans[i]) continue;
            if (flag) {
                flag = 0;
            } else {
                putchar('+');  // ��һ������ÿһ�������һ���Ӻš�
            }
            printf("%d*%d", Face[i], ans[i]);
        }
        putchar('\n');
    }

    return 0;
}
