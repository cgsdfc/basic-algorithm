#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

/*
ֱ��ģ��̰�Ĳ������£�
1. �ȴ���߽������
2. ��ʼ��������ǰ����6����򻻳���Ȼ������ֱ�������׶Σ����ߵ��
3. ��ǰС��6���������ֱ�����
*/
double Cost(int n) {
    double ans;
    if (n <= 4) return 10;
    if (n <= 8) return 10 + 2 * (n - 4);
    // ǰ���׶ν�����
    ans = 18;
    n -= 8;
    assert(n > 0);
    while (n > 0) {
        if (n >= 6) {
            // ��6�������ϵĳ����򻻳�������ˡ�
            if (n <= 8) {
                // ֱ�ӵ����ˡ�
                ans += 10 + (n - 4) * 2;
                break;
            } else {
                ans += 18;
                n -= 8;
            }
        } else {
            // ����6�����ˣ��������ܸ����ˡ�
            ans += n * 2.4;
            break;
        }
    }
    return ans;
}

/*
�����ʵ�֡�
����ÿ8���ﻻ��һ�Σ���ÿ�������һ�ڶ��׶Σ�8����ͻ�����
������Ϊ��
1. ��һ��8����������ꡣ
2. �����һ��8��������ʣ�µĴ���8����򻻳��ȼ����������ˣ�18 vs 19.2����
��ʣ�µĹ��ﲻ��8ʱ����Ϊ������==5ʱ�������ͼ�������ǡ����ȣ�����
1. nС��5ʱ������������
2. n���ڵ���5ʱ��������
*/
double Cost2(int n) {
    double ans;

    if (n <= 4) return 10;
    if (n <= 8) return 10 + 2 * (n - 4);
    // ���Դ�0��ʼ����Ϊ�����������׸�8���
    ans = 0;
    while (n >= 8) {
        ans += 18;
        n -= 8;
    }
    if (n < 5) {
        ans += n * 2.4;
    } else {
        ans += 10 + (n - 4) * 2;
    }
    return ans;
}

int main(int argc, char* argv[]) {
    int n;

    freopen("./in.txt", "r", stdin);

    while (scanf("%d", &n), n != 0) {
        double ans = Cost2(n);
        if ((int) ans == ans) {
            printf("%d\n", (int) ans);
        } else {
            printf("%.1f\n", ans);
        }
    }
    return 0;
}
