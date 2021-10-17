#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

// ����¼��
#define MAXN 10005

typedef struct Record {
    char id[10];
    int time;
    // 1 for in, 0 for out.
    int in;
} Record;

int N, K;

//���м�¼���������������кϷ���¼��
Record records[MAXN];
// ÿһ������������ʱ�䡣
Record cars[MAXN];

// ���������Ϸ���¼�������Ȱ����ƾ��࣬Ȼ��ʱ���С�������С�
int CMP(const void* _a, const void* _b) {
    Record *a = (Record*) _a, *b = (Record*) _b;
    int cmp = strcmp(a->id, b->id);
    if (cmp) return cmp;
    return a->time - b->time;
}

// ������ʱ������ʹ�ò�ѯʱ�併��O(N)��
int CMP2(const void* _a, const void* _b) {
    Record *a = (Record*) _a, *b = (Record*) _b;
    return a->time - b->time;
}

// �������ͣ����õĳ��ıȽϺ������Ȱ�time�Ӵ�С���ٰ�id��С����
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

    // �����Ϸ��ļ�¼�ԡ�
    qsort(records, N, sizeof(Record), CMP);
    i = 0;
    while (i < N) {
        int j = i;
        // һ������ͣ��ʱ���ܺ͡�
        int sum = 0;
        // ö��һ���������кϷ���¼��
        while (j < N && strcmp(records[i].id, records[j].id) == 0) {
            // ע�⣬�ڲ�ѭ��ö��һ���������м�¼�����ѭ��ö�����г���
            // ��Ѱ�ҺϷ���¼ʱ�����뱣֤������¼ͬ��һ����
            if (j != N - 1 && strcmp(records[j].id, records[j + 1].id) == 0 && records[j].in &&
                !records[j + 1].in) {
                // �õ�һ�����������Ϸ���¼��
                // ��ͬһʱ�̲����ֳ��ֽ�����dur������Ϊ0.
                int dur = records[j + 1].time - records[j].time;
                /*
                ʵ�ⷢ�֣����ĸ��㣬����assert������ʱ���󣬲���assert��ʱ��
                ˵��dur��ʱΪ0������dur���ַ�������ԭ����ö��һ���������м�¼ʱԽ��
                ����һ�����ˡ�
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
        // �ڲ�ѭ��Ҳʵ���˶�һ�����Ķ����¼��ȥ�أ�����cars����ĳ����ظ���
        if (sum) {
            // ��¼һ��������ͣ��ʱ�䡣
            Record r = records[i];
            r.time = sum;
            cars[ncars++] = r;
        }
        i = j;
    }
    assert(num > 0);
    // ����¼��ʱ��˳�����С�
    qsort(records, num, sizeof(Record), CMP2);
    /*
    ��ÿ����ѯʱ��T���ҵ���һ������T��ʱ��ļ�¼��ͬʱ�ۼƳ���������
    ע�⵽T�ǵ����ģ����ֻ��Ҫɨ��һ�鼴�ɡ� �����ÿһ��Tȥ�������м�¼����
    �ᳬʱ���Ż�ǰ�ĸ��Ӷ�ʱO(T*N)���Ż���ʱO(N)�� �������T��������ģ������ÿ��
    �ö��ֲ��ң����Ӷ�ΪO(T*logN)��
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
        // �ۼƵ�timeΪֹ�ĳ�����
        for (; j < num && records[j].time <= time; j++) {
            n += (records[j].in ? 1 : -1);
        }
        printf("%d\n", n);
    }

    // ����ÿ����¼��ʱ���������򣬵ó�ͣ����õĳ���
    qsort(cars, ncars, sizeof(Record), CMP3);
    time = cars[0].time;
    for (i = 0; i < ncars && cars[i].time == time; ++i) {
        printf("%s ", cars[i].id);
    }

    printf("%02d:%02d:%02d\n", time / 3600, time % 3600 / 60, time % 60);
    return 0;
}
