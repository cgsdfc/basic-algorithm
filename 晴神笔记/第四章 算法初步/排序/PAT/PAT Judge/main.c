#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

// Nr of User
#define MAXN (10000 + 5)
// Nr of Problems
#define MAXK (5 + 5)
// Nr of Submissions
#define MAXM (100000 + 5)

/*
��û���ύ���������-��
���ύ���ǵ÷�-1������0�֡�
û���ύ�����ߵ÷�Ϊ-1���ټ����ܷ�ʱ��������0�֡�
ֻ����һ���ύ���Ҳ�Ϊ-1�֣���μ�����
���μ������������һ�ⶼû���ύ����һ�ⶼû��ͨ����������
*/
typedef struct User {
  int id; // 5 dig, 1-N
  /*
  ĳ����ύ״̬��
  0��û���ύ��
  -1���ύ���Ǳ���ʧ�ܡ�
  1���ύ�ұ�����ˡ�
  */
  int submi[MAXK];
  int score[MAXK]; // �������յ÷�
  int total;       // �����ܷ�
  int perf;        // ������Ŀ����
  int valid;
} User;

User usr[MAXN];
int tot[MAXK]; // ÿ����Ŀ���ܷ֡�

int CMP(const void *_a, const void *_b) {
  User *a = (User *)_a;
  User *b = (User *)_b;
  if (a->total != b->total) {
    return b->total - a->total;
  }
  if (a->perf != b->perf) {
    return b->perf - a->perf;
  }
  return a->id - b->id;
}

int main(int argc, char *argv[]) {
  int N, K, M;
  int i;
  int num; // valid ������
  int r;

  freopen("./in.txt", "r", stdin);

  scanf("%d%d%d", &N, &K, &M);
  /*
  ע���±��1��ʼ��
  */
  for (i = 1; i <= K; ++i) {
    scanf("%d", &tot[i]);
  }

  while (M--) {
    int uid, pid, score;
    User *u;

    scanf("%d%d%d", &uid, &pid, &score);
    u = &usr[uid];
    u->id = uid;
    u->submi[pid] = (score == -1 ? -1 : 1);
    if (score != -1) {
      // ��ͨ��������ύ����valid��
      u->valid = 1;
    }
    /*
    ���������������ٶ����ύ��ʱ����㣬��Ϊһ���˿��Զ���������⣬
    �������Ͳ��ԣ�Ҫ�жϵ�һ�Σ���������������ÿ�������score���ټ���perf��
    */
    //		if (score == tot[pid]) {
    //			++u->perf;
    //		}
    if (u->score[pid] < score) {
      u->score[pid] = score;
    }
  }

  num = 0;
  /*
  ʵ�ʷ��֣�����ѭ���ڵĲ���Ҫ��Щ��������User����Ĳ������Ը���Щ��
  ������ʱ���١�
  */
  for (i = 1; i <= N; ++i) {
    int j;
    User *u = &usr[i];

    if (!u->valid) {
      continue;
    }
    for (j = 1; j <= K; ++j) {
      u->total += u->score[j];
      if (u->score[j] == tot[j]) {
        u->perf++;
      }
    }
    usr[num++] = *u;
  }
  // �±��uid�Ѿ�û���˶�Ӧ��ϵ��
  qsort(usr, num, sizeof(User), CMP);
  r = 1;
  for (i = 0; i < num; ++i) {
    int j;
    if (i > 0 && usr[i].total != usr[i - 1].total) {
      r = i + 1;
    }
    // rank user_id total_score s[1] ... s[K]
    printf("%d %05d %d", r, usr[i].id, usr[i].total);
    for (j = 1; j <= K; ++j) {
      if (usr[i].submi[j] != 0) {
        printf(" %d", usr[i].score[j]);
      } else {
        printf(" -");
      }
    }
    putchar('\n');
  }
  return 0;
}
