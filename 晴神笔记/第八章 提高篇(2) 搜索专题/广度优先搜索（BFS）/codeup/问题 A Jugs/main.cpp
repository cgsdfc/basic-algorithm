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
��ˮ����
BFS�ⷨ��
����N��ˮ����Ȼ��ÿ��ˮ����������� ��
�����ֲ�����
1. ��ˮ�����ա�
2. ��ˮ��������
3. ��ˮ��i��ˮ����j����ˮ�Ĺ�����ʹ��i�ջ���j����
ͨ�������ֲ�����ʵ��ĳ��ˮ���е�ˮǡ��ΪK��
*/

// ˮ������
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
��ĿҪ����Ϸ��������У����Ա�����������Ϣ��
*/
struct Oper {
  OP op;
  int i, j;
};

/*
����N=2������״̬����С����map���ɡ�
*/
struct Node {
  Water data[N];
  // ����Ƿ񵹳���K��ˮ��
  // ע�⣬��Ŀ��Ҫ����BͰ��K��������������һͰ��
  bool OK(int K) const { return data[1].now == K; }
  /*
  �ֵ���ȽϺ���д���ˣ�����map�������ˣ���һ��Ԫ�ز���mapʱ��
  �����Ԫ�غ�find��Ȼ����end��
  �����Ǵ���ıȽϺ���ʵ�֣��ص����ж���֮��ķ�����䡣
  */
  bool WrongLess(const Node &a) const {
    /*
    ����߼�����ʲô�ط��أ�
    ��ȷ���߼���
    1. �ҵ���һ������ȵ�Ԫ�أ��Ƚ�������Ԫ�أ����������еıȽ��ɴ˾�����
    2. �Ҳ���1������Ԫ�أ�˵������������ȡ�

    ������߼���
    1. �ҵ���һ��С�ڹ�ϵ������Ԫ�أ�������ڣ������е�С�ڹ�ϵ������
    2. �Ҳ���1������Ԫ�أ�˵��С�ڹ�ϵ��������

    ����֮����
    �������ڣ�ֻ�е�һ�����д���һ��Ԫ�رȵڶ������еĶ�ӦԪ��С��С�ڹ�ϵ�ͳ����ˣ�
    ����ʵ�ϣ�С�ڹ�ϵȡ�����������е�һ��**�����**��Ԫ�أ����Գ��ֵ�һ�����ڵ�Ԫ��ʱ��
    С�ڹ�ϵ���Ѿ��������ˣ��������̷���false�������ܼ�����С�ڵ�Ԫ�ء�
    */
    for (int i = 0; i < N; ++i) {
      if (data[i].now < a.data[i].now)
        return true;
    }
    return false;
  }

  // �ֵ���Ƚϡ�
  friend bool operator<(const Node &a, const Node &b) {
    for (int i = 0; i < N; ++i) {
      /*
      ���ص�ʱ���ǳ��ֵ�һ�������Ԫ�أ������ֵ���Ƚϵģ�������ˡ�
      ʱ������ʱ�����еıȽϾ͵ȼ��ڸ�Ԫ�صıȽϡ�

      ��ʵ�ϣ�POD��int��char�����еıȽϣ�������memcmpʵ�֡�
      */
      if (a.data[i].now != b.data[i].now) {
        return a.data[i].now < b.data[i].now;
      }
    }
    return false;
  }
  // ����Op�Ƿ������С�
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
������������С����map����ɢ�У�
˳�㱣��������У����ﵽ��״̬����̲������С�
��������Node������ʹ��Node��������
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
