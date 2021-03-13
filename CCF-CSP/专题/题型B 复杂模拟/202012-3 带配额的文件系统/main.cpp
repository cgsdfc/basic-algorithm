#include <cstdio>
#include <map>
#include <vector>
#include <iostream>
#include <string>
#include <cstring>
#include <cctype>
#include <cassert>
using namespace std;

typedef long long ll;

struct Node {
	string name;
	map<string, Node*> child;
	Node* father;
	
	// ��Ŀ¼Ϊtrue�� 
	bool dir;
	// ����������� 
	ll Q1, Q2;
	// ���Ӵ�С�������С�� 
	ll size1, size2;
	// ��ͨ�ļ���С�� 
	ll filesize;
	
	Node(bool _dir) {
		father=NULL;
		dir=_dir;
		Q1=Q2=0;
		size1=size2=0;
		filesize=0;
	}
	
};

Node* root;
vector<string> Path;

void Init() {
	root=new Node(true);
}

#define MAXP 1024 

void Parse(string& str) {
	// ·��������
	Path.clear();
	int i=0;
	int len=str.size();
	while (i<len) {
		while (i<len && str[i]=='/') {
			++i;
		}
		if (i>=len) break;
		
		string p;
		while (i<len && str[i] != '/') {
			p.push_back(str[i]);
			++i;
		}
		Path.push_back(p);
	}
}

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

bool Create(string& str, ll size) {
	Parse(str);
	assert(Path.size()); // ������/�� 
	Node* p=root;
	int i=0;
	// ·�����ҡ� 
	while (i<Path.size()) {
		string& n=Path[i];
		if (!p->dir) {
			// ·���ϳ�����ͬ����ͨ�ļ���
			return false; 
		}
		// ��ʱ���ܼ������Ƿ����㣬��Ϊ�������滻�ļ��������������ļ���
		// �ļ���С��������һ����size�� 
		if (!p->child.count(n)) {
			// ·��ȱʧ�������������ļ�����ȱʧ������Ҫ�½��ļ���
			// �������м��Ŀ¼����ȱʧ�� 
			break; 
		}
		p=p->child[n];
		++i;
	}
	assert(p);
	// ����·��������˲��ҡ� ˵��·���Ǵ��ڵġ� 
	if (i == Path.size()) {
		// �ļ��Ѿ����ڣ�p�Ǿ��ļ��Ľڵ㡣
		if (p->dir) {
			return false;
		}
		// �ļ��滻�������
		ll diff=size-p->filesize;
		// ��鸸�ڵ�size1.
		Node* fa=p->father;
		assert(fa->dir);
		// ע�����==0ʱ����ʾ���ޡ� 
		if (fa && fa->Q1 && fa->size1+diff > fa->Q1) {
			return false;
		}
		// ������Ƚڵ�size2.
		while (fa) {
			if (fa->Q2 && fa->size2+diff > fa->Q2) {
				return false;
			}
			fa=fa->father;
		}
		// ��ʽ�޸��ļ�ϵͳ��
		// BUG�����ڵ��childҪ�޸ģ���Ϊ�ļ������ܸı䡣
		// ����������Ȼ�ļ����������޸ģ���Ϊ���·���Ѿ������ˡ� 
		string& name=Path.back();
		assert(p->name == name); 
		fa=p->father; 
		p->filesize=size;
		// �޸Ĵ�С�� 
		fa->size1 += diff;
		while (fa) {
			fa->size2 += diff;
			fa=fa->father;
		}
		return true;
	} 
	
	// �����ļ���
	// �ȼ����ע��p��һ�������ļ��ĸ��ڵ㣬��һ�������Ƚڵ㡣	
	if (i == Path.size()-1) {
		// �ڲ������һ����ʱʧ�ܣ�˵��p�Ǹ��ڵ㡣���ڸ��ڵ㣬Ҫ��麢���� 
		assert(p->dir);
		if (p->Q1 && p->size1 + size > p->Q1) {
			return false; // ���������㡣 
		}
	}
	// ������ȵĺ������Ƿ����㡣
	Node* fa=p;
	while (fa) {
		if (fa->Q2 && fa->size2 + size > fa->Q2) {
			return false;
		}
		fa=fa->father;
	}
	// ������㣬��ʽ�޸��ļ�ϵͳ��
	// �Ȳ���Ŀ¼��
	while (i!=Path.size()-1) {
		Node* dir=new Node(true);
		dir->name=Path[i];
		assert(!p->child.count(dir->name));
		p->child[dir->name]=dir;
		dir->father=p;
		p=dir;
		++i;
	}
	// ����p�Ǹ��ڵ��ˡ�
	Node* file=new Node(false);
	assert(i==Path.size()-1);
	file->name=Path[i];
	file->filesize=size;
	file->father=p;
	p->child[file->name]=file;
	/*
	���Ҫ�����ļ�ϵͳsize��
	*/
	fa=file->father;
	assert(fa);
	fa->size1 += size;
	while (fa) {
		fa->size2 += size;
		fa=fa->father;
	}
	return true;
}

