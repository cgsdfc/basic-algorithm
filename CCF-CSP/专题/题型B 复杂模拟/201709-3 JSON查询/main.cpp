#include <cstdio>
#include <map>
#include <stack>
#include <string>
#include <cassert>
#include <cstring>
#include <vector>
using namespace std;

int N; // 行数。
int M; // 查询。

#define MAXL 100

// 两种类型的结点。 
enum {
	STR,OBJ
};

struct Node {
	// 标记是字符串还是对象。 
	int type;
	// 如果是str，则记录值。 
	string str;
	// 如果是对象，则记录下一层。 
	map<string, Node*> val;
	
	Node(int type) {
		this->type=type;
	}
	// 给obj加一个对子。 
	void Add(string& key, Node* val) {
		assert(type==OBJ);
		assert(this->val.count(key)==0);
		this->val[key]=val;
	}
};

Node* root; // 根对象，保证输入是一个对象。
vector<string> path; // 查询路径。

// 解析以点分隔的路径。 
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
	// 根据路径查找。
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

// 把所有行读入，并且连成一个字符串。 
string input;
void Read() {
	input.clear();
	while (N--) {
		char line[MAXL];
		gets(line);
		input.append(line);
	}
}


// 从i处开始解析出一个引号里的字符串。 
string Parse2(string& str, int& i) {
	string buf;
	++i;
	while (i<str.length()) {
		char c=str[i];
		if (c=='\"') {
			// 字符串结束了。 
			++i;
			break;
		}
		if (c=='\\') {
			// 转义序列。
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
	// now 指向当前被解析的对象。
	// 初始化为根对象。 
	now=new Node(OBJ);
	// 当前对象。
	 
	/*
	解析一个对象，把它看做key-value的序列。
	*/ 
	while (i<str.size()) {
		// 找到下一个pair。 
		while (i<str.size() && (str[i]==','||str[i]==' '||str[i]=='{')) {
			++i;
		}
		if (i>=str.size()) {
			// 语法错，不可能。 
			return NULL;
		}
		// 一个对象的pair列表结束了，即一个对象结束了。 
		if (str[i]=='}') {
			++i;
			// 出栈，替换当前对象。
			if (stk.empty()) {
				return now;
			}
			now=stk.top();
			stk.pop();
		} else if (str[i]=='\"') {
			// key的开始。
			string key=Parse2(str, i);
//			printf("key %s\n", key.c_str());
			
			// 找到value 
			while (i<str.length() && (str[i]==' '||str[i]==':')) {
				++i;
			}
			assert(i<str.length() && (str[i]=='\"'||str[i]=='{'));
			if (str[i]=='\"') {
				// string. 直接构造结点，并插入父节点。 
				Node* node=new Node(STR);
				node->str=Parse2(str, i);
				now->Add(key, node);
			} else if (str[i]=='{') {
				++i;
				Node* node=new Node(OBJ);
				now->Add(key, node);
				stk.push(now);
				now=node;
				// 当前对象入栈，开始解析新对象。 
			}  
		}
	}
}

int main(int argc, char** argv) {
	scanf("%d%d",&N,&M);
	getchar(); // 记住这个恶心玩儿！！ 
	 
	Read();
//	printf("input %s\n", input.c_str());
	
	root=Parse(input); // 建立对象。
	
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
