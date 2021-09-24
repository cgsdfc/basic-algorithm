#include <algorithm>
#include <cstring>
#include <iostream>
#include <vector>
using namespace std;
/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

/*
把字符串单独保留在一个数组中，用id表示学生，这样在最后的排序
中可以节省时间，避免字符串的大量移动。
*/

#define MAXK (2500 + 5)
struct Student {
  char name[10];
};

bool cmp(Student a, Student b) { return strcmp(a.name, b.name) < 0; }

vector<Student> course[MAXK];

void Add(int cid, Student stu) { course[cid].push_back(stu); }

void Print(int cid) {
  vector<Student> &c = course[cid];
  printf("%d %d\n", cid, c.size());
  sort(c.begin(), c.end(), cmp);
  for (int i = 0; i < c.size(); ++i) {
    printf("%s\n", c[i].name);
  }
}

int main(int argc, char **argv) {
  int N, K;
  scanf("%d%d", &N, &K);
  for (int i = 0; i < N; ++i) {
    Student s;
    int num;
    scanf("%s%d", s.name, &num);
    for (int j = 0; j < num; ++j) {
      int cid;
      scanf("%d", &cid);
      Add(cid, s);
    }
  }
  for (int i = 0; i < K; ++i) {
    int cid = i + 1;
    Print(cid);
  }
  return 0;
}
