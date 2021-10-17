/*
��Ŀ����
�������m��һ���еĵ�n�죬�����n���Ǽ��¼��š�

����
���������������y(1<=y<=3000)��n(1<=n<=366)��

���
�����ж���������ݣ�����ÿ�����ݣ���
yyyy-mm-dd�ĸ�ʽ�������ж�Ӧ�����ڴ�ӡ������

�������� Copy
2013 60
2012 300
2011 350
2000 211

2013-03-01
2012-10-26
2011-12-16
2000-07-29
*/

#include <stdio.h>

const int MonDays[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

int Leap(int y) {
    return (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0);
}

int GetMonDays(int yy, int mm) {
    return MonDays[mm] + (mm == 2 && Leap(yy));
}

typedef struct Time {
    int yy, mm, dd;
} Time;

Time Get(int yy, int n) {
    Time t;
    int mm = 1;
    int ds;

    while (n > (ds = GetMonDays(yy, mm))) {
        n -= ds;
        ++mm;
    }
    t.yy = yy;
    t.mm = mm;
    t.dd = n;
    return t;
}

void Print(Time t) {
    printf("%04d-%02d-%02d\n", t.yy, t.mm, t.dd);
}

int main() {
    int yy, n;

    freopen("./in.txt", "r", stdin);

    while (scanf("%d%d", &yy, &n) != EOF) {
        Time t = Get(yy, n);
        Print(t);
    }

    return 0;
}
