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

// ���������������
int count[MAXA];
// �п��ܱ������������
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
�Ȱ������˳���������O(nlogn)��
Ȼ���ÿ����ѯ��ɸ���������䷶Χ�ڵ��ˣ�ֱ�������ÿ����ѯO(n)��
�ܵ��� max{O(nlogn),O(kn)}��
���ǵ� k=10e3, n=10e5���ʸ��Ӷ���O(nlogn). ����ͨ����

����ÿһ����ѯ����һ��������������Ӷ�Ҳ��O(nlogn)�����ǳ����ϴ�
��ǰ�߳�����1��������k�����ᳬʱ��

����һ��Ԥ���������Խ��Ͳ�ѯ���Ӷȡ�
ע�⵽��M��������100����ÿ�β�ѯ���������100�ˣ���ͬһ��������˲����������100�ˡ�
�����ͬ������˰��Ƹ����򣬳���100�����˿��Բ����ǡ������ͰѲ�ѯ���Ӷȴ�O(n)����O(100*200)��
��һ�����ܵ�200�������ÿ�������100�ˣ���n�޹أ�����ǳ�������O(1)��
ÿ����ѯΪ����ʱ����Ȼ���������Ӷ�û��Ӱ�죬����ʵ������ʱ����󽵵͡�
Ԥ����ĸ��Ӷ�ΪO(n)

ʵ�⣬�ܰ�����������һ��ĺ�ʱ��300ms����150ms��
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

    // Ԥ����
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
