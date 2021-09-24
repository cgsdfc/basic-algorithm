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
若没有提交过，则输出-。
若提交但是得分-1，则当作0分。
没有提交，或者得分为-1，再计算总分时，都算作0分。
只有有一题提交并且不为-1分，则参加排序。
不参加排序的条件是一题都没有提交或者一题都没有通过编译器。
*/
typedef struct User {
  int id; // 5 dig, 1-N
  /*
  某题的提交状态：
  0：没有提交。
  -1：提交但是编译失败。
  1：提交且编译过了。
  */
  int submi[MAXK];
  int score[MAXK]; // 各题最终得分
  int total;       // 各题总分
  int perf;        // 满分题目数量
  int valid;
} User;

User usr[MAXN];
int tot[MAXK]; // 每道题目的总分。

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
  int num; // valid 人数。
  int r;

  freopen("./in.txt", "r", stdin);

  scanf("%d%d%d", &N, &K, &M);
  /*
  注意下标从1开始。
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
      // 有通过编译的提交，则valid。
      u->valid = 1;
    }
    /*
    完美解题数不能再读入提交的时候计算，因为一个人可以多次完美解题，
    则数量就不对，要判断第一次，或者再下面计算出每题的最终score后再计算perf。
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
  实际发现，输入循环内的操作要简单些，而遍历User数组的操作可以复杂些，
  这样耗时更少。
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
  // 下标和uid已经没有了对应关系。
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
