#include <cstdio>
#include <algorithm>
using namespace std;

#define MAXN 1005
int Count[MAXN];
struct {
	int data[MAXN];
	int len;
} ans;

bool cmp(int a, int b) {
	if (Count[a] != Count[b]) {
		return Count[a] > Count[b];
	}
	return a < b;
}

// É¢ÁÐ+ÅÅÐò
int N;

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char** argv) {
	scanf("%d", &N);
	while (N--) {
		int x;
		scanf("%d", &x);
		Count[x]++;
		if (Count[x] == 1) {
			ans.data[ans.len++]=x;
		}
	}
	sort(ans.data, ans.data+ans.len, cmp);
	for (int i=0;i<ans.len;++i) {
		printf("%d %d\n", ans.data[i], Count[ans.data[i]]);
	}
	
	return 0;
}
