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

    L = malloc(sizeof(Node));  // ͷ�ڵ㡣
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
ע����ֲ������棬p�������������ָ�룩�ĳ�ʼֵ��
�� Get��Insert��Delete ���漰pos�Ĳ����p=head����ͷ�ڵ㡣
��Ϊ����Ҫ�õ�ĳ�ڵ��ǰһ���ڵ㣬�����ʼ��Ϊhead->next����pos=1ʱ���Ҳ���
ǰһ���ڵ��ˡ�
���� Show ���棬��ΪҪ��ӡ��Ч�����ݣ���ͷ�ڵ����������Ч�ģ�����p=head->next.
*/

void Show(Node* L) {
    Node* p = L->next;
    if (!p) {
        puts("Link list is empty");
        return;
    }
    while (p) {
        // ���û����һ�����Ǿ������һ��Ԫ�ء�
        printf("%d%s", p->data, p->next ? " " : "\n");
        p = p->next;
    }
}

/*
���룬pos��1��ʼ��ʧ�ܷ���1���ɹ�����0
*/
int Insert(Node* L, int pos, int x) {
    Node* p = L;
    int i = 0;
    // �����pos-1�Ρ�
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
ɾ����
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
����pos��Ԫ�ء�ע�⣬ֱ����posԪ�ؼ��ɡ�
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
