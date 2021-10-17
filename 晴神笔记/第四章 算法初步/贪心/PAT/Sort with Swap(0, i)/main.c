#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

#define MAXN 100005

/*
要将无序元素组织成一种数据结构，满足：
1. 快速找出一个元素，或者判空。
2. 快速删除其中一个元素。
*/

typedef struct Node Node;
struct Node {
    int pos;
    int val;
    Node* prev;  // 因为要删除节点，故需要双链表。
    Node* next;
};

Node nodes[MAXN];
Node Head;

// 加入一个节点。
void Add(int x, int pos) {
    Node* node = &nodes[x];
    node->pos = pos;
    node->val = x;
    / if (x == pos || x == 0) {
        return;
    }
    // 加入链表。
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

// 删除x元素。
void Remove(int x) {
    Node* node = &nodes[x];
    node->next->prev = node->prev;
    node->prev->next = node->next;
    node->next = node->prev = NULL;
}

// 把0和x的位置交换。
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
    int ans = 0;  // 需要几次交换

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
        int x;  // 待交换元素。
                //		PrintList();

        if (nodes[0].pos != 0) {
            // 0不在其本位上，则把该位置上应有的元素与0交换。
            x = nodes[0].pos;  // 0所在的位置上应该放的元素。
            Swap(x);
            // 把 x 从无序链表里删除。
            Remove(x);
        } else {
            // 0在其本位上，说明可能是有序了，否则就找到第一个
            // 无序元素，和0交换。
            if (Empty()) {
                // 没有无序元素了。
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
