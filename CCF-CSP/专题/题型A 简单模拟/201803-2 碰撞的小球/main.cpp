#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

int N, L, T;
// N��С�������Ҷ˵�ΪL��ģ��T�롣

struct Ball {
    int id;
    int dir;  // ����0�ң�1��
    int pos;  // �������λ�á�
};

enum { DirR = 0, DirL = 1 };

#define MAXN 105

Ball bs[MAXN];
// ��һ��״̬��
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
    �����С���˳��Ҳ�������˳�򣬵��ǲ��ǽ���ģ��ĳ�ʼ˳��
    �Ȱ�С����λ�ô�С��������ģ����ٰ�������˳������Ȼ�������
    */
    sort(bs, bs + N, cmpByPos);

    // ����T��ģ�⡣
    while (T--) {
        //		Print();

        for (int i = 0; i < N; ++i) {
            /*
            ����ÿ��С�򣬸��ݵ�ǰ״̬������һ��״̬��
            */
            Ball b = bs[i];
            // ע�⸴��id��
            next[i].id = b.id;

            // �����ǽ��
            // ע�⣬������λ�ò��䣬��ֻ������ߵ������ײ��ǽ��
            if (i == 0 && b.pos == 1 && b.dir == DirL) {
                next[i].pos = 0;
                next[i].dir = DirR;
            } else if (i == N - 1 && b.pos == L - 1 && b.dir == DirR) {
                // �����ǽ��
                next[i].pos = L;
                next[i].dir = DirL;
            } else if (i > 0 && b.dir == DirL && bs[i - 1].dir == DirR && b.pos - bs[i - 1].pos == 2) {
                // ����ߵ�����ײ��
                next[i].pos = b.pos - 1;
                next[i].dir = DirR;
            } else if (i < N - 1 && b.dir == DirR && bs[i + 1].dir == DirL && bs[i + 1].pos - b.pos == 2) {
                // ���ұߵ�����ײ��
                next[i].pos = b.pos + 1;
                next[i].dir = DirL;
            } else {
                // û����ײ������
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
