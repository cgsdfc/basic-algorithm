#include <algorithm>
#include <cstdio>
using namespace std;

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

/*
���ƺϲ������������С�
*/

struct Interval {
  int L, R;
  int len() { return R - L; }
  bool operator<(Interval a) {
    if (L != a.L)
      return L < a.L;
    return R < a.R;
  }
};

#define MAXN 2005
int N;
Interval A[MAXN], B[MAXN];

void Read(Interval a[]) {
  for (int i = 0; i < N; ++i) {
    scanf("%d%d", &a[i].L, &a[i].R);
  }
}

// a����b��
bool Include(Interval &a, Interval &b) { return a.L <= b.L && b.R <= a.R; }

// a < b
bool Less(Interval &a, Interval &b) { return a.R <= b.L; }

bool Overlap(Interval &a, Interval &b) { return (a.L <= b.L && b.L <= a.R); }

int Compute(Interval a, Interval b) {
  int L = max(a.L, b.L);
  int R = min(a.R, b.R);
  return max(0, R - L);
}

void Solve() {
  // ��������С������ֱ����ƽ�����Ӷ��㷨��
  int ans = 0;
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) {
      int len = Compute(A[i], B[j]);
      ans += len;
    }
  }
  printf("%d\n", ans);
}

/*
���Ը��ӶȵĽⷨ�����ǹ鲢�߼��Ƚϸ��ӡ�
ʹ��2-pointer����ע��ָ����Ƶ�������
һ��ָ����Ƶ������ǣ�

��ǰ��ָ���䲻��������һ�����еĵ�ǰָ��֮����κ����䷢��������

������ָ�붼������������ʱ���ƶ�����һ�����ɡ�

���������ϴ�ʱ������㷨�������ơ�
*/
void Solve2() {
  int ans = 0;
  int i = 0, j = 0;

  while (i < N && j < N) {
    Interval a = A[i], b = B[j];
    int len = Compute(a, b);
    ans += len;
    if (!len) {
      // �������䲻�ཻ��
      if (a.R <= b.L) {
        // a ����ߡ�
        ++i;
      } else {
        // a ���ұߡ�
        ++j;
      }
    } else {
      if (len == a.len()) {
        // a������b��
        ++i;
      } else if (len == b.len()) {
        // b������a��
        ++j;
      } else if (a.L < b.L) {
        // ab�ʽ���״��
        // a����ߡ�
        ++i;
      } else {
        // a���ұߡ�
        ++j;
      }
    }
  }
  printf("%d\n", ans);
}

int main(int argc, char **argv) {
  scanf("%d", &N);
  Read(A);
  Read(B);
  Solve2();
  return 0;
}
