#include <algorithm>
#include <iostream>
using namespace std;

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

struct Node {
  int addr, pos, data, next, flag;
};

#define MAXN (100000 + 5)
Node node[MAXN];

/*
参考代码是在输出的时候完成反转的，
我的代码则是在排序时完成反转的。
前者的方法需要考虑较多边界条件。
而通过排序完成反转是完全可行的。
*/

struct cmp {
  int N; // 合法节点总数。
  int K; // 分组数。

  cmp(int _N, int _K) {
    N = _N;
    K = _K;
  }

  bool operator()(const Node &a, const Node &b) {
    if (!a.flag || !b.flag) {
      // 存在非法节点。
      return a.flag > b.flag; // flag=1 的在前面
    }
    /*
    每K个一组，组内反转，最后不到K个元素，不反转。
    */
    if (a.pos / K != b.pos / K || (N % K != 0 && a.pos / K == N / K)) {
      // a,b不是同一组，或者a，b都是最后的不足K个的那组。
      // 不要逆序。
      return a.pos < b.pos;
    }
    return a.pos > b.pos;
  }
};

int main(int argc, char **argv) {
  int head;
  /*
  注意：
  用N来判定两个节点是否是同一组，以及其他条件时，注意N应该时合法节点的总数，
  而不是输入的N，因为输入的N包括了非法节点。
  */
  int N;
  int K;

  freopen("./in.txt", "r", stdin);

  // 第二步，初始化
  for (int i = 0; i < MAXN; ++i) {
    node[i].next = -1;
    node[i].flag = 0;
  }

  scanf("%d%d%d", &head, &N, &K);
  for (int i = 0; i < N; ++i) {
    int addr;
    scanf("%d", &addr);
    scanf("%d%d", &node[addr].data, &node[addr].next);
    node[addr].addr = addr;
  }

  /*
  第三步，遍历链表，标记数据。
  */
  int count = 0;
  int p = head;
  while (p != -1) {
    node[p].flag = 1;
    node[p].pos = count;
    ++count;

    //		printf("addr %d data %d next %d pos %d\n", node[p].addr, node[p].data,
    //node[p].next, node[p].pos);

    p = node[p].next;
  }

  /*
  第四步，排序，把合法节点集中到左边
  */
  sort(node, node + MAXN, cmp(count, K));
  for (int i = 0; i < count; ++i) {
    if (i == count - 1) {
      printf("%05d %d -1\n", node[i].addr, node[i].data);
    } else {
      printf("%05d %d %05d\n", node[i].addr, node[i].data, node[i + 1].addr);
    }
  }

  return 0;
}
