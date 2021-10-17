#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

/*
比较浮点数

当浮点数需要比较时，如果经过了运算，则有可能因为精度丢失而使得 == 比较错误，
必须人为修正。6中关系比较运算符都需要修正。
*/

// 极小值的定义，取10的-8次方。
const double eps = 1e-8;

/*
比较两个浮点数，把误差考虑在内。
*/

// a 落在区间 (b-eps, b+eps)，则认为 a == b 。
int Equal(double a, double b) {
    return fabs(a - b) < eps;
}

// a 落在区间 (b+eps, +inf)，则认为 a > b 。
int More(double a, double b) {
    return a - b > eps;
}

int Less(double a, double b) {
    return a - b < -eps;
}

// a 大于等于 b，就是 非 a 小于 b 。
int MoreEq(double a, double b) {
    return !Less(a, b);
}

int LessEq(double a, double b) {
    return !More(a, b);
}

int NotEq(double a, double b) {
    return !Equal(a, b);
}

int main(int argc, char* argv[]) {
    // sin(pi/4)=sqrt(2)/2
    // sin(pi/3)=sqrt(3)/2
    // sin(pi/6)=1/2
    assert(Equal(4 * asin(sqrt(2) / 2), 3 * asin(sqrt(3) / 2)));

    // 注意 1/2 == 0 要得到 0.5，必须是 1.0/2 。
    assert(Equal(6 * asin(1.0 / 2), 4 * asin(sqrt(2) / 2)));
    return 0;
}
