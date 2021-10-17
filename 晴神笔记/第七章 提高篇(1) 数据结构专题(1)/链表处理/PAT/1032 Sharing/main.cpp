#include <algorithm>
#include <iostream>
using namespace std;

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

struct Node {
    // flag 标记第一个链表的元素。
    int flag;
    int next;
    char data;
};

// 地址是5位十进制数，故一共10e5个地址。
#define MAXN (100000 + 5)
Node node[MAXN];

int main(int argc, char** argv) {
    int a, b;  // 两个链表的头地址。
    int N;

    // next 必须初始化为-1，否则后面的遍历会失败。
    for (int i = 0; i < MAXN; ++i) {
        node[i].next = -1;
        node[i].flag = 0;
    }

    scanf("%d%d%d", &a, &b, &N);
    while (N--) {
        int addr;
        char data;
        int next;
        /*
        注意这里的输入。
        */
        scanf("%d %c %d", &addr, &data, &next);
        node[addr].data = data;
        node[addr].next = next;
    }
    int p = a;
    while (p != -1) {
        node[p].flag = 1;
        p = node[p].next;
    }
    p = b;
    int ans = -1;
    while (p != -1) {
        if (node[p].flag) {
            ans = p;
            break;
        }
        p = node[p].next;
    }
    if (ans == -1) {
        printf("-1\n");
    } else {
        printf("%05d\n", ans);
    }

    return 0;
}
