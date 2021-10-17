#include <cstdio>

const int MAXN = 10000 + 5;

int N;  // ��������
int M;  // �������

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
        // ���½ǣ�X��YС��
        down.Read();
        // ���Ͻ�, XС,Y��.
        up.Read();
    }
} win[MAXN];

// 0����������Ĵ��ڡ�

int Find(Point p) {
    // ���ҵ�����ĸ����ڡ�
    for (int i = 0; i < N; ++i) {
        if (win[i].In(p)) { return i; }
    }
    return -1;  // û�е����κδ��ڡ�
}

// ��i�Ŵ����ƶ���0�ţ������������λ�ò��䡣
void Move(int i) {
    Win temp = win[i];  // �ȱ��档
    for (int j = i; j >= 1; j--) {
        // ��ǰ�渲�Ǻ��档ע��˳���ܷ���
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
    // ���Ŵ��򣬴��ϵ����������id��
    for (int i = 0; i < N; ++i) {
        printf("%d ", win[i].id);
    }
    puts("");

    return 0;
}
