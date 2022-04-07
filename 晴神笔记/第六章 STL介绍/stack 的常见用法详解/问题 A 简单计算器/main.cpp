#include <cassert>
#include <iostream>
#include <stack>
#include <string>
using namespace std;

// ֱ�Ӽ�����׺���ʽ��ģ�塣

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */
const string AllOps = "+-*/";

bool IsOp(char x) {
    return AllOps.find(x) != string::npos;
}

int Prio(char op) {
    // ��������ȼ���
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
    // a��b�ĳ�ջ˳��
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
            assert(b); // ��������еģ�����֪��������ˡ�
            a /= b;
            break;
    }
    data.push(a);
}

int main(int argc, char** argv) {
    string str;
    while (getline(cin, str) && str != "0") {
        // ��Ҫ����ջ��һ��װ��������һ��װ��������
        stack<char> op;
        stack<double> data;
        int i = 0;
        // �����ַ�����
        while (i < str.size()) {
            // �����ո�
            while (i < str.size() && str[i] == ' ') {
                ++i;
            }
            if (i == str.size()) break;

            char x = str[i];
            if (IsOp(x)) {
                ++i;
                /*
                �ؼ����裺
                ��סֻ�е��������x�����ȼ�С�ڵ���ջ�����ȼ��ų�ջ��
                */
                // ջ�գ���������������ȼ�����ջ����
                // ��ǰ�Ĳ��������ȼ��ϸߣ�Ҫ��ջ��
                if (op.empty() || Prio(x) > Prio(op.top())) {
                    op.push(x);
                } else {
                    // ������������������ȡ���Ĺ�ϵ��
                    // ��ǰ���������ȼ��ϵͣ�ջ�ڵĲ��������Ե��������㡣
                    while (!op.empty() && Prio(x) <= Prio(op.top())) {
                        char top = op.top();
                        op.pop();
                        Compute(data, top);
                    }
                    // ��ǰ����������������������ȼ��͵Ĳ������㣬����ֻ����ջ��
                    op.push(x);
                }
            } else if (isdigit(x)) {
                // ֻ�������������ż��㣬������������������ջ��
                int num = 0;
                // �Ƚ������˲�������
                while (i < str.size() && isdigit(str[i])) {
                    num = num * 10 + (str[i] - '0');
                    ++i;
                }
                data.push(num);
            } else {
                // ��Ӧ���б���ַ���
                assert(false);
            }
        }
        // ��ס��������dataջ��
        while (!op.empty()) {
            Compute(data, op.top());
            op.pop();
        }
        // ���ջ�ض�ֻ��һ��Ԫ�أ���������Ľ����
        // ����Ǻ�׺���ʽ���㷨���Ӽ򵥣�����������ֱ�ӵ����������㼴�ɡ�
        printf("%.2f\n", data.top());
    }

    return 0;
}
