#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

#define MAXN 20
int ans; // 计数出栈序列数。 
int stack[MAXN]; // 栈模拟。
int top; // top指向栈顶的下一个元素。 
int N; // 1--N 个元素。

void Clear(void) {
	top=0;
}

int Empty(void) {
	return top==0;
}

int Top(void) {
	return stack[top-1];
}

void Push(int x) {
	stack[top++]=x;
}

void Pop(void) {
	--top;
}

/*
index：当前未入栈的最小元素。
*/ 
void DFS(int index) {
	if (Empty() && index == N+1) {
		++ans;
		return;
	}
	if (index <= N) {
		// 还可以入栈。
		Push(index);
		DFS(index+1);
		Pop(); // 复原。 
	}
	if (!Empty()) {
		// 还可以出栈。
		int x=Top();
		Pop();
		DFS(index);
		Push(x); // 复原。 
	} 
}

int main(int argc, char *argv[]) {
	while (scanf("%d", &N) != EOF) {
		ans=0;
		Clear();
		DFS(1);
		printf("%d\n", ans);
	}
	return 0;
}

