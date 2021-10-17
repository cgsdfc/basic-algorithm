#include <algorithm>
#include <iostream>
using namespace std;

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

struct Node {
    // flag ��ǵ�һ�������Ԫ�ء�
    int flag;
    int next;
    char data;
};

// ��ַ��5λʮ����������һ��10e5����ַ��
#define MAXN (100000 + 5)
Node node[MAXN];

int main(int argc, char** argv) {
    int a, b;  // ���������ͷ��ַ��
    int N;

    // next �����ʼ��Ϊ-1���������ı�����ʧ�ܡ�
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
        ע����������롣
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
