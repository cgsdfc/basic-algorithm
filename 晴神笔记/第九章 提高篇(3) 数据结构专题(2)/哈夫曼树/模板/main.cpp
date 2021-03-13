#include <cstdio>
#include <queue> // 哈夫曼树构建必备优先队列。
using namespace std;

/*
用优先队列实现合并果子问题。
*/
 
// 注意，默认的PQ的比较器是less，实现的是大顶堆，
// 我们这里需要小顶堆，所以用的比较器是greater。
// 比较器在queue头文件里就有。自己实现也可，但要注意
// cmp的实现。另外如果要传入别的的比较器，必须传入Container参数，
// 用vector<T> 就好。 

typedef long long ll;
 
priority_queue<ll, vector<ll>, greater<ll> > q;
 
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char** argv) {
	int N;
	scanf("%d", &N);
	while (N--) {
		ll x;
		scanf("%d", &x);
		// 输入果子重量，并使堆初始化为N个元素。
		q.push(x); 
	}
	int ans=0;
	// 构建哈夫曼树，同时计算WPL，即加权最小路径和。
	// 这里用的是另一个计算式子，即非叶节点的权重和。
	// WPL的定义是所有叶子的路径长度乘叶子的权重之和。
	while (q.size() > 1) {
		int a=q.top();q.pop();
		int b=q.top();q.pop();
		int root=a+b; // a，b的根节点权重。
		// 由于不需要保存树的链接关系，这里的节点只保存了权重。
		q.push(root);
		ans += root;  // root 必定是非叶子节点。 
	}
	printf("%d\n", ans);
	
	return 0;
}
