#include <cstdio>
#include <queue> // �������������ر����ȶ��С�
using namespace std;

/*
�����ȶ���ʵ�ֺϲ��������⡣
*/
 
// ע�⣬Ĭ�ϵ�PQ�ıȽ�����less��ʵ�ֵ��Ǵ󶥶ѣ�
// ����������ҪС���ѣ������õıȽ�����greater��
// �Ƚ�����queueͷ�ļ�����С��Լ�ʵ��Ҳ�ɣ���Ҫע��
// cmp��ʵ�֡��������Ҫ�����ĵıȽ��������봫��Container������
// ��vector<T> �ͺá� 

typedef long long ll;
 
priority_queue<ll, vector<ll>, greater<ll> > q;
 
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char** argv) {
	int N;
	scanf("%d", &N);
	while (N--) {
		ll x;
		scanf("%d", &x);
		// ���������������ʹ�ѳ�ʼ��ΪN��Ԫ�ء�
		q.push(x); 
	}
	int ans=0;
	// ��������������ͬʱ����WPL������Ȩ��С·���͡�
	// �����õ�����һ������ʽ�ӣ�����Ҷ�ڵ��Ȩ�غ͡�
	// WPL�Ķ���������Ҷ�ӵ�·�����ȳ�Ҷ�ӵ�Ȩ��֮�͡�
	while (q.size() > 1) {
		int a=q.top();q.pop();
		int b=q.top();q.pop();
		int root=a+b; // a��b�ĸ��ڵ�Ȩ�ء�
		// ���ڲ���Ҫ�����������ӹ�ϵ������Ľڵ�ֻ������Ȩ�ء�
		q.push(root);
		ans += root;  // root �ض��Ƿ�Ҷ�ӽڵ㡣 
	}
	printf("%d\n", ans);
	
	return 0;
}
