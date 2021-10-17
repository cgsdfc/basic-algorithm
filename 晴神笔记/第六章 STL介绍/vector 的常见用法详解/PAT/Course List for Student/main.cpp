#include <algorithm>
#include <assert.h>
#include <iostream>
#include <math.h>
#include <string.h>
#include <vector>
using namespace std;

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

#define MAXN (26 * 26 * 26 * 10 + 5)

/*
�����Ĺؼ��Ƕ�ѧ�����ֽ���hash����mapҲ�ã�ֱ��ӳ��Ҳ�ã�
����ʵ����O(1)����O(logn)��ѯѧ�������������Ӷȸߵ���������
*/

vector<int> students[MAXN];

// ��ѧ�����ֽ���ɢ�С�
int Hash(char name[], int len) {
    int ans = 0;
    for (int i = 0; i < 3; ++i) {
        ans = ans * 26 + name[i] - 'A';
    }
    return ans * 10 + name[len - 1] - '0';
}

// ��ʾһ��ѧ��ѡ��һ���Ρ�
void Insert(char name[], int len, int cid) {
    int h = Hash(name, len);
    assert(0 <= h && h < MAXN);
    students[h].push_back(cid);
}

// ��ӡһ��ѧ����ȫ���γ̡�
void Print(char name[], int len) {
    int h = Hash(name, len);
    vector<int>& stu = students[h];

    printf("%s %d", name, stu.size());
    sort(stu.begin(), stu.end());
    for (int i = 0; i < stu.size(); ++i) {
        printf(" %d", stu[i]);
    }
    printf("\n");
}

int main(int argc, char** argv) {
    int N;
    int K;

    scanf("%d%d", &N, &K);
    for (int i = 0; i < K; ++i) {
        int cid;
        int num;
        scanf("%d%d", &cid, &num);
        while (num--) {
            char name[10];
            scanf("%s", name);
            Insert(name, strlen(name), cid);
        }
    }

    for (int i = 0; i < N; ++i) {
        char name[10];
        scanf("%s", name);
        Print(name, strlen(name));
    }
    return 0;
}
