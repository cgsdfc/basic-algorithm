#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

#define MAXN 100005

/*
��Ȼp����N����������10e9������ֻ��mp��˵�ʱ�򣬲ſ���Խ�磬
���������ط���int���ɣ����ʱ���Խ��������κε�int��
*/
int a[MAXN];

int CMP(const void* _a, const void* _b) {
    // ��С������������
    return *(int*) _a - *(int*) _b;
}

// M<=m*p.
int LessEq(int M, int m, int p) {
    int res = m * p;
    return res < 0 || M <= res;
}

int main(int argc, char* argv[]) {
    int N, p;
    int i;
    int m, M;
    int ans = 0;  // ������󳤶ȡ�

    freopen("./in.txt", "r", stdin);

    scanf("%d%d", &N, &p);
    for (i = 0; i < N; ++i) {
        scanf("%d", &a[i]);
    }
    qsort(a, N, sizeof(int), CMP);
    /*
    ȡ��m����Mȡ����MС�ڵ���mp�����Ԫ�أ�ʹ��һ�����е�Ԫ����ࡣ
    ��m���������е���Сֵ��������ʱ����Ϊmp��������M���ٲ����١�
    ��M�����λ������M��λ�����������������m�����λ��ʱ���͵õ���
    ��������С�����M�������һ��Ԫ��ʱ��M�޷��������ˣ���ʱ�ó������ֵ����
    �𰸡�

    ������logn��Ȼ���m��ʼΪ0��Ԫ�أ�M��ʼΪ�������������Ԫ�ء�
    ֮�󲻶�����m������M��ֱ��M�������Ԫ�ء��������O(n)���ܵĸ��Ӷ�Ϊnlogn��
    */
    /*
    ����two-pointer��������������m��M����ָ�룬���������¡�
    ����֮���Թ��ڶ��ַ�������Ϊ����M�����ö��ַ����ң�������m��N֮���һ������mp������
    �����mp��upper-bound��
    */

    m = 0;
    for (i = N - 1; i >= 0; --i) {
        if (LessEq(a[i], a[m], p)) {
            M = i;
            break;
        }
    }
    ans = M - m + 1;

    //	printf("%d\n", ans);

    while (M <= N - 1 && m <= N - 1) {
        int len;

        ++m;
        if (m > M) break;

        for (i = M; i < N && LessEq(a[i], a[m], p); ++i)
            ;
        M = i - 1;
        len = M - m + 1;

        //		printf("m %d M %d len %d\n", m,M,len);

        if (len > ans) { ans = len; }
    }

    printf("%d\n", ans);

    return 0;
}
