#include <cstdio>
#include <iostream>
#include <map>
#include <string>
using namespace std;
/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

const char Low[13][5] = {"tret", "jan", "feb", "mar", "apr", "may", "jun",
                         "jly",  "aug", "sep", "oct", "nov", "dec"};
const char Hi[13][5] = {{},    "tam", "hel", "maa", "huh", "tou", "kes",
                        "hei", "elo", "syy", "lok", "mer", "jou"};

map<string, int> M2E;
map<int, string> E2M;

/*
总答案数是有限的并且很小，所以先预计算，后查询比较快。
注意：
当x是13的整数倍时，个位不输出，只输出十位符号，比如13是tam，26是hel。
而不是tam tret。
本题map用在实现两种数字的映射。
*/
void Init2() {
    for (int i = 0; i < 169; ++i) {
        int x = i;
        int lo = x % 13;
        int hi = x / 13;
        string y;
        if (!hi) {
            y = Low[lo];
        } else if (!lo) {
            y = Hi[hi];
        } else {
            y += Hi[hi];
            y += " ";
            y += Low[lo];
        }
        M2E[y] = x;
        E2M[x] = y;
    }
    //	for (map<int, string>::iterator it=E2M.begin();it!=E2M.end();++it) {
    //		printf("%d %s\n", it->first, it->second.c_str());
    //	}
}

int main(int argc, char** argv) {
    Init2();
    int N;
    scanf("%d", &N);
    getchar();
    while (N--) {
        string str;
        getline(cin, str);
        int x;
        if (sscanf(str.c_str(), "%d", &x) == 1) {
            // 成功读取了int。
            printf("%s\n", E2M[x].c_str());
        } else {
            printf("%d\n", M2E[str]);
        }
    }
    return 0;
}
