#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

int N;
int sum = 0;

/*
F��һ������Ҷ�ӽڵ�����

һ���ڵ��ֵN�ǵ�ǰʣ�µ��ǹ�������N=0������Ҷ�ӽڵ㡣
������N���ڵ���2�������������ӣ�һ����N-1��һ����N-2��
��N==1����ֻ��һ�����ӣ�0.
F(N)��N������Ҷ�ӽڵ�Ĺ�ϵ��û����ȷ����ѧ����ʽ��
*/
void F(int n) {
    if (n == 0) {
        ++sum;
        return;
    }
    if (n >= 2) { F(n - 2); }
    assert(n >= 1);
    F(n - 1);
}
int main(int argc, char* argv[]) {
    while (scanf("%d", &N) != EOF) {
        sum = 0;
        F(N);
        printf("%d\n", sum);
    }
    return 0;
}
