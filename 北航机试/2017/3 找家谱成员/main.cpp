#include <algorithm>
#include <cstdio>
#include <iostream>
#include <map>
#include <string>
#include <vector>
using namespace std;

#define MAXN 505  // ���ڵ�����

map<string, int> mp1;
string mp2[MAXN];
int index;

// ����·����
vector<int> P1, P2;
int Root;
// ��¼���ڵ㣬������Ϊ-1.
int father[MAXN];
// ��¼�ڵ�����ȡ�
int depth[MAXN];

// �ַ���ת��š�
int Map(string& str) {
    if (mp1.count(str)) {
        return mp1[str];
    } else {
        mp1[str] = index;
        mp2[index] = str;
        return index++;
    }
}

// ��ȡ�Ӹ��ڵ㵽v��·����
void GetPath(int v, vector<int>& p) {
    while (v != -1) {
        p.push_back(v);
        v = father[v];
    }
    // �Ӹ��ڵ㿪ʼ��
    reverse(p.begin(), p.end());
}

/*
��Ч�ⷨ������������������LCA���ɡ�
�����ڵ㣬������ͬһ���ϣ����a�Ĳ�νϴ��a��������
����b������������������ʱ��¼�����ڵ����ȣ���Ȼ��һ����������ֱ������ͬһ���ڵ㡣
������ab���Ƚ������ab�ȽϽӽ�ʱ���졣��ʵ�ϣ����Ӷȵ���ab��LCA�ĸ߶ȣ���������޹ء�
*/
void Solve2(int a, int b) {
    // ��β
    int diff = abs(depth[a] - depth[b]);
    while (depth[a] > depth[b]) {
        a = father[a];
    }
    while (depth[b] > depth[a]) {
        b = father[b];
    }
    while (a != b) {
        a = father[a];
        b = father[b];
    }
    int lca = a;
    printf("%s %d\n", mp2[lca].c_str(), diff);
}

/*
����һ���������������ڵ㣬�����ǵ�LCA��������Ĺ������ȣ�����ڵ�Ĳ�β
˼·����¼���ڵ㣬Ȼ���ҵ������ڵ㣬��������������Ϊֹ����¼�����ڵ㵽���ڵ��·����
�Ը��ڵ�Ϊ����������·�����еĹ���ǰ׺Q���������LCA����Q�����һ��Ԫ�ء�
·���ĳ���ǡ���Ǹýڵ�Ĳ�Σ�����·������������ɣ�Ӧ�ò���ȡ����ֵ����

�㷨�ĸ��Ӷȣ��������ڵ�����֮�͵����Ժ�����
*/
void Solve(int a, int b) {
    GetPath(a, P1);
    GetPath(b, P2);
    // ������·���Ĺ���ǰ׺��
    int i = 0;
    while (i < P1.size() && i < P2.size() && P1[i] == P2[i]) {
        ++i;
    }
    int lca = P1[i - 1];
    int diff = P1.size() - P2.size();
    // �����о���ֵ��ζ������
    printf("%s %d\n", mp2[lca].c_str(), abs(diff));
}

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

int main(int argc, char** argv) {
    fill(father, father + MAXN, -1);
    fill(depth, depth + MAXN, 0);

    /*
    ����û��N������ʾ��ֻ��ÿ������2���ַ�����Ȼ���ж��Ƿ���
    ��������������
    ������뷽ʽ��CҲ��һ���ģ�һ�����������ַ���scanf("%s%s")��Ȼ�󿴿��Ƿ�������
    �������ַ�����
    */
    string s1, s2, s3;
    int a, b;
    while (cin >> s1 >> s2) {
        if (cin >> s3) {
            // �е������ַ���˵������һ�飬�����������롣
            int fa = Map(s1);
            int u = Map(s2);
            int v = Map(s3);
            father[u] = father[v] = fa;
            depth[u] = depth[v] = depth[fa] + 1;
        } else {
            // ��ѯ�����롣
            a = Map(s1);
            b = Map(s2);
        }
    }
    Solve2(a, b);

    return 0;
}
