#include <algorithm>
#include <iostream>
#include <queue>
using namespace std;

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

struct Person {
  int weight; // 老鼠重量。
  int turn;   // 比赛了多少轮。
  int rank;   // 最终排名。
};

#define MAXN 1005

Person person[MAXN];
// 保存当前程序员的id顺序。
int id[MAXN];

// 按参加比赛的轮次数从大到小排列，轮次最高的是总冠军。
bool cmpByTurn(int a, int b) { return person[a].turn > person[b].turn; }

void PrintId(int N) {
  for (int i = 0; i < N; ++i) {
    printf("%d ", id[i]);
  }
  printf("\n");
}

/*
注意order数组的含义。
6在0号位置，表示6号老鼠排第0号，而不是0号老鼠拍第六号。
*/

int main(int argc, char **argv) {
  int N; // N个程序员。
  int G; // 每次分为G组。
#ifndef ONLINE_JUDGE
  freopen("./in.txt", "r", stdin);
#endif
  // 初始化程序员的基本数据。
  scanf("%d%d", &N, &G);
  /*
  注意，当G=1，而N>1时，程序会死循环，因为每次分组没有使队列的元素减少，
  自然最后也不会减到零。
  然而当G=1并且N=1，即参数人员只有1人，且分一组时，程序能够正确运行。
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
    // 把order数组直接输入，则按此顺序就是各个人的参数顺序。
    scanf("%d", &id[i]);
  }
  //	PrintId(N);

  /*
  模拟比赛的过程，
  每一轮结束后，就把turn增大1.
  */
  queue<int> q;
  for (int i = 0; i < N; ++i) {
    // 全部人入队。
    q.push(id[i]);
  }

  /*
  要非常注意这个循环的写法 。
  对于当前队列的全部元素，将其分为G个一组，对每一组取其最大值，然后最大值
  对应的人的编号入队。注意这个冠军属于下一轮，所以当前轮不应涉及它。
  要非常注意当前轮和下一轮的人不要混在一起了。在使用同一个队列的情况下，
  非常容易出错。
  */

  while (true) {
    int total = q.size();
    //		printf("q.size %d grop %d\n", q.size(), group);
    /*
    控制这种循环的方法有2种：
    1. 组外循环，组内循环，每组用i，j控制，外层控制i，内层控制j。
    2. 计算出组数，每组控制不要超过G和总数。
    */

    for (int i = 0; i < total; i += G) {
      int step = min(i + G, total);
      //			printf("i %d step %d total %d\n", i, step,
      //total);

      int max = -1; // 最好成绩。
      int win;      // 本轮的冠军。
      // 每组的人数必须计算出来，否则队列里前一组的冠军会混进来。
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
      // 冠军已经出现，但是它的轮次和第二名还是一样的。
      // 要给它加一次。
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

  // 比赛结束，按照轮次排序。
  sort(id, id + N, cmpByTurn);
#ifndef ONLINE_JUDGE
  for (int i = 0; i < N; ++i) {
    printf("%d turn %d\n", id[i], person[id[i]].turn);
  }
#endif

  // 按照turn计算各人排名。
  /*
  注意排名的规则，同分占一个排名。
  对于：5 4 3 3 2 2 1 来说：
  排名为：1 2 3 3 5 5 7
  而不是：1 2 3 3 4 4 5
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
