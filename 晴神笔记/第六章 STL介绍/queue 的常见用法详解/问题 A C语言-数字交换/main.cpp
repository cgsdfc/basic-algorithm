#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

/*
ע�⴦���һ��Ԫ�������ģ��������һ��Ԫ������С�������
����һ����������������һ������СԪ����ɺ����Ԫ�ص��±���ܸı䣬
���һ��Ԫ�ص�ֵ���ܸı䡣 
�����ȼ�¼�����Сֵ���±꣬Ȼ�����ν������ε������ǲ��Եġ�
����ÿ�ζ��������ֵ����Сֵ����λ�ã�Ȼ�󽻻���
�ö���ʵ�ֵĻ�����������һ����ʱ���У����һ������������ 
*/

void Print(queue<int> q) {
	while (!q.empty()) {
		printf("%d ", q.front());
		q.pop();
	}
	printf("\n");
}

/*
��x���ֵ�λ�û�Ϊ��һ��Ԫ�أ��ѵ�һ��Ԫ�ػ�Ϊx��
*/ 
void SwapFirst(queue<int>& q, int x) {
	if (q.front() == x) {
		return;
	}
	queue<int> temp;
	temp.push(x); // x��Ϊ��һ��Ԫ�ء� 
	int first=q.front();
	q.pop();
	while (!q.empty()) {
		if (q.front() == x) {
			// x�����ˣ���Ϊfirst�� 
			temp.push(first);
		} else {
			temp.push(q.front());
		}
		q.pop();
	}
	q=temp;
}

/*
��x���ֵ�λ�û�Ϊ���һ��Ԫ�أ������һ��Ԫ�ػ�Ϊx��
*/ 
void SwapLast(queue<int>& q, int x) {
	if (q.back() == x) {
		return;
	}
	queue<int> temp;
	int last=q.back();
	// q�����һ��Ԫ�ز��ܷ���temp��
	// ��Ӧ�ð�x��Ϊ���һ������temp�� 
	while (q.size() != 1) {
		if (q.front() == x) {
			temp.push(last);
		} else {
			temp.push(q.front());
		}
		q.pop();
	}
	temp.push(x);
	q=temp; 
}

int main(int argc, char** argv) {
	const int N=10;
	int i;
	int Min, Max;
	queue<int> q;
	
	for (int i=0;i<N;++i) {
		int x;
		scanf("%d", &x);
		if (i==0||x>Max) {
			Max=x;
		}
		if (i==0||x<Min) {
			Min=x;
		}
		q.push(x);
	}
	
//	printf("Min %d Max %d\n", Min, Max);
	
	SwapFirst(q, Min);
//	Print(q);
	
	SwapLast(q, Max);
	Print(q);
	
	return 0;
}
