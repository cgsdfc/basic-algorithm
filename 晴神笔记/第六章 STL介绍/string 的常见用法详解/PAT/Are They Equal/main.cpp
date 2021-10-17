#include <cassert>
#include <iostream>
#include <string>
using namespace std;

struct Float {
    string frac;
    int exp;

    Float() {}
    bool operator==(Float b) {
        return frac == b.frac && exp == b.exp;
    }

    // 这个数字是0，有唯一表示。
    void Init0(int N) {
        exp = 0;
        while (N--) {
            frac.push_back('0');
        }
    }
    // 输出。
    friend ostream& operator<<(ostream& os, Float& f) {
        return os << "0." << f.frac << "*10^" << f.exp;
    }

    /*
    保存指数和尾数，即标准形式里面的两个部分，即可完全表示一个浮点数。
    尾数保留N位，在此基础上进行比较。

    先去掉前导零，然后分清几种情况：
    1. 有整数部分，则e=整数部分长度，可以没有点，可以没有小数。
    2.
    没有整数部分，整数部分可以直接没有，可以是全零，则e=-小数点后面的零（到第一个非零为止）。
    3. 每种情况里面都要特判0，即.0, 0 0.0 000 000.000 等等。
    0的表示形式唯一，特判然后直接赋值。
    */

    Float(string str, int N) {
        // 先去掉前导零。
        while (str.size() && str[0] == '0') {
            str.erase(str.begin());
        }
        if (str.empty()) {
            // 数字0.
            Init0(N);
            return;
        }
        if (str[0] == '.') {
            // 纯小数。
            str.erase(str.begin());
            exp = 0;
            // 删除点后到第一个非零数之间的0.
            // exp就是负的这些零的个数。
            while (str.size() && str[0] == '0') {
                str.erase(str.begin());
                exp--;
            }
            if (str.empty()) {
                // 去掉0后就没有了，说明就是0.
                Init0(N);
                return;
            }
            // str 就是尾数了，但是还没有截断N位。
        } else {
            // 存在整数部分。
            // 整数部分的长度，就是exp。
            exp = 0;
            int k = 0;
            while (k < str.size() && str[k] != '.') {
                ++k;
                ++exp;
            }
            if (k != str.size()) {
                // 说明有点。把点删掉。
                str.erase(str.begin() + k);
            }
            // 剩下的str就是frac了，就差截断N位。
        }
        for (int i = 0; i < N; ++i) {
            if (i < str.size()) {
                frac.push_back(str[i]);
            } else {
                frac.push_back('0');
            }
        }
    }
};

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

int main(int argc, char** argv) {
    int N;
    string s1, s2;

    cin >> N >> s1 >> s2;
    Float a = Float(s1, N);
    Float b = Float(s2, N);
    if (a == b) {
        cout << "YES " << a << "\n";
    } else {
        cout << "NO " << a << " " << b << "\n";
    }
    return 0;
}
