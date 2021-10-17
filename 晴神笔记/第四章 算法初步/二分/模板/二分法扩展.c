#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

/*
���ַ�����Ľ���ֵ��
�躯��f������[left,right]�ǵ��������ģ����ǵݼ���ͬ����
������������һ������������ö��ַ������Ľ���ֵ��
*/

const double eps = 1e-5;

double f(double x) {
    return x * x - 2;  // ����f��ֵ��
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
