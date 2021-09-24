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
�ο��������������ʱ����ɷ�ת�ģ�
�ҵĴ�������������ʱ��ɷ�ת�ġ�
ǰ�ߵķ�����Ҫ���ǽ϶�߽�������
��ͨ��������ɷ�ת����ȫ���еġ�
*/

struct cmp {
  int N; // �Ϸ��ڵ�������
  int K; // ��������

  cmp(int _N, int _K) {
    N = _N;
    K = _K;
  }

  bool operator()(const Node &a, const Node &b) {
    if (!a.flag || !b.flag) {
      // ���ڷǷ��ڵ㡣
      return a.flag > b.flag; // flag=1 ����ǰ��
    }
    /*
    ÿK��һ�飬���ڷ�ת����󲻵�K��Ԫ�أ�����ת��
    */
    if (a.pos / K != b.pos / K || (N % K != 0 && a.pos / K == N / K)) {
      // a,b����ͬһ�飬����a��b�������Ĳ���K�������顣
      // ��Ҫ����
      return a.pos < b.pos;
    }
    return a.pos > b.pos;
  }
};

int main(int argc, char **argv) {
  int head;
  /*
  ע�⣺
  ��N���ж������ڵ��Ƿ���ͬһ�飬�Լ���������ʱ��ע��NӦ��ʱ�Ϸ��ڵ��������
  �����������N����Ϊ�����N�����˷Ƿ��ڵ㡣
  */
  int N;
  int K;

  freopen("./in.txt", "r", stdin);

  // �ڶ�������ʼ��
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
  ����������������������ݡ�
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
  ���Ĳ������򣬰ѺϷ��ڵ㼯�е����
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
