#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */
typedef struct Node Node;
struct Node {
    int data;
    Node* next;
};

enum {
    OK = 0,
    ERR = 1,
};

Node* Create(void) {
    int N;
    Node* L;

    L = malloc(sizeof(Node));  // 头节点。
    L->next = NULL;
    scanf("%d", &N);
    while (N--) {
        int x;
        Node* p;

        scanf("%d", &x);
        p = malloc(sizeof(Node));
        p->data = x;
        p->next = L->next;
        L->next = p;
    }
    return L;
}

/*
注意各种操作里面，p（即遍历链表的指针）的初始值。
在 Get，Insert，Delete 等涉及pos的操作里，p=head，即头节点。
因为它需要得到某节点的前一个节点，如果初始化为head->next，则当pos=1时就找不到
前一个节点了。
而在 Show 里面，因为要打印有效的数据，而头节点的数据是无效的，所以p=head->next.
*/

void Show(Node* L) {
    Node* p = L->next;
    if (!p) {
        puts("Link list is empty");
        return;
    }
    while (p) {
        // 如果没有下一个，那就是最后一个元素。
        printf("%d%s", p->data, p->next ? " " : "\n");
        p = p->next;
    }
}

/*
插入，pos从1开始，失败返回1，成功返回0
*/
int Insert(Node* L, int pos, int x) {
    Node* p = L;
    int i = 0;
    // 走最多pos-1次。
    while (p && i < pos - 1) {
        p = p->next;
        ++i;
    }
    if (!p) return ERR;

    L = malloc(sizeof(Node));
    L->data = x;
    L->next = p->next;
    p->next = L;
    return OK;
}

/*
删除。
*/
int Delete(Node* L, int pos) {
    Node* p = L;
    int i = 0;
    while (p && i < pos - 1) {
        p = p->next;
        ++i;
    }
    if (!p) return ERR;
    L = p->next;
    p->next = L->next;
    free(L);
    return OK;
}

/*
查找pos的元素。注意，直接找pos元素即可。
*/
int Get(Node* L, int pos, int* x) {
    Node* p = L;
    int i = 0;
    while (p && i < pos) {
        p = p->next;
        ++i;
    }
    if (!p) return ERR;
    *x = p->data;
    return OK;
}

int main(int argc, char* argv[]) {
    Node* L;
    int N;
    char str[20];

#ifndef ONLINE_JUDGE
    freopen("./in.txt", "r", stdin);
#endif

    L = Create();
    scanf("%d", &N);
    while (N--) {
        scanf("%s", str);
        if (!strcmp(str, "show")) {
            Show(L);
        } else if (!strcmp(str, "insert")) {
            int pos, x;
            scanf("%d%d", &pos, &x);
            if (OK == Insert(L, pos, x)) {
                puts("insert OK");
            } else {
                puts("insert fail");
            }
        } else if (!strcmp(str, "delete")) {
            int pos;
            scanf("%d", &pos);
            if (OK == Delete(L, pos)) {
                puts("delete OK");
            } else {
                puts("delete fail");
            }
        } else if (!strcmp(str, "get")) {
            int pos, x;
            scanf("%d", &pos);
            if (OK == Get(L, pos, &x)) {
                printf("%d\n", x);
            } else {
                puts("get fail");
            }
        } else {
            assert(0);
        }
    }

    return 0;
}
