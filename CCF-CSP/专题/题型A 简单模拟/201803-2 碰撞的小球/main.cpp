#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

int N, L, T;
// N个小球，区间右端点为L，模拟T秒。

struct Ball {
    int id;
    int dir;  // 方向，0右，1左。
    int pos;  // 坐标轴的位置。
};

enum { DirR = 0, DirL = 1 };

#define MAXN 105

Ball bs[MAXN];
// 下一个状态。
Ball next[MAXN];

bool cmpByPos(Ball& a, Ball& b) {
    return a.pos < b.pos;
}
bool cmpById(Ball& a, Ball& b) {
    return a.id < b.id;
}

void Print() {
    for (int i = 0; i < N; ++i) {
        printf("%d%s", bs[i].pos, i == N - 1 ? "\n" : " ");
    }
}

int main(int argc, char** argv) {
    scanf("%d%d%d", &N, &L, &T);
    for (int i = 0; i < N; ++i) {
        scanf("%d", &bs[i].pos);
        bs[i].id = i;
    }
    /*
    输入的小球的顺序，也是输出的顺序，但是不是进行模拟的初始顺序。
    先把小球按照位置从小到大排序，模拟后，再按照输入顺序排序，然后输出。
    */
    sort(bs, bs + N, cmpByPos);

    // 进行T次模拟。
    while (T--) {
        //		Print();

        for (int i = 0; i < N; ++i) {
            /*
            对于每个小球，根据当前状态计算下一个状态。
            */
            Ball b = bs[i];
            // 注意复制id。
            next[i].id = b.id;

            // 检查左墙。
            // 注意，球的相对位置不变，即只有最左边的球才能撞左墙。
            if (i == 0 && b.pos == 1 && b.dir == DirL) {
                next[i].pos = 0;
                next[i].dir = DirR;
            } else if (i == N - 1 && b.pos == L - 1 && b.dir == DirR) {
                // 检查右墙。
                next[i].pos = L;
                next[i].dir = DirL;
            } else if (i > 0 && b.dir == DirL && bs[i - 1].dir == DirR && b.pos - bs[i - 1].pos == 2) {
                // 和左边的球碰撞。
                next[i].pos = b.pos - 1;
                next[i].dir = DirR;
            } else if (i < N - 1 && b.dir == DirR && bs[i + 1].dir == DirL && bs[i + 1].pos - b.pos == 2) {
                // 和右边的球碰撞。
                next[i].pos = b.pos + 1;
                next[i].dir = DirL;
            } else {
                // 没有碰撞发生。
                next[i].dir = b.dir;
                if (b.dir == DirL) {
                    next[i].pos = b.pos - 1;
                } else {
                    next[i].pos = b.pos + 1;
                }
            }
        }
        memcpy(bs, next, sizeof(Ball) * N);
    }

    sort(bs, bs + N, cmpById);
    Print();

    return 0;
}
