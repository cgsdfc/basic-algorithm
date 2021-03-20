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

// �жϿ��С� 
bool Empty(string& str) {
	for (int i=0;i<str.length();++i) {
		if (!isspace(str[i])) return false;
	}
	return true;
}

void Read() {
	// �������е��С� 
	string line;
	while (getline(cin, line)) {
		lines.push_back(line);
	}
}

/*
ע�⵽��Ŀ�����������Ӻ�ǿ������Ƕ�ף�����Ƕ�ײ�����1�㣬����
����ֱ�Ӱѳ����ӻ���ǿ���ķ�Χ�ٳ�������Ϊ����Ƕ�׳���1�㣬����
��һ�������ӵĿ�ʼ��ֱ������������ˣ��Ϳ����ˣ������ģ�����ǿ��Ҳ��ͬ��
�����ͱȽ����״����ˣ������ע�⵽��һ�㣬��Ϊ��������Ƕ�ף��Ǿ��鷳���ˡ�
��Χ�ٳ������õݹ鴦���ɡ�
ע���ǿ����ʱ��������һ���»��ߺ�Ҫ��һ�����ҵڶ����»��ߡ� 
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
			int j=i+1; // ע�⣬i��������»��ߣ�Ҫ��i����ĵ�һ���»��ߡ� 
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
			// ��ͨ�ַ���ֱ�������
			putchar(ch);
			++i; 
		}
	}
}

// ����һ�У���β������س��� 
void Block(string& str, int pos) {
	ParseBlock(str, pos, str.length()-1);
}

void Clean(string& str, int& i) {
	// ��i��ʼȥ�������Ŀո�
	while (i<str.length() && str[i]==' ') {
		++i;
	}
}

void Title(string& str) {
	int i=0;
	while (i<str.length() && str[i]=='#') {
		++i;
	}
	int n=i; // �ȼ��� 
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
	// ��������С�
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
