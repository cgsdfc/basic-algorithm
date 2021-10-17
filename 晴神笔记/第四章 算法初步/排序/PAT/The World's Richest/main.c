#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

typedef struct Person {
    char name[10];
    int age;
    int net;
} Person;

#define MAXN 100005
#define MAXM 105
#define MAXA 205

// 各个年龄的人数。
int count[MAXA];
// 有可能被输出的人数。
Person valid[MAXM * MAXA + 5];
Person per[MAXN];

int Amax, Amin;

int InRange(int age) {
    return Amin <= age && age <= Amax;
}

int CMP(const void* _a, const void* _b) {
    Person* a = (Person*) _a;
    Person* b = (Person*) _b;

    if (a->net != b->net) { return b->net - a->net; }
    if (a->age != b->age) { return a->age - b->age; }
    return strcmp(a->name, b->name);
}

/*
先按照输出顺序进行排序，O(nlogn)。
然后对每个查询，筛掉不在年龄范围内的人，直接输出，每个查询O(n)。
总的是 max{O(nlogn),O(kn)}。
考虑到 k=10e3, n=10e5，故复杂度是O(nlogn). 可以通过。

若对每一个查询进行一次排序操作，则复杂度也是O(nlogn)，但是常数较大，
（前者常数是1，后者是k），会超时。

还有一种预处理方法可以降低查询复杂度。
注意到，M的上限是100，即每次查询输出不超过100人，则同一个年龄的人不会输出超过100人。
因此相同年龄的人按财富排序，超过100名的人可以不考虑。这样就把查询复杂度从O(n)降到O(100*200)，
即一共可能的200个年龄和每个年龄的100人，和n无关，因此是常数，即O(1)。
每个查询为常数时，虽然对整个复杂度没有影响，但是实际运行时间会大大降低。
预处理的复杂度为O(n)

实测，能把数据量最大的一组的耗时从300ms降到150ms。
*/

int main(int argc, char* argv[]) {
    int n, k;
    int i;
    int nvalid;

    freopen("./in.txt", "r", stdin);

    scanf("%d%d", &n, &k);
    for (i = 0; i < n; ++i) {
        scanf("%s%d%d", per[i].name, &per[i].age, &per[i].net);
    }
    qsort(per, n, sizeof(Person), CMP);

    // 预处理
    nvalid = 0;
    for (i = 0; i < n; ++i) {
        int age = per[i].age;
        if (count[age] < MAXM) {
            count[age]++;
            valid[nvalid++] = per[i];
        }
    }

    for (i = 0; i < k; ++i) {
        int m;
        int j;
        int num;

        scanf("%d%d%d", &m, &Amin, &Amax);
        printf("Case #%d:\n", i + 1);
        num = 0;
        for (j = 0; j < nvalid; ++j) {
            Person* p = &valid[j];
            if (InRange(p->age) && num < m) {
                ++num;
                printf("%s %d %d\n", p->name, p->age, p->net);
            }
        }
        if (!num) { puts("None"); }
    }
    return 0;
}
