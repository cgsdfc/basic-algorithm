#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

typedef struct Record {
    char name[25];
    int mon, dd, hh, mm;
    // 1 for online, 0 for offline.
    int on;
} Record;

#define MAXN 1010

/*
只过了第一个测试点，估计是资费计算的逻辑有些问题，但是计算的方法和书上是一样的。
*/

Record rec[MAXN];
Record valid[MAXN];
int toll[25];

int CMP(const void* _a, const void* _b) {
    Record* a = (Record*) _a;
    Record* b = (Record*) _b;
    // 用户名按字典序。
    int cmp = strcmp(a->name, b->name);
    if (cmp) return cmp;
    // 时间按照时间顺序。
    if (a->mon != b->mon) return a->mon - b->mon;
    if (a->dd != b->dd) return a->dd - b->dd;
    if (a->hh != b->hh) return a->hh - b->hh;
    return a->mm - b->mm;
}

void PrintGroup(int m) {
    // 处理头部。
    int total = 0;
    int k;

    printf("%s %02d\n", valid[0].name, valid[0].mon);
    for (k = 0; k < m; k += 2) {
        int mins = 0;
        int cost = 0;
        Record a = valid[k], b = valid[k + 1];

        printf("%02d:%02d:%02d %02d:%02d:%02d", a.dd, a.hh, a.mm, b.dd, b.hh, b.mm);
        while (a.dd < b.dd || a.hh < b.hh || a.mm < b.mm) {
            cost += toll[a.hh];
            ++mins;
            ++a.mm;
            if (a.mm >= 60) {
                a.mm = 0;
                ++a.hh;
            }
            if (a.hh >= 24) {
                a.hh = 0;
                ++a.dd;
            }
        }
        printf(" %d $%.2f\n", mins, cost / 100.0);
        total += cost;
    }
    // 处理尾部。
    // 到达了一个人的最后一条记录。
    printf("Total amount: $%.2f\n", total / 100.0);
}

void Print(int n) {
    int i, j;

    // 外层循环枚举每一个人。
    for (j = 0; j < n;) {
        int m = 0;
        const char* name = rec[j].name;
        /*
        如果一个用户没有合法记录，则该用户的任何信息都不能输出。
        */
        for (i = j; i < n && 0 == strcmp(name, rec[i].name);) {
            if (i != n - 1 && rec[i].on && !rec[i + 1].on) {
                // 一对合法的记录是连续的两条，分别是online和offline。
                valid[m++] = rec[i];
                valid[m++] = rec[i + 1];
                i += 2;
            } else {
                // 一条非法记录。
                ++i;
            }
        }
        j = i;
        if (m) { PrintGroup(m); }
    }
}

int main(int argc, char* argv[]) {
    int n;
    int i;
    int j;

    freopen("./in.txt", "r", stdin);

    for (i = 0; i < 24; ++i) {
        scanf("%d", &toll[i]);
    }
    scanf("%d", &n);
    for (i = 0; i < n; ++i) {
        char buf[10];
        scanf("%s %d:%d:%d:%d %s", rec[i].name, &rec[i].mon, &rec[i].dd, &rec[i].hh, &rec[i].mm, buf);
        rec[i].on = (0 == strcmp(buf, "on-line"));
    }
    qsort(rec, n, sizeof(Record), CMP);

    //	for (i=0;i<n;++i) {
    //		Record r=rec[i];
    //		printf("%s %02d:%02d:%02d %s\n", r.name,
    // r.dd,r.hh,r.mm,(r.on?"online":"offline"));
    //	}

    Print(n);

    return 0;
}
