#include <cstdio>
#include <cctype>
#include <cstring>
#include <vector>
#include <string>
#include <cassert>
#include <stack>
#include <utility>
#include <iostream>
using namespace std;

vector<string> lines;
int N;

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

// 判断空行。 
bool Empty(string& str) {
	for (int i=0;i<str.length();++i) {
		if (!isspace(str[i])) return false;
	}
	return true;
}

void Read() {
	// 输入所有的行。 
	string line;
	while (getline(cin, line)) {
		lines.push_back(line);
	}
}

/*
注意到题目条件，超链接和强调可以嵌套，但是嵌套不超过1层，所以
可以直接把超链接或者强调的范围抠出来，因为不能嵌套超过1层，所以
从一个超链接的开始端直接搜索其结束端，就可以了，不会错的；对于强调也是同理。
这样就比较容易处理了，如果不注意到这一点，以为可以无限嵌套，那就麻烦多了。
范围抠出来后，用递归处理即可。
注意抠强调的时候，遇到第一个下划线后要加一，再找第二个下划线。 
*/
 
void ParseBlock(string& str, int L, int R);

void ParseLink(string& str, int L1, int R1, int L2, int R2) {
	printf("<a href=\"");
	// link
	ParseBlock(str, L2+1,R2-1);
	printf("\">");
	// text
	ParseBlock(str, L1+1,R1-1);
	printf("</a>");
}

void ParseEm(string& str, int L, int R) {
	assert(str[L]=='_');
	assert(str[R]=='_');
	printf("<em>");
	ParseBlock(str, L+1, R-1);
	printf("</em>");
}

void ParseBlock(string& str, int L, int R) {
	int i=L;
	while (i<=R) {
		char ch=str[i];
		if (ch == '_') {
			int j=i+1; // 注意，i本身就是下划线，要找i后面的第一个下划线。 
			while (j<=R && str[j] != '_') {
				++j;
			}
			ParseEm(str, i, j);
			i=j+1;
		} else if (ch == '[') {
			int j=i;
			while (j<=R && str[j] != ']') {
				++j;
			}
			assert(j<=R && str[j]==']');
			assert(j+1<=R && str[j+1]=='(');
			int k=j;
			while (k<=R && str[k] != ')') {
				++k;
			}
			assert(k<=R && str[k]==')');
			ParseLink(str, i, j, j+1, k);
			i=k+1;
		} else {
			// 普通字符，直接输出。
			putchar(ch);
			++i; 
		}
	}
}

// 处理一行，结尾不输出回车。 
void Block(string& str, int pos) {
	ParseBlock(str, pos, str.length()-1);
}

void Clean(string& str, int& i) {
	// 从i开始去掉连续的空格。
	while (i<str.length() && str[i]==' ') {
		++i;
	}
}

void Title(string& str) {
	int i=0;
	while (i<str.length() && str[i]=='#') {
		++i;
	}
	int n=i; // 等级。 
	Clean(str, i);
	printf("<h%d>", n);
	Block(str, i);
	printf("</h%d>\n", n);
}

void Ulist(int& i) {
	puts("<ul>");
	while (i<N && lines[i].size() && lines[i][0] == '*') {
		string& str=lines[i];
		int j=1;
		Clean(str, j);
		printf("<li>");
		Block(str, j);
		printf("</li>\n");
		++i;
	}
	puts("</ul>");
}

void Para(int& i) {
	printf("<p>");
	Block(lines[i], 0);
	// 先输出首行。
	++i; 
	while (i<N && !Empty(lines[i])) {
		printf("\n");
		Block(lines[i], 0);
		++i;
	}
	printf("</p>\n");
}

int main(int argc, char** argv) {
	Read();
	N=lines.size(); 
	int i=0;
	while (i<N) {
		while (i<N && Empty(lines[i])) {
			++i;
		}
		if (i>=N) {
			break;
		}
		string& str=lines[i];
		assert(str.length());
		if (str[0]=='#') {
			Title(str);
			++i;
		} else if (str[0] == '*') {
			Ulist(i);
		} else {
			Para(i);
		}
	}
	return 0;
}
