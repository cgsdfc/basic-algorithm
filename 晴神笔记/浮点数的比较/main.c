#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

/*
�Ƚϸ�����

����������Ҫ�Ƚ�ʱ��������������㣬���п�����Ϊ���ȶ�ʧ��ʹ�� == �Ƚϴ���
������Ϊ������6�й�ϵ�Ƚ����������Ҫ������
*/

// ��Сֵ�Ķ��壬ȡ10��-8�η���
const double eps = 1e-8;

/*
�Ƚ����������������������ڡ�
*/

// a �������� (b-eps, b+eps)������Ϊ a == b ��
int Equal(double a, double b) {
    return fabs(a - b) < eps;
}

// a �������� (b+eps, +inf)������Ϊ a > b ��
int More(double a, double b) {
    return a - b > eps;
}

int Less(double a, double b) {
    return a - b < -eps;
}

// a ���ڵ��� b������ �� a С�� b ��
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

    // ע�� 1/2 == 0 Ҫ�õ� 0.5�������� 1.0/2 ��
    assert(Equal(6 * asin(1.0 / 2), 4 * asin(sqrt(2) / 2)));
    return 0;
}
