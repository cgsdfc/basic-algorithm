/*
题目描述
给出年分m和一年中的第n天，算出第n天是几月几号。

输入
输入包括两个整数y(1<=y<=3000)，n(1<=n<=366)。

输出
可能有多组测试数据，对于每组数据，按
yyyy-mm-dd的格式将输入中对应的日期打印出来。

样例输入 Copy
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
