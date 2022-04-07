#include <iostream>
#include <stack>
using namespace std;

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

char Match(char x) {
    switch (x) {
        case '}': return '{';
        case ']': return '[';
        case ')': return '(';
        default: return 0;
    }
}

bool Judge(string& str) {
    stack<char> s;
    for (int i = 0; i < str.size(); ++i) {
        char x = str[i];
        switch (x) {
            case '{':
            case '[':
            case '(': s.push(x); break;
            case '}':
            case ']':
            case ')':
                if (!s.empty() && s.top() == Match(x)) {
                    s.pop();
                } else {
                    return false;
                }
                break;
        }
    }
    // 注意，合法的状态是最后栈为空。
    return s.empty();
}

/*
注意点：
1. 对栈进行top，pop之前必须判定empty。
2. 读取整数后若要getline，则必须先getchar。
*/
// 模板：检查括号序列是否合法。
int main(int argc, char** argv) {
    int N;
    while (scanf("%d", &N) != EOF) {
        getchar(); // scanf 会跳过换行，但不会主动清除换行，必须用getchar手动清除。
        while (N--) {
            string str;
            getline(cin, str);
            bool ans = Judge(str);
            printf("%s\n", ans ? "yes" : "no");
        }
    }
    return 0;
}
