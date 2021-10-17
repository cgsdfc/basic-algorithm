#include <cassert>
#include <cstdio>
#include <cstring>
/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

/*
���鼯�������ͨ�����Ľڵ�����

��������˱��뻥��Ϊ���ѣ�˵����һ����ͨͼ��
��ĿҪ�����������࣬˵�������������ͨ������
*/

//������
#define MAXN (10000000)

int father[MAXN + 5];
int num[MAXN + 5];  // ͳ����iΪ���ķ����Ĵ�С�����i���Ǹ���Ϊ0.

int N;        // ������
int ans = 1;  // ��Сֵ��1.

int Find(int x) {
    int a = x;
    while (father[x] != x) {
        x = father[x];
    }
    while (father[a] != a) {
        int temp = father[a];
        father[a] = x;
        a = temp;
    }
    return x;
}

/*
����ʱ�Ĺؼ��Ż���
��Union�м���ÿ����ͨ�����Ĵ�С��ͬʱ�����������ֵ��
�����Ͳ��ö�α���������father��Ҳ��û����O(V)�ĺ�ʱ��
���ӶȾ���O(E)��
*/

void Union(int a, int b) {
    int faA = Find(a);
    int faB = Find(b);
    if (faA != faB) {
        father[faA] = faB;
        num[faB] += num[faA];
        num[faA] = 0;
        if (num[faB] > ans) {
            // ������ͨ����һ���ںϲ��в�����
            ans = num[faB];
        }
    }
}

/*
ע�����ͼ�ĵ���ԶԶ���ڱ�����
�ɼ��󲿷ֵ��ǹ����㡣����Ҫ����ʹ�㷨�ĸ��Ӷ�����E��
��Ҫ����V��
*/

int main(int argc, char** argv) {
    while (scanf("%d", &N) != EOF) {
        ans = 1;  // ��ʼ������
        for (int i = 1; i <= MAXN; ++i) {
            father[i] = i;
            num[i] = 1;
        }
        while (N--) {
            int A, B;
            scanf("%d%d", &A, &B);
            Union(A, B);
        }
        assert(ans > 0);
        printf("%d\n", ans);
    }
    return 0;
}
