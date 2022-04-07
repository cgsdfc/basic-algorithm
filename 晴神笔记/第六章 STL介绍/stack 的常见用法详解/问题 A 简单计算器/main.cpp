#include <cassert>
#include <iostream>
#include <stack>
#include <string>
using namespace std;

// 直接计算中缀表达式的模板。

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */
const string AllOps = "+-*/";

bool IsOp(char x) {
    return AllOps.find(x) != string::npos;
}

int Prio(char op) {
    // 运算符优先级。
    switch (op) {
        case '-':
        case '+': return 1;
        case '*':
        case '/': return 2;
        default: return 999;
    }
}

void Compute(stack<double>& data, char op) {
    assert(data.size() >= 2);
    // a、b的出栈顺序。
    double a, b;
    b = data.top();
    data.pop();
    a = data.top();
    data.pop();
    switch (op) {
        case '-': a -= b; break;
        case '+': a += b; break;
        case '*': a *= b; break;
        case '/':
            assert(b); // 这个必须有的，否则不知道哪里错了。
            a /= b;
            break;
    }
    data.push(a);
}

int main(int argc, char** argv) {
    string str;
    while (getline(cin, str) && str != "0") {
        // 需要两个栈，一个装操作符，一个装操作数。
        stack<char> op;
        stack<double> data;
        int i = 0;
        // 解析字符串。
        while (i < str.size()) {
            // 跳过空格。
            while (i < str.size() && str[i] == ' ') {
                ++i;
            }
            if (i == str.size()) break;

            char x = str[i];
            if (IsOp(x)) {
                ++i;
                /*
                关键步骤：
                记住只有当新运算符x的优先级小于等于栈顶优先级才出栈。
                */
                // 栈空，或者新运算符优先级大于栈顶。
                // 当前的操作符优先级较高，要入栈。
                if (op.empty() || Prio(x) > Prio(op.top())) {
                    op.push(x);
                } else {
                    // 上下两个条件正好是取反的关系。
                    // 当前操作符优先级较低，栈内的操作符可以弹出并计算。
                    while (!op.empty() && Prio(x) <= Prio(op.top())) {
                        char top = op.top();
                        op.pop();
                        Compute(data, top);
                    }
                    // 当前操作符必须等遇到比它优先级低的才能运算，现在只能入栈。
                    op.push(x);
                }
            } else if (isdigit(x)) {
                // 只有遇到操作符才计算，遇到操作数就无脑入栈。
                int num = 0;
                // 先将解析此操作数。
                while (i < str.size() && isdigit(str[i])) {
                    num = num * 10 + (str[i] - '0');
                    ++i;
                }
                data.push(num);
            } else {
                // 不应该有别的字符。
                assert(false);
            }
        }
        // 记住最后还有清空data栈。
        while (!op.empty()) {
            Compute(data, op.top());
            op.pop();
        }
        // 最后栈必定只有一个元素，就是运算的结果。
        // 如果是后缀表达式，算法更加简单，碰到操作符直接弹出两数计算即可。
        printf("%.2f\n", data.top());
    }

    return 0;
}
