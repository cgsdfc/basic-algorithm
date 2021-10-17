#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

// 最大记录数
#define MAXN 10005

typedef struct Record {
    char id[10];
    int time;
    // 1 for in, 0 for out.
    int in;
} Record;

int N, K;

//所有记录。后用来保存所有合法记录。
Record records[MAXN];
// 每一个车，及其总时间。
Record cars[MAXN];

// 用来保留合法记录的排序。先按车牌聚类，然后按时间从小到大排列。
int CMP(const void* _a, const void* _b) {
    Record *a = (Record*) _a, *b = (Record*) _b;
    int cmp = strcmp(a->id, b->id);
    if (cmp) return cmp;
    return a->time - b->time;
}

// 用来对时间排序，使得查询时间降至O(N)。
int CMP2(const void* _a, const void* _b) {
    Record *a = (Record*) _a, *b = (Record*) _b;
    return a->time - b->time;
}

// 用于输出停车最久的车的比较函数。先按time从大到小，再按id从小到大。
int CMP3(const void* _a, const void* _b) {
    Record *a = (Record*) _a, *b = (Record*) _b;
    if (a->time != b->time) { return b->time - a->time; }
    return strcmp(a->id, b->id);
}

int To(int hh, int mm, int ss) {
    return ss + mm * 60 + hh * 3600;
}

int main(int argc, char* argv[]) {
    int num = 0;
    int ncars = 0;
    int i = 0;
    int j = 0;
    int time;

    freopen("./in.txt", "r", stdin);

    scanf("%d%d", &N, &K);
    for (i = 0; i < N; ++i) {
        int hh, mm, ss;
        char buf[5];

        scanf("%s %d:%d:%d %s", records[i].id, &hh, &mm, &ss, buf);
        records[i].in = (strcmp(buf, "in") == 0);
        records[i].time = To(hh, mm, ss);
    }

    // 保留合法的记录对。
    qsort(records, N, sizeof(Record), CMP);
    i = 0;
    while (i < N) {
        int j = i;
        // 一个车的停车时间总和。
        int sum = 0;
        // 枚举一辆车的所有合法记录。
        while (j < N && strcmp(records[i].id, records[j].id) == 0) {
            // 注意，内层循环枚举一个车的所有记录，外层循环枚举所有车，
            // 在寻找合法记录时，必须保证两条记录同属一车。
            if (j != N - 1 && strcmp(records[j].id, records[j + 1].id) == 0 && records[j].in &&
                !records[j + 1].in) {
                // 得到一个车的两条合法记录。
                // 在同一时刻不能又出又进，故dur不可能为0.
                int dur = records[j + 1].time - records[j].time;
                /*
                实测发现，第四个点，加上assert后，运行时错误，不加assert则超时，
                说明dur有时为0或负数。dur出现非正数的原因是枚举一个车的所有记录时越界
                到下一辆车了。
                */
                assert(dur > 0);
                sum += dur;
                records[num++] = records[j];
                records[num++] = records[j + 1];
                j += 2;
            } else {
                j++;
            }
        }
        // 内层循环也实现了对一个车的多个记录的去重，所以cars里面的车不重复。
        if (sum) {
            // 记录一个车的总停车时间。
            Record r = records[i];
            r.time = sum;
            cars[ncars++] = r;
        }
        i = j;
    }
    assert(num > 0);
    // 按记录的时间顺序排列。
    qsort(records, num, sizeof(Record), CMP2);
    /*
    对每个查询时间T，找到第一个大于T的时间的记录，同时累计车的数量。
    注意到T是递增的，因此只需要扫描一遍即可。 如果对每一个T去遍历所有记录，则
    会超时。优化前的复杂度时O(T*N)，优化后时O(N)。 若输入的T不是有序的，则可以每次
    用二分查找，复杂度为O(T*logN)。
    */
    //
    //	for (i=0;i<num;++i) {
    //		Record r=records[i];
    //		printf("%s %d:%d:%d %d\n", r.id, r.time/3600, r.time%3600/60,
    // r.time%60, r.in);
    //	}

    j = 0;
    int n = 0;
    while (K--) {
        int hh, mm, ss;
        int time;

        scanf("%d:%d:%d", &hh, &mm, &ss);
        //		printf("%d:%d:%d\n", hh,mm,ss);

        time = To(hh, mm, ss);
        // 累计到time为止的车数。
        for (; j < num && records[j].time <= time; j++) {
            n += (records[j].in ? 1 : -1);
        }
        printf("%d\n", n);
    }

    // 计算每条记录的时间间隔，排序，得出停的最久的车。
    qsort(cars, ncars, sizeof(Record), CMP3);
    time = cars[0].time;
    for (i = 0; i < ncars && cars[i].time == time; ++i) {
        printf("%s ", cars[i].id);
    }

    printf("%02d:%02d:%02d\n", time / 3600, time % 3600 / 60, time % 60);
    return 0;
}
