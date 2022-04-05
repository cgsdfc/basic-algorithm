#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

#define MAXN 20
int ans;          // 计数出栈序列数。
int stack[MAXN];  // 栈模拟。
int top;          // top指向栈顶的下一个元素。
int N;            // 1--N 个元素。

void Clear(void) {
    top = 0;
}

int Empty(void) {
    return top == 0;
}

int Top(void) {
    return stack[top - 1];
}

void Push(int x) {
    stack[top++] = x;
}

void Pop(void) {
    --top;
}

/*
index：当前未入栈的最小元素。
每一步有两种可能的操作：
1. 取一个还未入栈的元素，入栈；
2. 从栈中弹出一个元素，该元素不再入栈。
直到所有元素都入栈一次、出栈一次为止，即栈为空，且待入栈元素为空。
*/
void DFS(int index) {
    if (Empty() && index == N + 1) {
        ++ans;
        return;
    }
    if (index <= N) {
        // 还可以入栈。
        Push(index);
        DFS(index + 1);
        Pop();  // 复原。
    }
    if (!Empty()) {
        // 还可以出栈。
        int x = Top();
        Pop();
        DFS(index);
        Push(x);  // 复原。
    }
}

// 求N个元素的所有出栈序列数，实际上是斯特林数，这里用递归模拟计数。
int main(int argc, char* argv[]) {
    while (scanf("%d", &N) != EOF) {
        ans = 0;
        Clear();
        DFS(1);
        printf("%d\n", ans);
    }
    return 0;
}
