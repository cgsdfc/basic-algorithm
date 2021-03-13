#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn=1010;
int toll[25];

struct Record {
	char name[25];
	int month, dd, hh, mm;
	bool status;
} rec[maxn],temp;

bool cmp(Record a, Record b) {
	int s=strcmp(a.name, b.name);
	if (s!=0) return s<0;
	else if (a.month!=b.month) return a.month<b.month;
	else if (a.dd!=b.dd) return a.dd<b.dd;
	else if (a.hh!=b.hh) return a.hh-b.hh;
	else return a.mm<b.mm;
}

void get_ans(int on, int off, int& time, int& money) {
	temp=rec[on];
	while (temp.dd<rec[off].dd || temp.hh<rec[off].hh||r)
}
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]) {
	return 0;
}
