#include <cstdio>

const int MAXN = 10000 + 5;

int N;  // 窗口数。
int M;  // 点击数。

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

struct Point {
    int X, Y;
    void Read() {
        scanf("%d%d", &X, &Y);
    }
};

struct Win {
    int id;
    Point up, down;

    bool In(Point p) {
        return (up.X <= p.X && p.X <= down.X) && (down.Y <= p.Y && p.Y <= up.Y);
    }
    void Read() {
        scanf("%d", &id);
        // 右下角，X大，Y小。
        down.Read();
        // 左上角, X小,Y大.
        up.Read();
    }
} win[MAXN];

// 0号是最上面的窗口。

int Find(Point p) {
    // 查找点击了哪个窗口。
    for (int i = 0; i < N; ++i) {
        if (win[i].In(p)) { return i; }
    }
    return -1;  // 没有点中任何窗口。
}

// 把i号窗口移动到0号，其他窗口相对位置不变。
void Move(int i) {
    Win temp = win[i];  // 先保存。
    for (int j = i; j >= 1; j--) {
        // 用前面覆盖后面。注意顺序不能反。
        win[j] = win[j - 1];
    }
    win[0] = temp;
}

int main(int argc, char** argv) {
    scanf("%d", &N);
    for (int i = 0; i < N; ++i) {
        win[i].Read();
    }
    scanf("%d", &M);
    while (M--) {
        Point p;
        p.Read();
        int i = Find(p);
        if (i == -1) continue;
        Move(i);
    }
    // 叠放次序，从上到下输出窗口id。
    for (int i = 0; i < N; ++i) {
        printf("%d ", win[i].id);
    }
    puts("");

    return 0;
}
