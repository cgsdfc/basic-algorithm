#include <iostream>
#include <stack>
#include <cassert>
#include <vector> // MAXN 多大不知道 
using namespace std;

bool Judge(vector<int>& seq, int N, int M) {
	stack<int> s;
	// 当前入栈序列，即1,2,3...N 
	int i=1;
	// 当前出栈序列，即 seq[0], ..., seq[N-1] 
	int j=0;
	
	/*
	算法思路：
	总体上，用栈来模拟入栈和出栈的整个过程。
	用出栈序列来告诉我们现在应该对栈做什么操作。
	如果在出栈序列的指示下，我们能找到一个合法的栈操作序列，则出栈序列本身也是合法的。 
	 
	比如初始的时候，栈为空，则肯定应该先把1入栈，否则无法开始。
	如果这时候出栈序列当前位置也是1，说明应该马上把1出栈，否则其他元素入栈后，
	再出栈就不能使当前出栈元素为1了。
	如果当前元素不是1，说明1现在不应该出栈，因为1应该晚些再出栈。所以当前应该入栈一个新的元素，
	并且继续算法。
	上述过程应该继续下去直到出栈序列耗尽，如果中途出现无法入栈（比如入栈序列耗尽，或栈满）
	则说明，按照这个出栈序列，我们无法找到一个合法的栈操作序列，使得出栈序列被重构出来。
	说明出栈序列是非法的。
	否则，说明存在一个栈操作序列，使得出栈序列能重构，所以出栈序列就是合法的。 
	 
	模拟算法：
	1. 如果栈顶元素等于出栈序列当前元素，则应该出栈，并且出栈序列当前元素后移。
	2. 否则，应该取入栈序列当前元素入栈。如果当前栈满或者入栈元素已用完，则返回false。
	3. 如果当前栈为空，则应该取入栈序列当前元素入栈，如果当前入栈元素已用完，则返回false。
	4. 算法在栈为空，入栈序列用完，出栈序列用完时结束并返回true。 
	*/
	while (j<seq.size()) {
		if (!s.empty()) {
			int top=s.top();
			if (top == seq[j]) {
				++j;
				/*
				在所有对s进行操作的地方输出该操作，则可以得出
				一个栈操作序列，该序列可以还原出栈序列。
				*/ 
				s.pop();
			} else if (s.size() < M && i<=N) {
				s.push(i);
				++i;
			} else {
				/*
				应该入栈，但是栈满了，或者元素用完了。
				*/ 
				return false;
			}
		} else {
			// 栈空，应该入栈。
			if (i<=N) {
				s.push(i);
				++i;
			} else {
				return false;
			}
		}
	}
	// 当出栈序列为空时，栈和入栈序列都应该为空。
	/*
	因为j每次移动，s必须弹出一次；而s压栈不超过N次，所以当j移动了N次，
	则s弹了N次，所以s必须压栈了N次（否则没有足够元素来出栈），
	所以此时入栈序列必定为空（因为总共只有N个元素）。（因为一个元素
	只能入栈一次，只能出栈一次）。 
	*/ 
	assert(s.empty()); 
	return true;
}

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char** argv) {
	int M; // 栈的最大长度 。 
	int N; // 1--N N个元素。 
	int K; // 要检查的K个序列。 
	
	scanf("%d%d%d",&M,&N,&K);
	while (K--) {
		// 读入一个出栈序列。 
		vector<int> seq;
		for (int i=0;i<N;++i) {
			int x;
			scanf("%d",&x);
			seq.push_back(x);
		}
		bool ans=Judge(seq, N, M);
		printf("%s\n", ans?"YES":"NO");
	}
	return 0;
}
