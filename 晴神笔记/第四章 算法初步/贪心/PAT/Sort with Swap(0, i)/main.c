#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

#define MAXN 100005

/*
Ҫ������Ԫ����֯��һ�����ݽṹ�����㣺
1. �����ҳ�һ��Ԫ�أ������пա�
2. ����ɾ������һ��Ԫ�ء�
*/

typedef struct Node Node;
struct Node {
    int pos;
    int val;
    Node* prev;  // ��ΪҪɾ���ڵ㣬����Ҫ˫����
    Node* next;
};

Node nodes[MAXN];
Node Head;

// ����һ���ڵ㡣
void Add(int x, int pos) {
    Node* node = &nodes[x];
    node->pos = pos;
    node->val = x;
    / if (x == pos || x == 0) {
        return;
    }
    // ��������
    node->next = Head.next;
    node->prev = &Head;
    Head.next->prev = node;
    Head.next = node;
}

void Init(void) {
    Head.next = Head.prev = &Head;
}

int Empty(void) {
    return Head.next == &Head;
}

// ɾ��xԪ�ء�
void Remove(int x) {
    Node* node = &nodes[x];
    node->next->prev = node->prev;
    node->prev->next = node->next;
    node->next = node->prev = NULL;
}

// ��0��x��λ�ý�����
void Swap(int x) {
    int pos = nodes[x].pos;
    nodes[x].pos = nodes[0].pos;
    nodes[0].pos = pos;

    //	printf("swap 0 %d\n", x);
}

void PrintList(void) {
    Node* node;
    node = Head.next;
    while (node != &Head) {
        printf("%d -> ", node->val);
        node = node->next;
    }
    puts("");
}

int Front(void) {
    if (Empty()) return -1;
    return Head.next->val;
}

int main(int argc, char* argv[]) {
    int N;
    int i;
    int ans = 0;  // ��Ҫ���ν���

    Init();

    freopen("./in.txt", "r", stdin);

    scanf("%d", &N);
    for (i = 0; i < N; ++i) {
        int x;
        scanf("%d", &x);
        assert(0 <= x && x < N);
        Add(x, i);
    }

    //	for (i=0;i<N;++i) {
    //		printf("%d at %d\n", i, nodes[i].pos);
    //	}
    //
    //	PrintList();
    //	Remove(7);
    //	PrintList();
    //	return 0;

    while (1) {
        int x;  // ������Ԫ�ء�
                //		PrintList();

        if (nodes[0].pos != 0) {
            // 0�����䱾λ�ϣ���Ѹ�λ����Ӧ�е�Ԫ����0������
            x = nodes[0].pos;  // 0���ڵ�λ����Ӧ�÷ŵ�Ԫ�ء�
            Swap(x);
            // �� x ������������ɾ����
            Remove(x);
        } else {
            // 0���䱾λ�ϣ�˵�������������ˣ�������ҵ���һ��
            // ����Ԫ�أ���0������
            if (Empty()) {
                // û������Ԫ���ˡ�
                break;
            }
            x = Front();
            Swap(x);
        }
        ++ans;
    }
    printf("%d\n", ans);

    return 0;
}
