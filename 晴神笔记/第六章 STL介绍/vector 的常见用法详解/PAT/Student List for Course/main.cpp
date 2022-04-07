#include <algorithm>
#include <cstring>
#include <iostream>
#include <vector>
using namespace std;
/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

// 这两道题考的其实是Map反转问题，即把Map的value和key反转，冗余的部分用list保存。

#define MAXK (2500 + 5)
struct Student {
    char name[10];
};

bool cmp(Student a, Student b) {
    return strcmp(a.name, b.name) < 0;
}

vector<Student> course[MAXK];

void Add(int cid, Student stu) {
    course[cid].push_back(stu);
}

void Print(int cid) {
    vector<Student>& c = course[cid];
    printf("%d %d\n", cid, c.size());
    sort(c.begin(), c.end(), cmp);
    for (int i = 0; i < c.size(); ++i) {
        printf("%s\n", c[i].name);
    }
}

int main(int argc, char** argv) {
    int N, K;
    scanf("%d%d", &N, &K);
    for (int i = 0; i < N; ++i) {
        Student s;
        int num;
        scanf("%s%d", s.name, &num);
        for (int j = 0; j < num; ++j) {
            int cid;
            scanf("%d", &cid);
            Add(cid, s);
        }
    }
    for (int i = 0; i < K; ++i) {
        int cid = i + 1;
        Print(cid);
    }
    return 0;
}
