#include <algorithm>
#include <iostream>
using namespace std;

/*
��̬�����ģ���⣬
1. ����ڵ�ͽڵ����顣
2. �ڵ��ʼ����
3. ���롣
4. �����ڵ�����ǡ�
5. ����û�кϷ��ڵ㡣
6. ����
7. �����
*/

struct Node {
    int addr;
    int key;
    int next;
    int flag;  // 1��ʾ�Ϸ���0��ʾ�Ƿ���
};

#define MAXN (100000 + 5)
Node node[MAXN];

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

bool cmp(Node a, Node b) {
    if (a.flag != b.flag) { return a.flag > b.flag; }
    return a.key < b.key;
}

int main(int argc, char** argv) {
    int head;
    int N;
    for (int i = 0; i < MAXN; ++i) {
        node[i].next = -1;
        node[i].flag = 0;
    }
    scanf("%d%d", &N, &head);
#ifndef ONLINE_JUDGE
    printf("N %d head %d\n", N, head);
#endif

    while (N--) {
        int addr;
        scanf("%d", &addr);
        scanf("%d%d", &node[addr].key, &node[addr].next);
        node[addr].addr = addr;
    }

    int count = 0;
    int p = head;
    while (p != -1) {
        node[p].flag = 1;
        ++count;
        p = node[p].next;
    }
    if (!count) {
        // N head
        printf("0 -1\n");
        return 0;
    }
    sort(node, node + MAXN, cmp);
    printf("%d %05d\n", count, node[0].addr);

    for (int i = 0; i < count; ++i) {
        if (i == count - 1) {
            // last node.
            printf("%05d %d -1\n", node[i].addr, node[i].key);
        } else {
            printf("%05d %d %05d\n", node[i].addr, node[i].key, node[i + 1].addr);
        }
    }

    return 0;
}
