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
������DFS������Ҫ�õݹ顣
*/

void DFS(int index, int start, int N, int R) {
	if (index == R) {
		// ѡ����R����
		// �����
		for (int i=0;i<ans.len;++i) {
			printf("%d%s", ans.data[i], i==ans.len-1?"\n":" ");
		}
		return; 
	}
	/*
	��ǰ��ѡ��Ԫ����index������ѡ����R-index����
	��ѡ�ķ�Χ��start--N����˱��뱣֤ ��ѡ��Χ���ڵ��ڴ�ѡԪ�ظ�����
	����N-start+1 >= R-index.
	*/
	 
	if (N-start+1 < R-index) {
		return;
	}
	
	/*
	��ǰֻ����start��N�ķ�Χѡ��
	*/
	while (start <= N) {
		/*
		ѡstart��Ȼ������start+1��Nѡ��
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
