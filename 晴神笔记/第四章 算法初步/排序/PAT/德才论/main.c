#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

/*
��һ�࣬�²ž�ȫ���·ֲŷ־�������H��
�ڶ��࣬��ʤ�ţ��ŷֲ������·ֵ���H��
�����࣬�ŵ¼������²ŷ־�����H�����·ָ��ڲŷ֡�
�����࣬�²ŷ־�����L��������������ࡣ
�����࣬�·ֻ�ŷֲ�����L����¼ȡ��
*/

int L, H;

typedef struct Student {
  char id[10];
  int de;
  int cai;
} Student;

#define MAXN 100010

Student stu[MAXN];

int Kind(Student *t) {
  if (t->de >= H && t->cai >= H)
    return 1;
  if (t->de >= H)
    return 2;
  if (t->de >= t->cai)
    return 3;
  return 4;
}

int Sum(Student *t) { return t->de + t->cai; }

int CMP(const void *_a, const void *_b) {
  Student *a = (Student *)_a;
  Student *b = (Student *)_b;
  int ak, bk;
  int as, bs;

  // ����ӵ͵��ߡ�
  ak = Kind(a);
  bk = Kind(b);
  if (ak != bk) {
    return ak - bk;
  }
  // ���ִܷӸߵ��͡�
  as = Sum(a);
  bs = Sum(b);
  if (as != bs) {
    return bs - as;
  }
  // ���·ִӸߵ��͡�
  if (a->de != b->de) {
    return b->de - a->de;
  }
  // ��׼��֤�ӵ͵��ߡ�
  return strcmp(a->id, b->id);
}

/*
14 60 80
10000001 64 90
10000002 90 60
10000011 85 80
10000003 85 80
10000004 80 85
10000005 82 77
10000006 83 76
10000007 90 78
10000008 75 79
10000009 59 90
10000010 88 45
10000012 80 100
10000013 90 99
10000014 66 60
*/

int main(int argc, char *argv[]) {
  int i;
  int M = 0;
  int N;

  scanf("%d%d%d", &N, &L, &H);
  for (i = 0; i < N; ++i) {
    // �����ߵ��˶�����
    Student t;
    scanf("%s%d%d", t.id, &t.de, &t.cai);
    if (t.de >= L && t.cai >= L) {
      stu[M++] = t;
    }
  }
  printf("%d\n", M);
  qsort(stu, M, sizeof(Student), CMP);
  for (i = 0; i < M; ++i) {
    printf("%s %d %d\n", stu[i].id, stu[i].de, stu[i].cai);
  }
  return 0;
}
