#include <cctype>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <queue>
using namespace std;

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

#define MAXN (100000 + 5)

// i�Žڵ�ĸ��׵��±꣬0��ʾû�и��ס��ڵ��Ŵ�1��ʼ��
int Parent[MAXN];

/*
����a�Ƿ�Ϊb�����ȡ�
*/
bool IsAncestor(int a, int b) {
    while (b) {
        if (Parent[b] == a) { return true; }
        b = Parent[b];
    }
    return false;
}

void Print(int N) {
    for (int i = 1; i <= N; ++i) {
        printf("%d p %d\n", i - 1, Parent[i] - 1);
    }
}

struct cmp {
    // �����ڵ��С�ں�����
    bool operator()(int a, int b) {
        if (a == b) return false;
        if (!Parent[a]) {
            // a�Ǹ������ȼ���ߡ�
            return false;
        }
        if (!Parent[b]) {
            // b�Ǹ���
            return true;
        }
        if (IsAncestor(a, b)) {
            // a�����ȣ�a>b
            return false;
        }
        if (IsAncestor(b, a)) {
            // b�����ȣ�b>a
            return true;
        }
        // ����û�����ȹ�ϵ�����ֵ���
        // ���С�������ȿ�ʼ����С�����ȼ��ߡ�
        return a > b;
    }
};

/*
���Ӷȣ�
���ѣ�NlogN��NΪ���������ڵ�������ÿ�αȽϲ��������Ӷ����������ĸ߶ȣ���logN��
�ʽ��Ѹ��Ӷ�Ϊ N*logN*logN��
�����ӶȺͽ���һ���������򣩣����ܵĸ��ӶȾ��ǣ�

        N*(logN)^2
*/

int main(int argc, char** argv) {
    freopen("./in.txt", "r", stdin);

    int N;
    while (scanf("%d", &N) != EOF) {
        getchar();
        //		printf("N %d\n", N);

        priority_queue<int, vector<int>, cmp> q;
        memset(Parent, 0, sizeof(Parent));

        for (int i = 0; i < N; ++i) {
            int p;  // ��������
            scanf("Task%d", &p);
            //			printf("p %d\n", p);

            ++p;  // 0=>1.

            string str;
            getline(cin, str);
            //			printf("%s\n", str.c_str());

            if (str == "(NULL)") {
                //  û�к��ӡ�
            } else {
                // �ҳ����к������񣨺������񣩣��������������������ִ���
                int j = 0;
                while (j < str.size()) {
                    while (j < str.size() && !isdigit(str[j])) {
                        ++j;
                    }
                    if (j == str.size()) break;
                    int num = 0;
                    while (j < str.size() && isdigit(str[j])) {
                        num = num * 10 + (str[j] - '0');
                        ++j;
                    }
                    ++num;
                    Parent[num] = p;
                    //					printf("p %d num %d\n", p, num);
                }
            }
            /*
            ��Ϊ��N�����񣬲�����N�У�ͬһ�����񲻿��ܳ������Σ����Ҳ����������񲻳��֣���ÿ�еĸ�������
            �ض���ͬ��
            */
            // ������ӡ�
            q.push(p);
        }

        //		Print(N);

        // ���������Ѿ���ӣ����Ӽ��ɡ�
        while (!q.empty()) {
            int x = q.top();
            q.pop();
            printf("Task%d%s", x - 1, q.empty() ? "\n" : " ");
        }
    }

    return 0;
}
