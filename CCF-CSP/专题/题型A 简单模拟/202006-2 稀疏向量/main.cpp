#include <cstdio>
//#include <algorithm>
// ע�ⲻ��Ҫ������Ŀ��֤index����
using namespace std;

// ���ݷ�Χ������int������ll֮�ڡ�
typedef long long ll;

struct Node {
  ll index;
  ll value;
};

#define MAXL (5 * 100000 + 5)

// ������������С��N�޹ء�
struct Vector {
  Node data[MAXL];
  int len;
} a, b;

void Read(Vector &a) {
  for (int i = 0; i < a.len; ++i) {
    scanf("%lld%lld", &a.data[i].index, &a.data[i].value);
  }
}

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

int main(int argc, char **argv) {
  ll ans = 0;
  int N;
  scanf("%d%d%d", &N, &a.len, &b.len);
  Read(a);
  Read(b);
  // ʵ�ʵ�������int�ڡ�
  int i = 0;
  int j = 0;
  while (i < a.len && j < b.len) {
    if (a.data[i].index == b.data[j].index) {
      ans += a.data[i].value * b.data[j].value;
      ++i;
      ++j;
    } else if (a.data[i].index < b.data[j].index) {
      ++i;
    } else {
      ++j;
    }
  }
  printf("%lld\n", ans);

  return 0;
}
