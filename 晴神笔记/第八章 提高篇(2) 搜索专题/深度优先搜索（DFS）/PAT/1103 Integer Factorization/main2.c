#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
Ԥ���� ����N^P С�ڵ��� N ������
��Ϊ��ö������ʱ����ʵö�ٵ������ӵ��ݣ�
�������ӵ��ݱ����Ӵ�����ö�ٸ��ӶȻ��½���
*/

// ʹ���������������������е�pow��������ϵͳ��powҪ�졣
static int Power(int a, int b) {
    int ans = 1;
    while (b) {
        if (b & 1) { ans *= a; }
        a *= a;
        b >>= 1;
    }
    return ans;
}

/*
n <= N^(1/P)����N���P��С����N=400��P=2ʱ��nȡ���Ͻ磬
��20.
*/
#define MAXF 40
/*
fac[i]=i^P.
*/
struct {
    int data[MAXF];
    int len;
} fac;

/*
���ɵ�����������󳤶ȣ�
����K�����ֵ��
*/
#define MAXK (400 + 1)

typedef struct List {
    int data[MAXK];
    int len;
} List;

// ����ȫ�֣��ֲ����ֵ��
static List ans, temp;
static int MaxSum = -1;

static int N, K, P;

void Init(int N, int P) {
    int i = 0;
    int p = 0;
    while (p <= N) {
        p = Power(i, P);
        fac.data[fac.len++] = p;
        ++i;
    }
}

/*
�ó�fac����������ת��Ϊ�ڼ����в���Ԫ�ؿ��ظ����Ӽ���
ʹ���Ӽ�������������ĳ�������������⣬
����ģ�弴�ɡ�
*/

static void DFS(int index, int nowK, int nowN, int nowSum) {
    if (nowK == K && nowN == N) {
        // һ���⡣
        if (nowSum > MaxSum) {
            /*
            ö�ٵ�˳�򣬱�֤��temp�����ǵݼ��ģ�����ÿ�ε�temp���ֵ���ݼ��ġ�
            */
            MaxSum = nowSum;
            ans = temp;
        }
        return;
    }
    /*
    ��δ���֣����ǳ����˱�Ȼû��������
    1. nowK == K���� nowN != N
    2. nowK < K���� nowN >= N
    */
    if (nowK == K || nowN >= N) { return; }
    /*
    ģ�������Ԫ�ؿ��ظ������������
    1. ѡ��ǰԪ�أ�Ȼ��������ǵ�ǰԪ�ء�����һ��Ϊʲô��
    ��Ϊ����ÿһ��Ԫ�أ�������ѡ 0-m ���������0�����ǾͿ�����һ��Ԫ�أ�
    �������0�����Ǿ���ζ�ſ���һֱѡ��ֱ������߽���������������֪��������ѡ���١�
    ��Ϊ���û�����������Ļ����ǿ������������ġ�
    2. ��ѡ��ǰԪ�أ�Ȼ�����������һ��Ԫ�ء�
    */

    if (index < 1) {
        // ���Ӳ����� 0.
        return;
    }

    // ѡ��ǰԪ�ء�
    temp.data[temp.len++] = index;
    DFS(index, nowK + 1, nowN + fac.data[index], nowSum + index);
    temp.len--;

    // ��ѡ��ǰԪ�ء�
    DFS(index - 1, nowK, nowN, nowSum);
}

int Main2(void) {
#ifndef ONLINE_JUDGE
    freopen("./in.txt", "r", stdin);
#endif

    scanf("%d%d%d", &N, &K, &P);
    Init(N, P);
    DFS(fac.len - 1, 0, 0, 0);

    if (MaxSum == -1) {
        // û��һ���Ϸ��⡣
        printf("Impossible\n");
    } else {
        int i;
        // 169 = 6^2 + 6^2 + 6^2 + 6^2 + 5^2
        printf("%d = ", N);
        for (i = 0; i < ans.len; ++i) {
            printf("%d^%d%s", ans.data[i], P, i == ans.len - 1 ? "\n" : " + ");
        }
    }
    return 0;
}

#ifdef ONLINE_JUDGE
int main(void) {
    return Main2();
}
#endif

/*
����ⷨ 257 ms��
�� Main1 �Ľⷨ 659 ms �졣
*/
