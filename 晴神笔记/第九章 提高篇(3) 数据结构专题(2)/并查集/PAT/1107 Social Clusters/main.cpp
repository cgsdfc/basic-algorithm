#include <algorithm>
#include <cstdio>
using namespace std;

#define MAXK (1001)  // ��������±ꡣ
#define MAXN (1001)  // ���� ��

struct Hobby {
    // �������а��á�
    int data[MAXK];
    int len;
    // ��ѯĳ�������Ƿ���ڡ�
    bool hash[MAXK];
};

// N���˵İ�����Ϣ��
Hobby hb[MAXN];

bool Has(int a, int b) {
    // �������Ƿ��й������á�
    if (hb[a].len > hb[b].len) { swap(a, b); }
    // �����϶̵İ����б�
    for (int i = 0; i < hb[a].len; ++i) {
        int x = hb[a].data[i];
        if (hb[b].hash[x]) { return true; }
    }
    return false;
}

/*
���������ˣ�ֻҪ�����й������ã����Ǿ���һ���ߣ�
���ֹ�ϵ�����д����ԣ�Ҳ����˵��A��B�й������ã�B��C�й������ã�
����A��C����û�й������á�

ö�����бߣ���ö�����еĽڵ�ԣ���������й������ã��ͽ��кϲ���
O(N*N*K)������Nƽ���Ѿ�10e6�ˣ��ж��бߵ��߼���ÿ�Щ��
��ÿ���˵İ����б�����Ȼ���ù鲢���ж��Ƿ��й���Ԫ�أ�
Ԥ����ĸ��Ӷ���NKlogK��ÿ�β�ѯ�ĸ��Ӷ���K��

����1��
��һ��MAXK����bool�Ͷ�Ӧÿ���˵İ����б���ѯʱ�������ߵ����顣
Ԥ������O(K)��ÿ�β�ѯ��O(MAXK),

����2��
����Ȼ��鲢�ҹ���Ԫ�ء�Ԥ������O(KlogK), ÿ�β�ѯ��O(K)

����3:
��ÿһ���ˣ��ȼ�¼bool���飬Ҳ��¼int���飬Ȼ���ѯʱ����һ���˵�int���飬
����һ���˵�bool���顣Ԥ������O(K)��ÿ�β�ѯ��O(K).
*/

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

int N;  // ��������

int father[MAXN];
int num[MAXN];

int Find(int x) {
    int a = x;
    while (x != father[x]) {
        x = father[x];
    }
    while (a != father[a]) {
        int temp = father[a];
        father[a] = x;
        a = temp;
    }
    return x;
}

void Union(int a, int b) {
    int faA = Find(a);
    int faB = Find(b);
    if (faA != faB) {
        father[faA] = faB;
        num[faB] += num[faA];
        num[faA] = 0;
    }
}

bool cmp(int a, int b) {
    return a > b;
}

/*
���ݵ��ص㣬ÿ���˵�Kֵ�Ƚ�С�����ӽ�MAXK�������ñȽ�ϡ�裬
����O(K)�ıȽ��㷨���ᳬʱ��
*/

int main(int argc, char** argv) {
    scanf("%d", &N);
    for (int i = 1; i <= N; ++i) {
        int k;
        scanf("%d:", &k);
        hb[i].len = k;
        for (int j = 0; j < k; ++j) {
            int x;
            scanf("%d", &x);
            hb[i].data[j] = x;
            hb[i].hash[x] = true;
        }
    }
    // ���鼯��ʼ����
    for (int i = 1; i <= N; ++i) {
        father[i] = i;
        num[i] = 1;
    }
    // ö��ÿһ���ˡ�
    for (int i = 1; i <= N - 1; ++i) {
        for (int j = i + 1; j <= N; ++j) {
            if (Has(i, j)) { Union(i, j); }
        }
    }
    // num��¼��ÿ�������Ĵ�С��
    sort(num + 1, num + N + 1, cmp);
    // ͳ�Ʒ����������cluster������
    int len = 0;
    for (int i = 1; i <= N; ++i) {
        if (num[i]) {
            ++len;
        } else { // ��Ϊ������ģ����涼��0�����ÿ��ˡ�
            break;
        }
    }
    printf("%d\n", len); // ������з����Ĵ�С��
    for (int i = 1; i <= len; ++i) {
        printf("%d%s", num[i], i == len ? "\n" : " ");
    }

    return 0;
}
