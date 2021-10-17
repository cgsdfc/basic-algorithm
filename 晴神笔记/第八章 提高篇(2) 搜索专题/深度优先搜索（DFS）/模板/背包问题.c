#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

/*
�������⣺
��N����Ʒ��ÿ����Ʒ������ͼ�ֵ�������ԣ������������ʽ������
������Ҫ����ѡ��������Ʒ��������ΪV�ı����У��������������V�������£�
ʹ���ܼ�ֵ����������ܼ�ֵ��

����ı�����ö�پ���N��Ԫ�ص�ȫ���������Ӽ���������ͬԪ���������Ӽ���Ҳ�����ռ���
��������ö�ٷ��������ظ���ö�������Ӽ�����˸��Ӷ��� 2^N ��
*/

/*
������Ʒѡ�񷽰���
*/
#define MAXN 100
struct {
    int data[MAXN];
    int len;
} ans, temp;

int N;                 // ��Ʒ������
int V;                 // ��������
int MaxValue = 0;      // ȫ������ֵ��
int W[MAXN], C[MAXN];  // ��Ʒ����� ����ֵ��

/*
������Ʒ���±꣬�Ӵ�С����ÿһ����Ʒ������ÿһ����Ʒindex������ѡ��
1. ѡ����Ʒ��
2. ��ѡ����Ʒ��
��������ĺ������Ǽ���������һ����Ʒ����index+1 ��
�߽磺
��N����Ʒ�����ǹ���ó���һ�����ظ��ģ������ķ���������Ʒ��һ���Ӽ���
��ʱӦ�ü��鷽���Ƿ�Ϸ��������С��V�������Ҹ����ܼ�ֵ�����ֵ��

index����ǰҪ���ǵ���Ʒ��
nowW����ǰ��ѡ��Ʒ���������
nowC����ǰ��ѡ��Ʒ���ܼ�ֵ��
*/

void DFS(int index, int nowW, int nowC) {
    if (index == N) {
        if (nowW <= V && nowC > MaxValue) {
            MaxValue = nowC;
            ans = temp;
        }
        return;
    }
    DFS(index + 1, nowW, nowC);  // ��ѡ index ��Ʒ��

    temp.data[temp.len++] = index;
    DFS(index + 1, nowW + W[index], nowC + C[index]);  // ѡ index ��Ʒ��
    --temp.len;
}

/*
��֦�汾��
*/

void DFS2(int index, int nowW, int nowC) {
    if (index == N) {
        return;  // ע�⣺ÿѡһ����Ʒ�ͻ��������ֵ�������ǵ�һ���������������ٸ��¡�
                 // �ʴ˴����ظ��¡�
    }
    DFS2(index + 1, nowW, nowC);  // ��ѡ�����������������ø��£�����indexҪ���¡�
    /*
    ��֦�߼���
    ���߲��֮ǰ�����ж�һ����������Ƿ���û�н���ģ�
    ����Ԥ�У�������������ѡ����᲻��Υ������������
    */
    if (nowW + W[index] <= V) {
        if (nowC + C[index] > MaxValue) { MaxValue = nowC + C[index]; }
        DFS2(index + 1, nowW + W[index], nowC + C[index]);
    }
}

void Solve1(void) {
    int i;
    scanf("%d%d", &N, &V);
    for (i = 0; i < N; ++i) {
        scanf("%d", &W[i]);
    }
    for (i = 0; i < N; ++i) {
        scanf("%d", &C[i]);
    }
    DFS(0, 0, 0);
    printf("%d\n", MaxValue);
    for (i = 0; i < ans.len; ++i) {
        printf("%d%s", ans.data[i], i == ans.len - 1 ? "\n" : " ");
    }
}
