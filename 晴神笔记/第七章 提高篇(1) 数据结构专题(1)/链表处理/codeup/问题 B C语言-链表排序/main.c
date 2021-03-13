#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

/*
把两条链表合为一条，然后归并排序。
*/

typedef struct Node Node;
struct Node {
	int id;
	int score;
	Node* next;
};

typedef struct List List;
struct List {
	Node* p;
	int len;
};

// 因为要排序，所以就不带头节点。 
List Create(void) {
	int M,N;
	List L={};
	int len;
	
	scanf("%d%d", &M, &N);
	len=M+N;
	L.len=len;
	while (len--) {
		Node* p=malloc(sizeof(Node));
		scanf("%d%d", &p->id, &p->score);
		p->next=L.p;
		L.p=p;
	}
	return L;
}

void Show(List L) {
	Node* p=L.p;
	while (p) {
		printf("%d %d\n", p->id, p->score);
		p=p->next;
	}
//	printf("%d\n", L.len);
}

Node* Merge(Node* left, Node* right) {
	Node* last;
	Node* head;
	assert(left && right);
	
	last=head=NULL;
	while (left && right) {
		if (left->id < right->id) {
			if (!head) {
				head=last=left;
			} else {
				last->next=left;
				last=left;
			}
			left=left->next;
		} else {
			if (!head) {
				head=last=right;
			} else {
				last->next=right;
				last=right;
			}
			right=right->next;
		}
	}
	if (left) {
		last->next=left;
	}
	if (right) {
		last->next=right;
	}

	return head;
}

List MergeSort(List L) {
	assert(L.p);
	if (L.len > 1) {
		List left, right;
		int len=L.len/2;
		int i=0;
		Node* p=L.p;
		
		while (p && i<len-1) {
			p=p->next;
			++i;
		}
		left.len=len;
		right.len=L.len-len;
		right.p=p->next;
		p->next=NULL;
		left.p=L.p;
		
		left=MergeSort(left);
		right=MergeSort(right);
		L.p=Merge(left.p, right.p);
	}
	// 注意，只有一个元素，也要返回L，否则就是UB。 
	return L;
}

int main(int argc, char *argv[]) {
	List L;
	
#ifndef ONLINE_JUDGE
	freopen("./in.txt","r",stdin);
#endif

	L=Create();
//	Show(L);
	
	L=MergeSort(L);
	Show(L);
	
	return 0;
}
