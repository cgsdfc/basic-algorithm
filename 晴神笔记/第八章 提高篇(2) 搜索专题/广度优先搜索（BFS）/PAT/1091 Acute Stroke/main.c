#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */
int M, N, L, T;

#define MAXM 1300
#define MAXN 130
#define MAXL 65

int A[MAXL][MAXM][MAXN];
int inq[MAXL][MAXM][MAXN];  // 标记坐标是否在队列中。

int ans;  // 总体积。

typedef struct Point {
    int x, y, z;
} Point;

// 队列实现。
typedef Point Elem;
typedef struct Node Node;
struct Node {
    Elem data;
    Node* next;
};
typedef struct Queue Queue;
struct Queue {
    Node* head;
    Node* last;
};

Queue New(void) {
    Queue q;
    q.head = q.last = malloc(sizeof(Node));
    q.head->next = NULL;
    return q;
}

Elem Front(Queue q) {
    return q.head->next->data;
}

Queue Push(Queue q, Elem x) {
    Node* p = malloc(sizeof(Node));
    p->data = x;
    p->next = NULL;
    q.last->next = p;
    q.last = p;
    return q;
}

Queue Pop(Queue q) {
    Node* p = q.head->next;
    q.head->next = p->next;
    free(p);
    if (!q.head->next) { q.last = q.head; }
    return q;
}

int Empty(Queue q) {
    return q.head->next == NULL;
}

const int X[] = {0, 0, 1, -1, 0, 0};
const int Y[] = {1, -1, 0, 0, 0, 0};
const int Z[] = {0, 0, 0, 0, 1, -1};

// 1286 by 128); L (≤60) is the number of slices o

// 是否需要将p入队。
int Judge(Point p) {
    if (!(0 <= p.z && p.z < L)) return 0;
    if (!(0 <= p.x && p.x < M)) return 0;
    if (!(0 <= p.y && p.y < N)) return 0;
    if (inq[p.z][p.x][p.y]) return 0;
    if (!A[p.z][p.x][p.y]) return 0;
    return 1;
}

void Print(Point p) {
    printf("%d %d %d\n", p.x, p.y, p.z);
}

void PrintQ(Queue q) {
    Node* p = q.head->next;
    int c = 0;
    while (p) {
        c++;
        p = p->next;
    }
    printf("cnt %d\n", c);
}

int BFS(Point v) {
    int tot = 1;  // 本次遍历的块的体积。
    Queue q = New();
    q = Push(q, v);
    inq[v.z][v.x][v.y] = 1;

    while (!Empty(q)) {
        int i;
        Point p = Front(q);

        //		Print(p);

        q = Pop(q);
        for (i = 0; i < 6; ++i) {
            Point k = {p.x + X[i], p.y + Y[i], p.z + Z[i]};
            //			Print(k);
            if (Judge(k)) {
                inq[k.z][k.x][k.y] = 1;
                q = Push(q, k);
                //				printf("1\n");
                ++tot;
            }
        }
        //		PrintQ(q);
    }
    return tot;
}

/*
碰到BFS的题目，还是用STL吧。
*/

int main(int argc, char* argv[]) {
    int i, j, k;

    freopen("./in.txt", "r", stdin);

    scanf("%d%d%d%d", &M, &N, &L, &T);
    for (k = 0; k < L; ++k) {
        // 输入L层。每层是M*N矩阵。
        for (i = 0; i < M; ++i) {
            for (j = 0; j < N; ++j) {
                scanf("%d", &A[k][i][j]);
            }
        }
    }

    //	for (k=0;k<L;++k) {
    //		for (i=0;i<M;++i) {
    //			for (j=0;j<N;++j) {
    //				printf("%d ", A[k][i][j]);
    //			}
    //			printf("\n");
    //		}
    //	}

    for (k = 0; k < L; ++k) {
        for (i = 0; i < M; ++i) {
            for (j = 0; j < N; ++j) {
                if (A[k][i][j] == 1 && inq[k][i][j] == 0) {
                    Point p = {i, j, k};
                    int V = BFS(p);

                    //					printf("V %d\n", V);

                    if (V >= T) { ans += V; }
                }
            }
        }
    }
    printf("%d\n", ans);
    return 0;
}
