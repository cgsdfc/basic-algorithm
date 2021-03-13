#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

#define MAXN 20
int ans; // ������ջ�������� 
int stack[MAXN]; // ջģ�⡣
int top; // topָ��ջ������һ��Ԫ�ء� 
int N; // 1--N ��Ԫ�ء�

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
index����ǰδ��ջ����СԪ�ء�
*/ 
void DFS(int index) {
	if (Empty() && index == N+1) {
		++ans;
		return;
	}
	if (index <= N) {
		// ��������ջ��
		Push(index);
		DFS(index+1);
		Pop(); // ��ԭ�� 
	}
	if (!Empty()) {
		// �����Գ�ջ��
		int x=Top();
		Pop();
		DFS(index);
		Push(x); // ��ԭ�� 
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

