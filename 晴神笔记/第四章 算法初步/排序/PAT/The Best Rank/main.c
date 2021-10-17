#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

const char Map[] = "ACME";

enum {
    kA,
    kC,
    kM,
    kE,
};

typedef struct Student {
    /*
    ��Ϊ����Ҫ���id������id��β�����󣬽�Ϊ10e6�����Կ���ֱ�Ӵ洢Ϊ������
    �����ڲ���id��Ӧ��ѧ��ʱ���Ϳ���ֱ��������ɢ���ˡ�
    ���ַ����Ļ�����Ҫ���ֲ��Ҳ��ܱȽϿ졣
    */
    char id[10];
    int score[4];
    int rank[4];
    int best_rank;
    int best_subj;
} Student;

#define MAXN 2010

Student stu[MAXN];

typedef struct Info {
    int stu;
    int score;
} Info;

Info score[MAXN];

int CMP(const void* _a, const void* _b) {
    Info* a = (Info*) _a;
    Info* b = (Info*) _b;
    return b->score - a->score;
}

int CMPID(const void* _a, const void* _b) {
    Student* a = (Student*) _a;
    Student* b = (Student*) _b;
    return strcmp(a->id, b->id);
}

/*
Sample Input:
5 6
310101 98 85 88
310102 70 95 88
310103 82 87 94
310104 91 91 91
310105 85 90 90
310101
310102
310103
310104
310105
999999
Sample Output:
1 C
1 M
1 E
1 A
3 A
N/A
*/

int main(int argc, char* argv[]) {
    int n, m;
    int i;
    int j;

    scanf("%d%d", &n, &m);
    for (i = 0; i < n; ++i) {
        int sum = 0;

        scanf("%s", stu[i].id);
        for (j = 1; j <= 3; ++j) {
            int x;
            scanf("%d", &x);
            sum += x;
            stu[i].score[j] = x;
        }
        //		Ϊ�˱���ȡ���������ֶܷ�����ƽ��������Ϊ������������Ҫƽ������
        stu[i].score[kA] = sum;
    }
    // �Ը���Ŀ��������Ȼ��ͳ��������
    /*
    ��һ����ʱ���鱣��ĳ��Ŀ�ĳɼ��Ͷ�Ӧ��ѧ����
    ����󣬼���������Ȼ����������浽��Ӧѧ���Ľṹ���С�
    */
    for (i = 0; i < 4; ++i) {
        int r;
        for (j = 0; j < n; ++j) {
            // ��¼ѧ��j�ĳɼ���
            score[j].stu = j;
            score[j].score = stu[j].score[i];
        }
        qsort(score, n, sizeof(Info), CMP);

        r = 1;
        for (j = 0; j < n; ++j) {
            if (j > 0 && score[j].score != score[j - 1].score) { r = j + 1; }
            // ��������¼����Ӧ��ѧ���Ķ�Ӧ��Ŀ�ϡ�
            stu[score[j].stu].rank[i] = r;
        }
    }
    // ����ÿ���˵�best rank��Ŀ��
    // ע�⣬����ԽСԽ�á�
    /*
    �����ٲ�ѯǰ��������ѧ���Ľ�������ѯʱ��ΪO(1)��
    */
    for (i = 0; i < n; ++i) {
        int min = n + 1;
        int pos = 0;
        for (j = 0; j < 4; ++j) {
            if (stu[i].rank[j] < min) {
                min = stu[i].rank[j];
                pos = j;
            }
        }
        stu[i].best_subj = pos;
        stu[i].best_rank = min;
    }

    // ��ѧ�����鰴id���򣬽��Ͳ��ҵĸ��Ӷȡ�
    qsort(stu, n, sizeof(Student), CMPID);
    while (m--) {
        Student t, *s;
        scanf("%s", t.id);
        s = (Student*) bsearch(&t, stu, n, sizeof(Student), CMPID);
        if (!s) {
            puts("N/A");
        } else {
            //			printf("%d %d\n", s->best_rank, s->best_subj);
            printf("%d %c\n", s->best_rank, Map[s->best_subj]);
        }
    }
    return 0;
}