void Print(Node* p) {
	if (!p->dir) {
		printf("%s %lld\n", p->name.c_str(), p->filesize);
	} else {
		printf("/%s size1 %lld size2 %lld Q1 %lld Q2 %lld\n", 
		p->name.c_str(), p->size1, p->size2, p->Q1, p->Q2);
		for (map<string,Node*>::iterator it=p->child.begin();it != p->child.end();++it) {
			Print(it->second);
		}
	}
}

bool Check(Node* p) {
	// ���ȫ������Ƿ����㡣
	if (!p->dir) return true;
	
	assert(p->size1 >= 0);
	assert(p->size2 >= 0);
	assert(p->size1 <= p->size2);
	
	if (p->Q1 && p->size1 > p->Q1) return false;
	if (p->Q2 && p->size2 > p->Q2) return false;
	for (map<string,Node*>::iterator it=p->child.begin();it!=p->child.end();++it) {
		if (!Check(it->second)) return false;
	}
	return true;
}

// �ͷ��ڴ档 
void Delete(Node* p) {
	if (p) {
		for (map<string,Node*>::iterator it=p->child.begin();it!=p->child.end();++it) {
			Delete(it->second);
		}
		delete p;
	}
}

bool Remove(string& str) {
	Parse(str);
	assert(Path.size()); // ����ɾ��/ 
	Node* p=root;
	int i=0;
	while (i<Path.size()) {
		// �Ե�ǰ�ڵ㣬���Һ��ӡ�
		string& n=Path[i];
		if (!p->dir) {
			// ��ǰ����Ŀ¼��
			return true; 
		}
		if (!p->child.count(n)) {
			// ��ǰ���Ӳ����ڡ�
			return true; 
		}
		p=p->child[n];
		assert(p);
		++i;
	}
	assert(p);
	if (p->dir) {
		// ɾĿ¼��ֱ������ȫ��size2���١�
		ll size2=p->size2;
		Node* fa=p->father;
		while (fa) {
			fa->size2 -= size2;
			assert(fa->size2 >= 0);
			fa=fa->father;
		}
	} else {
		// ɾ�ļ������׵�size1��С��ֱ����ȫ��size2���١�
		ll size=p->filesize;
		// �ļ����и��ڵ㡣 
		Node* fa=p->father;
		assert(fa);
		fa->size1 -= size;
		assert(fa->size1>=0);
		while (fa) {
			fa->size2 -= size;
			assert(fa->size2>=0);
			fa=fa->father;
		}
	}
	// �Ӹ��ڵ�Ĩȥ���ӡ�
	assert(p->father);
	assert(p->father->child.count(p->name)); // �����иú��ӡ� 
	p->father->child.erase(p->name);
	Delete(p);
	return true; // ���ǳɹ��� 
}

// Q1���ļ���С������ll�����������
// ���·�������50��������ס�
// ��������һ����Q��һ��û��Q���÷�50���ɺ�Qָ���йأ�
// ���Ƕ��ڻ����߼���û�����⣬û�뵽�����Բ����bug��
// ��˵�����ĳ����Ҫ�̶���ll����ô��ȫ�����ã������bug��
// �ͼ���Ƿ��в�һ�µ����⡣ 
bool Quota(string& str, ll Q1, ll Q2) {
	Parse(str);
	/*
	���ҵ���Ŀ¼��Ȼ�����ͷ�����size1��size2
	*/
	int i=0;
	Node* p=root;
	while (i<Path.size()) {
		string& n=Path[i];
		if (!p->dir) {
			return false;
		}
		if (!p->child.count(n)) {
			// ·�������ڡ� 
			return false;
		}
		p=p->child[n];
		++i;
	}
	if (!p->dir) {
		return false;
	}
//	printf("Q size1 %d size2 %d\n", p->size1, p->size2);
	
	// ���ܰ����ĵ�С�ڵ�ǰ��С�� 
	// ע�����Ϊ0��ʾ���ޡ� 
	if ((Q1 && p->size1 > Q1) || (Q2 && p->size2 > Q2)) {
		return false;
	}
	p->Q1=Q1;
	p->Q2=Q2;
	return true;
}

int main(int argc, char** argv) {
//	char str[MAXP];
	string str;
	
//	scanf("%s", str);
//	Parse(str);
//	for (int i=0;i<Path.size();++i) {
//		printf("%s\n", Path[i].c_str());
//	}
//	return 0;
	
//	freopen("./io.txt","r",stdin);
	
	Init(); // ��ش������� 
	int N;
	scanf("%d", &N);
	while (N--) {
//		getchar();
		char op;
		cin >> op;
//		scanf("%c", &op);
		ll size;
		ll Q1, Q2;
		bool ans=false;
		switch (op) {
			case 'C':
				cin >> str >> size;
//				scanf("%s%lld", str, &size);
				ans=Create(str, size);
				break;
			case 'R':
				cin >> str;
//				scanf("%s", str);
				ans=Remove(str);
				break;
			case 'Q':
				cin >> str >> Q1 >> Q2;
//				scanf("%s%lld%lld", str, &Q1, &Q2);
				ans=Quota(str, Q1, Q2);
				break;
			default:
				assert(false);
		}
//		assert(Check(root));
//		Print(root);
		puts(ans?"Y":"N");
	}
	return 0;
}
