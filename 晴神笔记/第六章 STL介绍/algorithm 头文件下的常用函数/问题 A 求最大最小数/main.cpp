#include <iostream>
#include <algorithm>
using namespace std;
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

#define MAX (1000000+1)

int main(int argc, char** argv) {
	int N;
	while (scanf("%d",&N) != EOF) {
		int Max=-MAX;
		int Min=MAX;
		while (N--) {
			int x;
			scanf("%d",&x);
			Max=max(Max, x);
			Min=min(Min, x);
		}
		printf("%d %d\n", Max, Min);
	}
	return 0;
}
