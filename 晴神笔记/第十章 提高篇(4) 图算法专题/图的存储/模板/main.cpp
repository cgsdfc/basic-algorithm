#include <cstdio>
#include <vector> // һ����vectorʵ�֡� 
using namespace std;
 
/*
ͼ�Ĵ洢��
1. �ڽӾ���O(V^2)���ʺϽڵ���С��1000.
	��Ȩ���ھ����Ԫ���С�
	 
2. �ڽӱ�O(V+E)���ʺϽڵ�������1000.
	��Ȩ��������Ԫ���С� 
*/

#define MAXN 100 // �ڵ������ޡ�

/*
���i->j����i��һ�����ߵ�j����G[i][j]��ŵ��Ǹñߵı�Ȩ������������ֵ�����������
��������ͼ�������i->j�������j->i����������ͼ�ľ����ǶԳƾ��� 
*/
 
int G[MAXN][MAXN];

/*
�ӱ߲�����
�޸Ķ�Ӧ�ľ���Ԫ�أ�����Ҫ�ӱ� i->j����ȨΪ w����
*/
void Add(int i, int j, int w) {
	G[i][j]=w;
} 

/*
Adj��vector���飬Adj�ĳ��ȵ��ڽڵ�������ÿ���ڵ�i���������еĳ�����Adj[i] �С�
�����������ߵ��յ��ţ�����int��������һ���ṹ�� Node����¼�ߵı�Ȩ���յ��š�
*/
 
vector<int> Adj[MAXN];

// һ���ߵ���Ϣ�� 
struct Node {
	int v; // �յ㡣
	int w; // Ȩ�ء�
	// ������������ӱߡ�
	Node(int _v, int _w) {
		v=_v;
		w=_w;
	} 
};

vector<Node> Adj2[MAXN];

/*
�ӱ߲�����
���磬Ҫ�ӱ� i->j����ȨΪw����
1. �ޱ�Ȩ��
*/
void Add2(int i, int j) {
	Adj[i].push_back(j);
}
/*
2. �б�Ȩ��
*/
void Add3(int i, int j, int w) {
	Adj2[i].push_back(Node(j, w));
}
/*
3. ����ͼ�ӱ� i<->j�����б�Ȩͬ�� 
*/
void Add4(int i, int j) {
	Adj[i].push_back(j);
	Adj[j].push_back(i);
}

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char** argv) {
	return 0;
}
