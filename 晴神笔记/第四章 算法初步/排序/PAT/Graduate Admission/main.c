#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

// ־Ը��
#define MAXK 6
// ѧУ��
#define MAXM 110
// ѧ����
#define MAXN 40005

typedef struct App {
    int ge;
    int gi;
    int id;
    int choice[MAXK];
    // ��һ����ͬһ��ѧУ¼ȡ���ˡ�
    struct App* next;
} App;

typedef struct School {
    int quo;
    // �����˱�¼ȡ�ˡ�
    int num;
    // ¼ȡ����
    App* admit;
} School;

App app[MAXN];
School school[MAXM];
int admits[MAXN];

int Total(App* a) {
    return a->ge + a->gi;
}

int CMP2(const void* _a, const void* _b) {
    return *(int*) _a - *(int*) _b;
}

int CMP(const void* _a, const void* _b) {
    App* a = (App*) _a;
    App* b = (App*) _b;
    if (Total(a) != Total(b)) { return Total(b) - Total(a); }
    return b->ge - a->ge;
}

// Tie�������ˣ�����������ͬ��
int Tie(App* a, App* b) {
    return Total(a) == Total(b) && a->ge == b->ge;
}

// ����ѧ��a��ѧУs¼ȡ�Ĺ�ϵ��
void Admit(App* a, School* s) {
    s->num++;
    if (s->admit) {
        a->next = s->admit;
        s->admit = a;
    } else {
        s->admit = a;
    }
}

int main(int argc, char* argv[]) {
    int N, M, K;
    int i;

    freopen("./in.txt", "r", stdin);

    scanf("%d%d%d", &N, &M, &K);
    for (i = 0; i < M; ++i) {
        // �������ѧУ�����ƻ���
        scanf("%d", &school[i].quo);
        //		printf("q=%d\n",school[i].quo);
    }
    for (i = 0; i < N; ++i) {
        // ����ѧ���Ŀ��Գɼ��Լ�־Ը��
        int j;

        app[i].id = i;
        scanf("%d%d", &app[i].ge, &app[i].gi);
        for (j = 0; j < K; ++j) {
            scanf("%d", &app[i].choice[j]);
        }
    }

    qsort(app, N, sizeof(App), CMP);

    //	for (i=0;i<N;++i) {
    //		int j;
    //		printf("id=%d ge=%d gi=%d\n", app[i].id, app[i].ge, app[i].gi);
    //		for (j=0;j<K;++j) {
    //			printf("%d ", app[i].choice[j]);
    //		}
    //		puts("");
    //	}
    //
    for (i = 0; i < N; ++i) {
        int j;
        App* a = &app[i];

        for (j = 0; j < K; ++j) {
            int sid = a->choice[j];
            School* sch = &school[sid];
            // ע�⣬һ����¼ȡ����������ѭ����
            if (sch->quo > 0) {
                // ����¼ȡ�����
                --sch->quo;
                Admit(a, sch);
                //				printf("admit %d to %d\n", a->id, sid);
                break;
            } else {
                assert(sch->admit);
                if (Tie(sch->admit, a)) {
                    // ������������ѧУ���һ��¼ȡ������ͬ���Ƹ�¼ȡ��
                    Admit(a, sch);
                    //					printf("admit %d to %d\n", a->id,
                    // sid);
                    break;
                }
            }
        }
    }
    // ��ӡ¼ȡ�����
    for (i = 0; i < M; ++i) {
        School* sch = &school[i];
        int num = sch->num;
        App* a = sch->admit;
        int j;

        if (!num) {
            puts("");
            continue;
        }
        for (j = 0; j < num; ++j) {
            admits[j] = a->id;
            a = a->next;
        }
        qsort(admits, num, sizeof(int), CMP2);
        for (j = 0; j < num; ++j) {
            printf("%d%s", admits[j], j == num - 1 ? "\n" : " ");
        }
    }
    return 0;
}
