#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

/*
二分法求根的近似值。
设函数f在区间[left,right]是单调递增的（若是递减，同理），
且在区间内有一个根，则可以用二分法求它的近似值。
*/

const double eps = 1e-5;

double f(double x) {
    return x * x - 2;  // 计算f的值。
}

double solve(double left, double right) {
    double mid;
    while (right - left > eps) {
        mid = (left + right) / 2;
        if (f(mid) > 0) {
            right = mid;
        } else {
            left = mid;
        }
    }
    return mid;
}
