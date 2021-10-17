#include <cstdio>

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

/*
�ҵ�����a��b��Χ�ڵ����������Ȳ����У�ÿ�����һ�����С�
�Ȳ�����Ҫ��ÿ��Ԫ��������������Ԫ�ظ������ڵ���3.
*/

const int MAXN = 1e6 + 5;
bool p[MAXN];

struct {
    int data[MAXN];
    int len;
} prime;

int a, b;

/*
�Ȱ�a��b֮�ڵ�ȫ�������ҳ�����Ȼ��˫ָ��ɨ�衣
*/
void FindPrime() {
    prime.len = 0;
    for (int i = 2; i < MAXN; ++i) {
        if (!p[i]) {
            // iΪ������
            if (a <= i && i <= b) { prime.data[prime.len++] = i; }
            for (int j = 2 * i; j < MAXN; j += i) {
                p[j] = true;
            }
        }
    }
}

int main(int argc, char** argv) {
    scanf("%d%d", &a, &b);
    FindPrime();
    //	for (int i=0;i<prime.len;++i) {
    //		printf("%d ", prime.data[i]);
    //	}
    //	puts("");

    /*
    ÿ��ȡ��ǰ�������������㹫�Ȼ����������㹫�������������
    */
    int i = 0;
    while (i + 2 < prime.len) {
        int A = prime.data[i];
        int B = prime.data[i + 1];
        int d = B - A;  //���
        int j = i + 2;  // �ӵ���������ʼ���ԡ�
        // ע������j�����á�
        while (j < prime.len && prime.data[j] - prime.data[j - 1] == d) {
            ++j;
        }
        int len = j - i;
        if (len >= 3) {
            //			printf("%d\n",d);
            for (int k = i; k < j; ++k) {
                printf("%d%s", prime.data[k], k == j - 1 ? "\n" : " ");
            }
            // j��ǰ������ֵĹ��һ�£�j���ܳ�Ϊ�µ�����ͷ��
            i = j;
        } else {
            // B-A != C-B�����ڳ�����BΪ����ͷ��
            ++i;
        }
        /*
        ע�⣬����ҵ��˳���3�������֣���Ҫ������Щ���֣��Ӻ��ң�����ͻ��ظ���
        ��������������ʹ�B��ʼ�ң���������1�����֡�
        */
    }

    return 0;
}
