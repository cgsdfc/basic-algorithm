#include <cstdio>
#include <cctype>
#include <cstring>
#include <cassert>
#include <stack>
#include <map>
using namespace std;

typedef map<string,int> Map;

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

const int MAXL=1005;
char str[MAXL];
Map lmp, rmp;
typedef Map::iterator It;

void Print(int l, int r) {
	while (l<=r) {
		putchar(str[l]);
		++l;
	}
	puts("");
}

void PM(Map& mp) {
	for (It it=mp.begin();it!=mp.end();++it) {
		printf("%s %d\n", it->first.c_str(), it->second);
	}
}

void Merge(Map& a, Map& b, int n) {
	// a+=b*n;
	for (It it=b.begin();it!=b.end();++it) {
		a[it->first] += it->second*n;
	} 
}

int FindNum(int& i, int right) {
	if (i<=right && isdigit(str[i])) {
		int n=0;
		while (i<=right && isdigit(str[i])) {
			n=n*10+(str[i]-'0');
			++i;
		}
		return n;
	}
	return 1;
}

Map Parse4(int left, int right) {
	/*
	把一个化学式看做一些项的序列。 
	*/
	stack<Map*> stk;
	// 顶层列表计数。 
	Map* now=new Map;
	int i=left;
	while (i<=right) {
		if (str[i]=='(') {
			// 开始新的列表的计数，保存旧的map。
			stk.push(now);
			now=new Map;
			++i; 
		} else if (str[i]==')') {
			// 当前列表计数完毕。
			++i;
			if (stk.empty()) {
				// 当前的列表就是顶级。
				break; 
			} else {
				int n=FindNum(i, right);
				Map* fa=stk.top();
				stk.pop();
				// 把当前列表合并到上一级列表。 
				Merge(*fa, *now, n);
				delete now;
				now=fa;
			}
		} else {
			// 简单元素，即Na或者H。 
			assert(isupper(str[i]));
			string elem;
			elem.push_back(str[i]);
			++i;
			if (i<=right && islower(str[i])) {
				elem.push_back(str[i]);
				++i;				
			}
			int n=FindNum(i, right);
			(*now)[elem] += n;
		}
	}
//	Print(left, right);
//	PM(*now);
	return *now;
}

void Parse3(Map& mp, int left, int right) {
	// 处理单个化学式。
	int coef=1;
	if (isdigit(str[left])) {
		coef=0;
		while (left <= right && isdigit(str[left])) {
			coef=coef*10+(str[left]-'0');
			++left;
		}
	}
	Map tot=Parse4(left, right);
	Merge(mp, tot, coef);
}

void Parse2(Map& mp, int left, int right) {
	// 分割成+分割的多个公式。
	int i=left;
	while (i <= right) {
		int j=i;
		while (j<=right && str[j]!='+') {
			++j;
		}
		Parse3(mp, i, j-1);
		i=j+1;
	}
}

bool Parse(int left, int right) {
	// 分成=分割的两个公式。
	lmp.clear();
	rmp.clear();
	
	int i=left;
	while (i<=right && str[i] != '=') {
		++i;
	}
	Parse2(lmp, left, i-1);
	Parse2(rmp, i+1, right);
#if 0
	PM(lmp);
	puts("");
	PM(rmp);
#endif

	return lmp == rmp;
}

int main(int argc, char** argv) {
	int N;
	scanf("%d",&N);
	getchar();
	while (N--) {
		fgets(str, sizeof(str), stdin);
		bool ans=Parse(0, strlen(str)-2);
		puts(ans?"Y":"N");
	}
	return 0;
}
