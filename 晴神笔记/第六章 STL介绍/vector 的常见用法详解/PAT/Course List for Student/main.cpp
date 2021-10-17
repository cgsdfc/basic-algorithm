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
这道题的关键是对学生名字进行hash，用map也好，直接映射也好，
必须实现在O(1)或者O(logn)查询学生姓名，否则复杂度高的难以想象。
*/

vector<int> students[MAXN];

// 对学生名字进行散列。
int Hash(char name[], int len) {
    int ans = 0;
    for (int i = 0; i < 3; ++i) {
        ans = ans * 26 + name[i] - 'A';
    }
    return ans * 10 + name[len - 1] - '0';
}

// 表示一个学生选了一个课。
void Insert(char name[], int len, int cid) {
    int h = Hash(name, len);
    assert(0 <= h && h < MAXN);
    students[h].push_back(cid);
}

// 打印一个学生的全部课程。
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
