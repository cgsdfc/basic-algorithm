#include <iostream>
#include <cstring>
using namespace std;
 
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

#define MAXN 25
struct {
	int data[MAXN];
	int len;
} ans;

/*
本节是DFS，就是要用递归。
*/

void DFS(int index, int start, int N, int R) {
	if (index == R) {
		// 选够了R个。
		// 输出。
		for (int i=0;i<ans.len;++i) {
			printf("%d%s", ans.data[i], i==ans.len-1?"\n":" ");
		}
		return; 
	}
	/*
	当前已选的元素有index个，待选的有R-index个，
	可选的范围是start--N，因此必须保证 可选范围大于等于待选元素个数。
	即，N-start+1 >= R-index.
	*/
	 
	if (N-start+1 < R-index) {
		return;
	}
	
	/*
	当前只能在start到N的范围选择。
	*/
	while (start <= N) {
		/*
		选start，然后后面从start+1到N选择。
		*/
		ans.data[ans.len++]=start; 
		DFS(index+1, start+1, N, R);
		ans.len--;
		++start;
	} 
}

int main(int argc, char** argv) {
	int N;
	int R;
	
	while (scanf("%d%d", &N, &R) != EOF) {
		memset(&ans, 0, sizeof(ans));
		DFS(0, 1, N, R);
	}
	return 0;
}
