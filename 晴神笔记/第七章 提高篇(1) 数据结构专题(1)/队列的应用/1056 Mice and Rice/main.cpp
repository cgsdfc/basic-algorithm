#include <algorithm>
#include <iostream>
#include <queue>
using namespace std;

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

struct Person {
  int weight; // ����������
  int turn;   // �����˶����֡�
  int rank;   // ����������
};

#define MAXN 1005

Person person[MAXN];
// ���浱ǰ����Ա��id˳��
int id[MAXN];

// ���μӱ������ִ����Ӵ�С���У��ִ���ߵ����ܹھ���
bool cmpByTurn(int a, int b) { return person[a].turn > person[b].turn; }

void PrintId(int N) {
  for (int i = 0; i < N; ++i) {
    printf("%d ", id[i]);
  }
  printf("\n");
}

/*
ע��order����ĺ��塣
6��0��λ�ã���ʾ6�������ŵ�0�ţ�������0�������ĵ����š�
*/

int main(int argc, char **argv) {
  int N; // N������Ա��
  int G; // ÿ�η�ΪG�顣
#ifndef ONLINE_JUDGE
  freopen("./in.txt", "r", stdin);
#endif
  // ��ʼ������Ա�Ļ������ݡ�
  scanf("%d%d", &N, &G);
  /*
  ע�⣬��G=1����N>1ʱ���������ѭ������Ϊÿ�η���û��ʹ���е�Ԫ�ؼ��٣�
  ��Ȼ���Ҳ��������㡣
  Ȼ����G=1����N=1����������Աֻ��1�ˣ��ҷ�һ��ʱ�������ܹ���ȷ���С�
  */
  //	if (G == 1) {
  //		abort();
  //	}

  for (int i = 0; i < N; ++i) {
    person[i].turn = 0;
    id[i] = i;
  }

  for (int i = 0; i < N; ++i) {
    scanf("%d", &person[i].weight);
  }
  for (int i = 0; i < N; ++i) {
    // ��order����ֱ�����룬�򰴴�˳����Ǹ����˵Ĳ���˳��
    scanf("%d", &id[i]);
  }
  //	PrintId(N);

  /*
  ģ������Ĺ��̣�
  ÿһ�ֽ����󣬾Ͱ�turn����1.
  */
  queue<int> q;
  for (int i = 0; i < N; ++i) {
    // ȫ������ӡ�
    q.push(id[i]);
  }

  /*
  Ҫ�ǳ�ע�����ѭ����д�� ��
  ���ڵ�ǰ���е�ȫ��Ԫ�أ������ΪG��һ�飬��ÿһ��ȡ�����ֵ��Ȼ�����ֵ
  ��Ӧ���˵ı����ӡ�ע������ھ�������һ�֣����Ե�ǰ�ֲ�Ӧ�漰����
  Ҫ�ǳ�ע�⵱ǰ�ֺ���һ�ֵ��˲�Ҫ����һ���ˡ���ʹ��ͬһ�����е�����£�
  �ǳ����׳���
  */

  while (true) {
    int total = q.size();
    //		printf("q.size %d grop %d\n", q.size(), group);
    /*
    ��������ѭ���ķ�����2�֣�
    1. ����ѭ��������ѭ����ÿ����i��j���ƣ�������i���ڲ����j��
    2. �����������ÿ����Ʋ�Ҫ����G��������
    */

    for (int i = 0; i < total; i += G) {
      int step = min(i + G, total);
      //			printf("i %d step %d total %d\n", i, step,
      //total);

      int max = -1; // ��óɼ���
      int win;      // ���ֵĹھ���
      // ÿ����������������������������ǰһ��Ĺھ���������
      for (int j = i; j < step; ++j) {
        int cur = q.front();
        ++person[cur].turn;
#ifndef ONLINE_JUDGE
        printf("cur %d w %d\n", cur, person[cur].weight);
#endif
        q.pop();
        if (person[cur].weight > max) {
          max = person[cur].weight;
          win = cur;
        }
      }
#ifndef ONLINE_JUDGE
      printf("win %d\n", win);
#endif
      q.push(win);
    }

    if (q.size() == 1) {
      // �ھ��Ѿ����֣����������ִκ͵ڶ�������һ���ġ�
      // Ҫ������һ�Ρ�
      int cur = q.front();
      person[cur].turn++;
      break;
    }
  }

  //	printf("turn\n");
  //	for (int i=0;i<N;++i) {
  //		printf("%d ", person[i].turn);
  //	}
  //	printf("\n");

  // ���������������ִ�����
  sort(id, id + N, cmpByTurn);
#ifndef ONLINE_JUDGE
  for (int i = 0; i < N; ++i) {
    printf("%d turn %d\n", id[i], person[id[i]].turn);
  }
#endif

  // ����turn�������������
  /*
  ע�������Ĺ���ͬ��ռһ��������
  ���ڣ�5 4 3 3 2 2 1 ��˵��
  ����Ϊ��1 2 3 3 5 5 7
  �����ǣ�1 2 3 3 4 4 5
  */

  int r;
  for (int i = 0; i < N; ++i) {
    if (i == 0 || person[id[i]].turn != person[id[i - 1]].turn) {
      person[id[i]].rank = r = i + 1;
    } else {
      person[id[i]].rank = r;
    }
  }

  for (int i = 0; i < N; ++i) {
    printf("%d%s", person[i].rank, i == N - 1 ? "\n" : " ");
  }

  return 0;
}
