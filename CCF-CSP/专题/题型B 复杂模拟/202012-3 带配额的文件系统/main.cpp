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
	
	// 是目录为true。 
	bool dir;
	// 孩子配额，后代配额。 
	ll Q1, Q2;
	// 孩子大小，后代大小。 
	ll size1, size2;
	// 普通文件大小。 
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
	// 路径解析。
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
	assert(Path.size()); // 不允许/。 
	Node* p=root;
	int i=0;
	// 路径查找。 
	while (i<Path.size()) {
		string& n=Path[i];
		if (!p->dir) {
			// 路径上出现了同名普通文件。
			return false; 
		}
		// 此时不能检查配额是否满足，因为可能是替换文件，而不是增加文件。
		// 文件大小的增量不一定是size。 
		if (!p->child.count(n)) {
			// 路径缺失，可能是最后的文件部分缺失，就是要新建文件，
			// 可能是中间的目录部分缺失。 
			break; 
		}
		p=p->child[n];
		++i;
	}
	assert(p);
	// 整个路径都完成了查找。 说明路径是存在的。 
	if (i == Path.size()) {
		// 文件已经存在，p是旧文件的节点。
		if (p->dir) {
			return false;
		}
		// 文件替换，检查配额。
		ll diff=size-p->filesize;
		// 检查父节点size1.
		Node* fa=p->father;
		assert(fa->dir);
		// 注意配额==0时，表示无限。 
		if (fa && fa->Q1 && fa->size1+diff > fa->Q1) {
			return false;
		}
		// 检查祖先节点size2.
		while (fa) {
			if (fa->Q2 && fa->size2+diff > fa->Q2) {
				return false;
			}
			fa=fa->father;
		}
		// 正式修改文件系统。
		// BUG：父节点的child要修改！因为文件名可能改变。
		// 但是这里显然文件名不可能修改，因为这个路径已经存在了。 
		string& name=Path.back();
		assert(p->name == name); 
		fa=p->father; 
		p->filesize=size;
		// 修改大小。 
		fa->size1 += diff;
		while (fa) {
			fa->size2 += diff;
			fa=fa->father;
		}
		return true;
	} 
	
	// 新增文件。
	// 先检查配额，注意p不一定是新文件的父节点，但一定是组先节点。	
	if (i == Path.size()-1) {
		// 在查找最后一部分时失败，说明p是父节点。对于父节点，要检查孩子配额。 
		assert(p->dir);
		if (p->Q1 && p->size1 + size > p->Q1) {
			return false; // 孩子配额不满足。 
		}
	}
	// 检查组先的后代配额是否满足。
	Node* fa=p;
	while (fa) {
		if (fa->Q2 && fa->size2 + size > fa->Q2) {
			return false;
		}
		fa=fa->father;
	}
	// 配额满足，正式修改文件系统。
	// 先补充目录。
	while (i!=Path.size()-1) {
		Node* dir=new Node(true);
		dir->name=Path[i];
		assert(!p->child.count(dir->name));
		p->child[dir->name]=dir;
		dir->father=p;
		p=dir;
		++i;
	}
	// 现在p是父节点了。
	Node* file=new Node(false);
	assert(i==Path.size()-1);
	file->name=Path[i];
	file->filesize=size;
	file->father=p;
	p->child[file->name]=file;
	/*
	最后要增加文件系统size。
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
	// 检查全部配额是否满足。
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

// 释放内存。 
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
	assert(Path.size()); // 不许删除/ 
	Node* p=root;
	int i=0;
	while (i<Path.size()) {
		// 对当前节点，查找孩子。
		string& n=Path[i];
		if (!p->dir) {
			// 当前不是目录。
			return true; 
		}
		if (!p->child.count(n)) {
			// 当前孩子不存在。
			return true; 
		}
		p=p->child[n];
		assert(p);
		++i;
	}
	assert(p);
	if (p->dir) {
		// 删目录，直到根，全部size2减少。
		ll size2=p->size2;
		Node* fa=p->father;
		while (fa) {
			fa->size2 -= size2;
			assert(fa->size2 >= 0);
			fa=fa->father;
		}
	} else {
		// 删文件，父亲的size1减小，直到根全部size2减少。
		ll size=p->filesize;
		// 文件总有父节点。 
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
	// 从父节点抹去孩子。
	assert(p->father);
	assert(p->father->child.count(p->name)); // 必须有该孩子。 
	p->father->child.erase(p->name);
	Delete(p);
	return true; // 总是成功。 
}

// Q1和文件大小必须用ll，否则溢出。
// 导致分数卡在50的罪魁祸首。
// 测试数据一半有Q，一半没有Q，得分50怀疑和Q指令有关，
// 但是都在怀疑逻辑有没有问题，没想到是语言层面的bug，
// 这说明如果某变量要固定用ll，那么就全部都用，如果有bug，
// 就检查是否有不一致的问题。 
bool Quota(string& str, ll Q1, ll Q2) {
	Parse(str);
	/*
	先找到该目录，然后检查释放满足size1，size2
	*/
	int i=0;
	Node* p=root;
	while (i<Path.size()) {
		string& n=Path[i];
		if (!p->dir) {
			return false;
		}
		if (!p->child.count(n)) {
			// 路径不存在。 
			return false;
		}
		p=p->child[n];
		++i;
	}
	if (!p->dir) {
		return false;
	}
//	printf("Q size1 %d size2 %d\n", p->size1, p->size2);
	
	// 不能把配额改的小于当前大小。 
	// 注意配额为0表示无限。 
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
	
	Init(); // 务必创建根。 
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
