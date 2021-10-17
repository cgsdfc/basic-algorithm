#include <algorithm>
#include <cassert>
#include <cctype>
#include <iostream>
#include <string>
using namespace std;

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

/*
输入两个浮点数，
然后转换为尾数，指数的形式，然后指数对齐（向小指数对齐，因为这样使得尾数扩大，
精度不丢失。
然后计算出标准表示下的尾数和指数是多少，输出为标准形式。
*/

struct Float {
    typedef long long ll;  // 有效数字，即尾数不超过10位。
    // 指数不可能太大，否则对阶后会溢出。
    ll frac;  // 包括了符号。
    int exp;

    Float(ll _frac, int _exp) {
        frac = _frac;
        exp = _exp;
    }

    /*
    解析字符串，得到浮点数的表示。
    算法：
    用i扫描整个字符串，得到浮点数格式的各个部分，组装成Float对象。
    注意：
    1. 整数部分前面有可选的负号，要考虑。
    2. e指数部分有可选的负号，要考虑。
    3. 很多部分都是可选的。

    表示方式：
    value = frac * pow(10, exp)
    这种方法无法区分是否标准型，
    但是输出的时候，可以根据frac的有效位数和exp的大小而转化为标准形式输出。
    */

    Float(string str) {
        int sign = 1;
        int i = 0;

        if (str[0] == '-') {
            ++i;
            sign = -1;
        }

        // 因为加法之后肯定不是标准形式了，所以一开始就不需要标准化。
        // 把尾数去掉前导零和小数点后保存，而指数就是 -小数位数+E后面的数字。
        while (i < str.size() && str[i] == '0') {
            ++i;
        }
        if (str.size() == i) {
            // 数字零。
            frac = exp = 0;
            return;
        }
        // 计算尾数大小。
        frac = 0;
        for (; i < str.size() && isdigit(str[i]); ++i) {
            frac = frac * 10 + (str[i] - '0');
        }
        if (i == str.size()) {
            // 没有点也没有e。说明这是整数。
            exp = 0;
            frac *= sign;
            return;
        }
        // 如果有点，则继续计算尾数，并计算指数。
        // 因为点在e前面，所以先判点。
        exp = 0;
        if (str[i] == '.') {
            ++i;
            // 在我们的表示方式下，exp=-小数部分长度+e数。
            while (i < str.size() && isdigit(str[i])) {
                frac = frac * 10 + (str[i] - '0');
                --exp;
                ++i;
            }
        }
        // 尾数计算完毕。
        frac *= sign;

        // 指数部分，计算出e后的整数，然后累加到exp上。
        if (i < str.size() && tolower(str[i]) == 'e') {
            ++i;
            int esign = 1;
            if (str[i] == '-') {
                esign = -1;
                ++i;
            }
            int e = 0;

            while (i < str.size() && isdigit(str[i])) {
                e = e * 10 + (str[i] - '0');
                ++i;
            }
            exp += esign * e;
        }
        // 现在应该没有字符了。
        assert(i == str.size());
    }

    // 对齐到小指数。
    void Align(int e) {
        while (exp > e) {
            --exp;
            frac *= 10;
        }
    }

    // 标准形式输出：
    // 如果是整数，则直接整数输出。
    // 如果是小数，则科学计数法输出，即[-]F.FFFe[-]EEEE 。
    // 整数有且仅有一位。
    void Print() {
        // 如果是整数0则直接输出。
        if (frac == 0) {
            printf("0\n");
            return;
        }

        ll N;
        if (frac < 0) {
            putchar('-');
            N = -frac;
        } else {
            N = frac;
        }

        // 先去掉后面的0.
        while (N % 10 == 0) {
            N /= 10;
            ++exp;
        }

        char buf[100];
        int len = 0;
        while (N) {
            buf[len++] = (N % 10) + '0';
            N /= 10;
        }
        /*
        分为两种情况：
        1. 整数，则没有e。
        2. 小数，则有e。
        */
        if (exp >= 0) {
            for (int i = len - 1; i >= 0; --i) {
                putchar(buf[i]);
            }
            for (int i = 0; i < exp; ++i) {
                putchar('0');
            }
        } else {
            if (len == 1) {
                putchar(buf[len - 1]);
            } else {
                printf("%c.", buf[len - 1]);
                for (int i = len - 2; i >= 0; --i) {
                    putchar(buf[i]);
                }
            }
            printf("e%d", exp + len - 1);
        }
        printf("\n");
    }

    void Print2() {
        printf("frac %lld exp %d\n", frac, exp);
    }
};

Float Add(Float a, Float b) {
    // 对阶，对齐到最小阶。
    int exp = min(a.exp, b.exp);

    a.Align(exp);
    b.Align(exp);
    //	a.Print2();
    //	b.Print2();

    Float res = Float(a.frac + b.frac, exp);
    return res;
}

int main(int argc, char** argv) {
    string s1, s2;

    while (cin >> s1 >> s2) {
        Float f1 = Float(s1);
        //		f1.Print2();

        Float f2 = Float(s2);
        //		f2.Print2();

        Float res = Add(f1, f2);
        res.Print();
    }

    return 0;
}
