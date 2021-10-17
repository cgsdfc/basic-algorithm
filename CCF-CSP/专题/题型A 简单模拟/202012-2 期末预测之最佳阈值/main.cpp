#include <algorithm>
#include <cstdio>
using namespace std;

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

/*
��ÿ����x��r����������ڵ���x��r==1�ĸ������Լ�С��x��r==0�ĸ�����
��������ֵ��ӣ�������xΪ��������ȷ�ʡ����������Ԥ���㣬���Ӷ���NlogN�������򣩡�
����ÿ������Ϊ��������ȷ�ʺ󣬴Ӵ�С����ȡmax���ɡ�

�����Ͱ�Nƽ���ĸ��ӶȽ���NlogN��

���õ���

����ʵ�ֵ�ʱ��ע���ظ�Ԫ�ص����⡣���㷨�ʼǡ����㷨���ŵĻ��õ������棬
Ԫ���ǲ��ظ��ģ����Դ��ڣ����ڵ��ڣ�С�ڣ�С�ڵ�����Щ��ϵ�������д����ԡ�
�������ظ�Ԫ�صĻ�����ֻ�д��ڵ��ں�С�ڵ�����������ϵ�д������ˣ���С��
���پ��д����ԣ����Ե��Ƶ�ʱ��ֻ����С�ڵ��ڵ�ǰԪ��x��ֵ��Ȼ������һ��ѭ����
�������������������棬�ظ�Ԫ�ؿ����ò���������Ԫ������⣩������˵��С�ڵ��ڵ���ȷ�ʣ�
Ҳ����С�ڵ���x������r==0��Ԫ�ظ���������ΪС��x����r==0��Ԫ�ظ��������ǿ��еġ�
*/

struct Node {
    int y, r;
};

#define MAXN 100005

Node node[MAXN];
int ge[MAXN];  // ���ڵ���x����r==1�ĸ�����
int le[MAXN];  // С�ڵ���x����r==0�ĸ�����

int M;

// Ҫ�Ӵ�С����Ϊ��ͬ����ȷ��Ҫȡ����y��
bool cmp(Node a, Node b) {
    return a.y > b.y;
}

void Print(int a[]) {
    for (int i = 0; i < M; ++i) {
        printf("%d ", a[i]);
    }
    printf("\n");
}

/*
��֪��������ó��淽���ܲ���100�֡�
��Nƽ����ʱ������70�֡�
*/
void Solve2() {
    int maxval = -1;
    int ans;

    for (int i = 0; i < M; ++i) {
        // ��ÿ��y��Ϊ������
        int tot = 0;  // ��ȷ�ʡ�
        int the = node[i].y;
        for (int j = 0; j < M; ++j) {
            int pred = node[j].y >= the;  // Ԥ�⺯����
            if (pred == node[j].r) { ++tot; }
        }
        //		printf("y %d tot %d\n", the, tot);
        if (tot > maxval || (tot == maxval && the > ans)) {
            maxval = tot;
            ans = the;
        }
    }
    printf("%d\n", ans);
}

int main(int argc, char** argv) {
    scanf("%d", &M);
    for (int i = 0; i < M; ++i) {
        scanf("%d%d", &node[i].y, &node[i].r);
    }
    // ���淽����
    Solve2();
    return 0;

    sort(node, node + M, cmp);

    /*
    ��ÿ��x������ڵ���x����r==1�ĸ�����
    */
    for (int i = 0; i < M; ++i) {
        if (i != 0) {
            // ��ǰ�����̳С�
            ge[i] = ge[i - 1];
        }
        if (node[i].r) { ++ge[i]; }
    }
    //	Print(ge);

    /*
    ע�⣬����Ҫ��С�ڵ��ڹ�ϵ���ܵ�����ȷ��
    ������gtһ�����߼�������С�ڵ���x����r==0�ĸ��� ��
    */
    for (int i = M - 1; i >= 0; --i) {
        if (i != M - 1) { le[i] = le[i + 1]; }
        if (!node[i].r) { ++le[i]; }
    }
    //	Print(le);

    /*
    ����Ҫһ��ѭ��������ȷ�ʡ�
    ��Ϊle�����ݻ�������Ҫ��
    */
    int x = le[M - 1];
    for (int i = M - 2; i >= 0; --i) {
        if (node[i].y != node[i + 1].y) {
            // �������ȷ����С�ڵ���ȷ�ʡ�
            // yi > yi+1, �� le[i+1] ��ʾС�ڵ���yi+1����ȷ�ʣ�
            //  ����С��yi����ȷ�ʾ���le[i+1].
            // ���򱣳���ȷ�ʲ��䣬��Ϊyi==yi+1����ͬԪ����ȷ����ͬ��
            x = le[i + 1];
        }
        ge[i] += x;
    }
    //	Print(ge);

    int maxval = -1;
    int ans;
    for (int i = 0; i < M; ++i) {
        int rate = ge[i];
        if (rate > maxval) {
            maxval = rate;
            ans = node[i].y;
        }
    }

    //	printf("max %d\n", maxval);
    printf("%d\n", ans);

    return 0;
}
