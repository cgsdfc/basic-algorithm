#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

int IsLeap(int y) {
    return (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0);
}

int Month[] = {
    0,  31,  // 1
    28,      // 2
    31,      // 3
    30,      // 4
    31,      // 5
    30,      // 6
    31,      // 7
    31,      // 8
    30,      // 9
    31,      // 10
    30,      // 11
    31,      // 12
};

typedef struct Time {
    int yy, mm, dd;
} Time;

int Days(Time t) {
    int days = Month[t.mm];
    int one = (t.mm == 2 && IsLeap(t.yy));
    return days + one;
}

void Print(Time t) {
    printf("%d %d %d\n", t.yy, t.mm, t.dd);
}

Time Read(int v) {
    Time t;

    //	scanf("%d", &v);
    t.yy = v / 10000;
    t.mm = v % 10000 / 100;
    t.dd = v % 100;
    return t;
}

// 注意，codeup是多点测试。
int main(int argc, char* argv[]) {
    //	Read();
    int a1, b1, tmp;
    Time a, b;
    int res;

    //	freopen("./in.txt", "r", stdin);

    while (scanf("%d%d", &a1, &b1) != EOF) {
        if (a1 > b1) {
            tmp = a1;
            a1 = b1;
            b1 = tmp;
        }
        // 保证a小于b
        a = Read(a1);
        b = Read(b1);

        res = 1;
        while (a.yy < b.yy || a.mm < b.mm || a.dd < b.dd) {
            int mds;  // 一个月的天数
            ++a.dd;
            mds = Days(a);
            if (a.dd == mds + 1) {
                a.dd = 1;
                ++a.mm;
            }
            if (a.mm == 13) {
                a.mm = a.dd = 1;
                ++a.yy;
            }
            ++res;
        }
        printf("%d\n", res);
    }
    return 0;
}
