#include <cstdio>
#include <string>
#include <vector>
#include <cstring>
#include <cctype>
using namespace std;

enum {
	LIT, // ����ֵ��
	STR, // str
	INT, // int
	PATH, // path
};

const char Name[5][5]={"","str","int","path"};

struct Node {
	int type;
//	���type��LIT������������ֵ�� 
	string val;
};

struct Rule {
//	·���ĸ����֡� 
	vector<Node> item;
	// �Ƿ���б�ܽ�β���ض���б�ܿ�ͷ��item֮��ض�����б�ܡ� 
	bool endslash;
	// �������� 
	string name;
	Rule() {
		this->endslash=false;
	}
};

int N; // �������� 
int M; // ��ѯ���� 

vector<Rule> rules;
#define MAXL 105 // ÿ�в�������ô�ࡣ

int Type(string& s) {
	if (s=="int") {
		return INT;
	}
	if (s=="str") {
		return STR;
	}
	if (s=="path") {
		return PATH;
	}
	return -1;
}

Rule ParseRule(char str[], int len) {
	// ����·����
	int i=0;
	Rule r;

	while (i<len) {
		while (i<len && str[i]=='/') {
			++i;
		}
		if (i>=len) {
			break;
		}
		if (str[i] == '<') {
			++i;
			string s;
			while (i<len && str[i]!='>') {
				s.push_back(str[i]);
				++i;
			}
			++i; // '>'
			int type=Type(s);
			Node n;
			n.type=type;
			r.item.push_back(n);
		} else {
			// LIT.
			string s;
			while (i<len && str[i]!='/') {
				s.push_back(str[i]);
				++i;
			}
			Node n;
			n.type=LIT;
			n.val=s;
			r.item.push_back(n);
		}
	}
	// ע�⣬item����Ϊ�գ���ֻ��һ��б�ܡ� 
	if (str[len-1]=='/') {
		r.endslash=(r.item.empty() || r.item.back().type != PATH);
	}
	return r;
}

void PrintRule(Rule& r) {
	for (int i=0;i<r.item.size();++i) {
		putchar('/');
		Node& n=r.item[i];
		switch (n.type) {
			case LIT:
				printf("%s", n.val.c_str());
				break;
			default:
				printf("<%s>", Name[n.type]);
				break;
		}
	}
	if (r.endslash) {
		putchar('/');
	}
	puts("");
}

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

string Clean(string& s) {
	// ����ȥ��ǰ��������֣������ȫ���򷵻�0. 
	int i=0;
	while (i<s.size()-1 && s[i]=='0') {
		++i;
	}
	return s.substr(i);
}

/*
�����bug��
�������ط���==д��=�������Ƚ���������߱���ӿո񰡡�
*/
 
vector<string> params;
bool Match(Rule& r, char str[], int len) {
//	puts(r.name.c_str());
	/*
	ɨ���������в��֣���ÿһ������̰��ƥ������url��
	�����һ���ֲ�ƥ�䣬��false��
	ȫ��ƥ����Ϻ󣬴���endslash���������url��endslashҪһ�¡�
	���url��������false��
	*/
	 
	params.clear();
	int j=0;
	for (int i=0;i<r.item.size();++i) {
		while (j<len && str[j]=='/') {
			++j;
		}
		if (j>=len) {
//			puts("Too short");
			return false;
		}
		Node& n=r.item[i];
		int type=n.type;
		string buf;
		if (type==LIT) {
			while (j<len && str[j]!='/') {
				buf.push_back(str[j]);
				++j;
			}
			if (buf != n.val) {
//				puts("lit false");
//				printf("buf %s val %s\n", buf.c_str(),n.val.c_str());
				return false;
			}
		} else {
			if (type == INT) {
				while (j<len && isdigit(str[j])) {
					buf.push_back(str[j]);
					++j;
				}
				buf=Clean(buf);
			} else if (type == STR) {
				while (j<len && str[j]!='/') {
					buf.push_back(str[j]);
					++j;
				}
			} else {
				// Path
				while (j<len) {
					buf.push_back(str[j]);
					++j;
				}
			}
//			printf("buf %s\n", buf.c_str());
			
			if (buf.empty()) {
//				puts("param false");
				return false; // ����ƥ����ַ����� 
			}
			params.push_back(buf);
		}
	}
//	printf("rule end %s endslash %d j %d len %d\n", r.name.c_str(), (int)r.endslash,j,len);
	
	
	if (j==len) {
		return !r.endslash;
	}
	if (j==len-1) {
		bool endslash=(str[j]=='/');
		return endslash==r.endslash;
	}
	return false;
}

int Match2(char str[], int len) {
//	printf("str %s\n", str);
	
	for (int i=0;i<rules.size();++i) {
		if (Match(rules[i], str, len)) {
			return i;
		}
	}
	return -1;
}

int main(int argc, char** argv) {
	scanf("%d%d",&N,&M);
	while (N--) {
		char str[MAXL], name[MAXL];
		scanf("%s%s",str,name);
		Rule r=ParseRule(str, strlen(str));
		r.name=name;
		rules.push_back(r);
	}

	while (M--) {
		char str[MAXL];
		scanf("%s", str);
		int ans=Match2(str, strlen(str));
		if (ans==-1) {
			puts("404");
		} else {
			Rule& r=rules[ans];
			printf("%s", r.name.c_str());
			for (int i=0;i<params.size();++i) {
				printf(" %s", params[i].c_str());
			}
			puts("");
		}
	}
	
#if 0
	puts("");
	for (int i=0;i<rules.size();++i) {
		PrintRule(rules[i]);
	}
#endif

	return 0;
}
