#include <algorithm>
#include <cstdio>
#include <vector>
using namespace std;
/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

#define MAXN 100
// int parent[MAXN];
// bool leaf[MAXN]; // true ��ʾ��Ҷ�ӽڵ㡣

const int root = 1;

int N;  // �ڵ�����

// void Init() {
//	fill(parent, parent+MAXN, -1);
//	fill(leaf, leaf+MAXN, true);
//}

/*
���������ߵķ���ʱ�临�Ӷ���nƽ����
����ȡ����BFS�����ߴ���̵�DFS��
ʱ�䶼��n���ռ�Ļ������ÿ��ǡ�
codeup�����ݽ�����nƽ���㷨���ᳬʱ��
�����ŵ���ʡ�ڴ棬���븴�Ӷȸ��͡�
*/

// int TreeHeight() {
//	int ans=0; // �����ĸߡ�
//	for (int i=1;i<=N;++i) {
//		if (leaf[i]) {
//			int hi=1;
//			int p=i;
//			while (p != root) {
//				p=parent[p];
//				++hi;
//			}
//			if (hi > ans) {
//				ans=hi;
//			}
////			printf("%d hi %d\n", i, hi);
//		}
//	}
//	return ans;
//}

// ��Ϊû��������ֱ�����������Ƕ�����ĺ����б�Ҳ��ͼ���ڽӱ�
vector<int> node[MAXN];

/*
DFS ���������߶ȣ�
1. ������H=0
2. �ǿ�����H=max{Hi,...}+1��Hi�������߶ȡ�

����ĿҪ����ĸ߶���0����1ʱ���ɸ��������DFS�ķ���ֵ��һ��
*/

int DFS(int root) {
    if (node[root].empty()) {
        // Ҷ�ڵ㡣�߽硣
        return 1;
    }
    int ans = -1;
    for (int i = 0; i < node[root].size(); ++i) {
        int h = DFS(node[root][i]);
        ans = max(ans, h);
    }
    return ans + 1;
}

int main(int argc, char** argv) {
    //	Init();
    scanf("%d", &N);
    int a, b;
    while (scanf("%d%d", &a, &b) != EOF) {
        // b��a���ӽڵ㡣
        //		parent[b]=a;
        //		leaf[a]=false;
        node[a].push_back(b);
    }
    //	int ans=TreeHeight();
    int ans = DFS(root);
    printf("%d\n", ans);

    return 0;
}
