#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

#define MAXM 1005

/*
��¼��ֵΪi��������
��ֵ���ϱ������Ƕ��ؼ���
һ����ֵ������500.
*/
int hashtable[510];

// int Min(int a, int b) {
//	return a<b?a:b;
//}

int main(int argc, char* argv[]) {
    int N, M;
    int i;
    int minV1 = MAXM;

    scanf("%d%d", &N, &M);
    for (i = 0; i < N; ++i) {
        int x;
        scanf("%d", &x);
        hashtable[x]++;
    }
    /*
    ע������߼�
    ���ֵȷ�M�Ͳ��ȷ�M�������
    ���ȷ�M����Ҫ��ͬ����ֵ��Ӳ������2����
    �����ȷ֣���Ҫ��������ֵ��Ӳ�Ҹ�������1����
    */
    for (i = 1; i <= 500; ++i) {
        int x = i;
        int y = M - x;
        if (y > 500) {
            // ������ֵ��Χ�������ָܷ
            continue;
        }
        if (!hashtable[x] || !hashtable[y]) {
            // ����ֵ�����ڡ�
            continue;
        }
        if ((x == y && hashtable[x] >= 2) || (x != y && hashtable[x] >= 1 && hashtable[y] >= 1)) {
            // �ҵ�һ��⡣
            /*
            ע�⣬����Ҫ������Сֵ���㷨����Ϊ��V1��ö�پ��Ǵ�С����ģ�
            ֻҪ�ڵ�һ�����н⴦���V1���ɡ�
            */
            //			int V1=Min(x, y);
            //			if (V1 < minV1) {
            //				minV1=V1;
            //			}
            printf("%d %d\n", x, y);
            return 0;
        }
    }
    puts("No Solution");
    //	if (minV1 == MAXM) {
    //		puts("No Solution");
    //	} else {
    //		printf("%d %d\n", minV1, M-minV1);
    //	}

    return 0;
}
