#include <cstdio>
#include <map>
#include <stack>
#include <string>
#include <cassert>
#include <cstring>
#include <vector>
using namespace std;

int N; // ������
int M; // ��ѯ��

#define MAXL 100

// �������͵Ľ�㡣 
enum {
	STR,OBJ
};

struct Node {
	// ������ַ������Ƕ��� 
	int type;
	// �����str�����¼ֵ�� 
	string str;
	// ����Ƕ������¼��һ�㡣 
	map<string, Node*> val;
	
	Node(int type) {
		this->type=type;
	}
	// ��obj��һ�����ӡ� 
	void Add(string& key, Node* val) {
		assert(type==OBJ);
		assert(this->val.count(key)==0);
		this->val[key]=val;
	}
};

Node* root; // �����󣬱�֤������һ������
vector<string> path; // ��ѯ·����

// �����Ե�ָ���·���� 
void GetPath(char str[], int len) {
	path.clear();
	int i=0;
	while (i<len) {
		while (i<len && str[i]=='.') {
			++i;
		}
		if (i>=len) break;
		string buf;
		while (i<len && str[i] != '.') {
			buf.push_back(str[i]);
			++i;
		}
		path.push_back(buf);
	}
}

Node* Find() {
	// ����·�����ҡ�
	Node* r=root;
	for (int i=0;i<path.size();++i) {
		string& str=path[i];
		if (r->type == OBJ && r->val.count(str)) {
			r=r->val[str];
		} else {
			return NULL;
		}
	}
	return r;
}

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

// �������ж��룬��������һ���ַ����� 
string input;
void Read() {
	input.clear();
	while (N--) {
		char line[MAXL];
		gets(line);
		input.append(line);
	}
}


// ��i����ʼ������һ����������ַ����� 
string Parse2(string& str, int& i) {
	string buf;
	++i;
	while (i<str.length()) {
		char c=str[i];
		if (c=='\"') {
			// �ַ��������ˡ� 
			++i;
			break;
		}
		if (c=='\\') {
			// ת�����С�
			++i; 
		}
		buf.push_back(str[i]);
		++i;
	}
	return buf;
}

Node* Parse(string& str) {
	stack<Node*> stk;
	int i=0;
	Node* now;
	// now ָ��ǰ�������Ķ���
	// ��ʼ��Ϊ������ 
	now=new Node(OBJ);
	// ��ǰ����
	 
	/*
	����һ�����󣬰�������key-value�����С�
	*/ 
	while (i<str.size()) {
		// �ҵ���һ��pair�� 
		while (i<str.size() && (str[i]==','||str[i]==' '||str[i]=='{')) {
			++i;
		}
		if (i>=str.size()) {
			// �﷨�������ܡ� 
			return NULL;
		}
		// һ�������pair�б�����ˣ���һ����������ˡ� 
		if (str[i]=='}') {
			++i;
			// ��ջ���滻��ǰ����
			if (stk.empty()) {
				return now;
			}
			now=stk.top();
			stk.pop();
		} else if (str[i]=='\"') {
			// key�Ŀ�ʼ��
			string key=Parse2(str, i);
//			printf("key %s\n", key.c_str());
			
			// �ҵ�value 
			while (i<str.length() && (str[i]==' '||str[i]==':')) {
				++i;
			}
			assert(i<str.length() && (str[i]=='\"'||str[i]=='{'));
			if (str[i]=='\"') {
				// string. ֱ�ӹ����㣬�����븸�ڵ㡣 
				Node* node=new Node(STR);
				node->str=Parse2(str, i);
				now->Add(key, node);
			} else if (str[i]=='{') {
				++i;
				Node* node=new Node(OBJ);
				now->Add(key, node);
				stk.push(now);
				now=node;
				// ��ǰ������ջ����ʼ�����¶��� 
			}  
		}
	}
}

int main(int argc, char** argv) {
	scanf("%d%d",&N,&M);
	getchar(); // ��ס�������������� 
	 
	Read();
//	printf("input %s\n", input.c_str());
	
	root=Parse(input); // ��������
	
	while (M--) {
		char str[MAXL];
		scanf("%s", str);
		GetPath(str, strlen(str));
		Node* ans=Find();
		if (!ans) {
			puts("NOTEXIST");
		} else {
			int type=ans->type;
			if (type == OBJ) {
				puts("OBJECT");
			} else {
				printf("STRING %s\n", ans->str.c_str());
			}
		}
	} 
	return 0;
}
