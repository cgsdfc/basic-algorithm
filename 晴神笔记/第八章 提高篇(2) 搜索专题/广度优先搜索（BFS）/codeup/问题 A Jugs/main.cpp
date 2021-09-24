#include <cassert>
#include <cstdio>
#include <map>
#include <queue>
//#include <unordered_map>
#include <cstring>
using namespace std;
/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

/*
灌水问题
BFS解法。
先是N个水壶，然后每个水壶有最大容量 。
有三种操作：
1. 把水壶倒空。
2. 把水壶倒满。
3. 把水壶i的水倒进j，倒水的规则是使得i空或者j满。
通过这三种操作，实现某个水壶中的水恰好为K。
*/

// 水壶数。
const int N = 2;

struct Water {
  int max;
  int now;
};

enum OP {
  EMPTY,
  FILL,
  POUR,
};

/*
题目要输出合法操作序列，所以保留操作的信息。
*/
struct Oper {
  OP op;
  int i, j;
};

/*
本题N=2，所以状态量较小，用map即可。
*/
struct Node {
  Water data[N];
  // 检查是否倒出了K升水。
  // 注意，题目的要求是B桶有K升，而不是任意一桶。
  bool OK(int K) const { return data[1].now == K; }
  /*
  字典序比较函数写错了，导致map出问题了，当一个元素不在map时，
  插入该元素后，find仍然返回end。
  以下是错误的比较函数实现，重点在判定和之后的返回语句。
  */
  bool WrongLess(const Node &a) const {
    /*
    这个逻辑错在什么地方呢？
    正确的逻辑：
    1. 找到第一个不相等的元素，比较这两个元素，而两个序列的比较由此决定。
    2. 找不到1所述的元素，说明两个序列相等。

    错误的逻辑：
    1. 找到第一个小于关系成立的元素，如果存在，则序列的小于关系成立。
    2. 找不到1所述的元素，说明小于关系不成立。

    错误之处：
    错误在于，只有第一个序列存在一个元素比第二个序列的对应元素小，小于关系就成立了，
    但事实上，小于关系取决于两个序列第一个**不相等**的元素，所以出现第一个大于的元素时，
    小于关系就已经不成立了，必须立刻返回false，而不能继续找小于的元素。
    */
    for (int i = 0; i < N; ++i) {
      if (data[i].now < a.data[i].now)
        return true;
    }
    return false;
  }

  // 字典序比较。
  friend bool operator<(const Node &a, const Node &b) {
    for (int i = 0; i < N; ++i) {
      /*
      返回的时机是出现第一个不相等元素，凡是字典序比较的，都是如此。
      时机出现时，序列的比较就等价于该元素的比较。

      事实上，POD如int，char的序列的比较，可以用memcmp实现。
      */
      if (a.data[i].now != b.data[i].now) {
        return a.data[i].now < b.data[i].now;
      }
    }
    return false;
  }
  // 返回Op是否能运行。
  bool CanDo(OP op, int i, int j) {
    switch (op) {
    case EMPTY:
      return data[i].now > 0;
    case FILL:
      return data[i].now < data[i].max;
    case POUR:
      // i => j
      return data[i].now > 0 && data[j].now < data[j].max;
    }
  }
  void Do(OP op, int i, int j) {
    assert(CanDo(op, i, j));
    int v;
    switch (op) {
    case EMPTY:
      data[i].now = 0;
      break;
    case FILL:
      data[i].now = data[i].max;
      break;
    case POUR:
      v = min(data[i].now, data[j].max - data[j].now);
      data[i].now -= v;
      data[j].now += v;
      break;
    }
    for (int i = 0; i < N; ++i) {
      assert(0 <= data[i].now && data[i].now <= data[i].max);
    }
  }
  Node(int Ca, int Cb) {
    memset(data, 0, sizeof(data));
    data[0].max = Ca;
    data[1].max = Cb;
  }
  Node() {}
  void Print() {
    printf("%d %d %d %d\n", data[0].now, data[1].now, data[0].max, data[1].max);
  }
};

/*
本题数据量较小，用map代替散列，
顺便保存操作序列，即达到此状态的最短操作序列。
不保存在Node，可以使得Node轻量化。
*/
map<Node, vector<Oper>> inq;

const char *To(int i) { return i == 0 ? "A" : "B"; }

void PrintResult(vector<Oper> &v) {
  //	printf("size %d\n", v.size());

  for (int i = 0; i < v.size(); ++i) {
    switch (v[i].op) {
    case EMPTY:
      printf("empty %s\n", To(v[i].i));
      break;
    case FILL:
      printf("fill %s\n", To(v[i].i));
      break;
    case POUR:
      printf("pour %s %s\n", To(v[i].i), To(v[i].j));
      break;
    }
  }
  puts("success");
}

void BFS(Node &init, int K) {
  queue<Node> q;
  q.push(init);
  inq[init] = vector<Oper>();

  while (!q.empty()) {
    Node p = q.front();
    q.pop();
    if (p.OK(K)) {
      PrintResult(inq[p]);
      return;
    }
    vector<Oper> next;
    for (int i = 0; i < N; ++i) {
      if (p.CanDo(EMPTY, i, 0)) {
        next.push_back({EMPTY, i, 0});
      }
      if (p.CanDo(FILL, i, 0)) {
        next.push_back({FILL, i, 0});
      }
      for (int j = i + 1; j < N; ++j) {
        if (p.CanDo(POUR, i, j)) {
          next.push_back({POUR, i, j});
        }
        if (p.CanDo(POUR, j, i)) {
          next.push_back({POUR, j, i});
        }
      }
    }
    for (int i = 0; i < next.size(); ++i) {
      Node v = p;
      v.Do(next[i].op, next[i].i, next[i].j);
      if (inq.find(v) == inq.end()) {
        q.push(v);
        vector<Oper> ops = inq[p];
        ops.push_back(next[i]);
        inq[v] = ops;
        //				printf("ops %d\n", ops.size());
      }
    }
  }
  assert(false);
}

int main(int argc, char **argv) {
#ifndef ONLINE_JUDGE
  freopen("./in.txt", "r", stdin);
#endif

  int Ca, Cb, K;
  while (scanf("%d%d%d", &Ca, &Cb, &K) != EOF) {
    Node init(Ca, Cb);
    inq.clear();
    BFS(init, K);
  }
  return 0;
}
