#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

const char WeekNames[][20] = {{},         "Monday", "Tuesday",  "Wednesday",
                              "Thursday", "Friday", "Saturday", "Sunday"};
const char MonNames[][20] = {{},    "Jan", "Feb", "Mar", "Apr", "May", "Jun",
                             "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
const int MonDays[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

int FindMon(char name[]) {
    int i;
    for (i = 1; i <= 12; ++i) {
        if (memcmp(MonNames[i], name, 3) == 0) { return i; }
    }
    assert(0);
    return -1;
}

typedef struct Time {
    int yy, mm, dd;
} Time;

// 记住1年1月1日是星期一，所以求星期几的题目，都以此为参照日。
const Time today = {1, 1, 1};
const int now = 1;

int IsLeap(int y) {
    return (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0);
}

int Less(Time a, Time b) {
    return a.yy < b.yy || a.mm < b.mm || a.dd < b.dd;
}

int Dis(Time a, Time b) {
    // a <= b
    int dis = 0;
    while (Less(a, b)) {
        int mds = MonDays[a.mm] + (a.mm == 2 && IsLeap(a.yy));

        ++a.dd;
        if (a.dd == mds + 1) {
            a.dd = 1;
            ++a.mm;
        }
        if (a.mm == 13) {
            a.mm = 1;
            ++a.yy;
        }
        ++dis;
    }
    return dis;
}

int Weekday(Time b) {
    int dis;
    dis = Dis(today, b);
    return dis % 7 + 1;
}

/*
21 December 2012
5 January 2013

Friday
Saturday
*/

void Print(Time t) {
    printf("%d %d %d\n", t.yy, t.mm, t.dd);
}

/*
求某年某月某日是星期几。

先记住：0001:01:01 是星期一。
然后任何日期都在此日期之后，就不需要区分是昨天还是明天了，
因为这个特殊日期是公历的第一天。
之后只需要计算待求日期距离这一天有多少天即可。
*/
int main(int argc, char* argv[]) {
    Time t;
    char mon[20];

    //	freopen("./in.txt", "r", stdin);

    while (scanf("%d%s%d", &t.dd, mon, &t.yy) != EOF) {
        int dis;
        int ans;

        t.mm = FindMon(mon);
        //		Print(t);

        ans = Weekday(t);
        //		printf("%d\n", ans);
        if (1 <= ans && ans <= 7)
            printf("%s\n", WeekNames[ans]);
        else
            abort();
    }
    return 0;
}
