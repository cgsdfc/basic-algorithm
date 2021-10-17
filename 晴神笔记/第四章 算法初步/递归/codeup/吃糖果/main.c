#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

int N;
int sum = 0;

/*
F是一棵树的叶子节点数。

一个节点的值N是当前剩下的糖果数，若N=0，则是叶子节点。
否则，若N大于等于2，则有两个孩子，一个是N-1，一个是N-2，
若N==1，则只有一个孩子，0.
F(N)和N是树和叶子节点的关系，没有明确的数学递推式。
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
