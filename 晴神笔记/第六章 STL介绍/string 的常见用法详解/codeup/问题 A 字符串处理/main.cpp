#include <algorithm>
#include <cassert>
#include <cctype>
#include <iostream>
#include <string>
using namespace std;

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

/*
����������������
Ȼ��ת��Ϊβ����ָ������ʽ��Ȼ��ָ�����루��Сָ�����룬��Ϊ����ʹ��β������
���Ȳ���ʧ��
Ȼ��������׼��ʾ�µ�β����ָ���Ƕ��٣����Ϊ��׼��ʽ��
*/

struct Float {
    typedef long long ll;  // ��Ч���֣���β��������10λ��
    // ָ��������̫�󣬷���Խ׺�������
    ll frac;  // �����˷��š�
    int exp;

    Float(ll _frac, int _exp) {
        frac = _frac;
        exp = _exp;
    }

    /*
    �����ַ������õ��������ı�ʾ��
    �㷨��
    ��iɨ�������ַ������õ���������ʽ�ĸ������֣���װ��Float����
    ע�⣺
    1. ��������ǰ���п�ѡ�ĸ��ţ�Ҫ���ǡ�
    2. eָ�������п�ѡ�ĸ��ţ�Ҫ���ǡ�
    3. �ܶಿ�ֶ��ǿ�ѡ�ġ�

    ��ʾ��ʽ��
    value = frac * pow(10, exp)
    ���ַ����޷������Ƿ��׼�ͣ�
    ���������ʱ�򣬿��Ը���frac����Чλ����exp�Ĵ�С��ת��Ϊ��׼��ʽ�����
    */

    Float(string str) {
        int sign = 1;
        int i = 0;

        if (str[0] == '-') {
            ++i;
            sign = -1;
        }

        // ��Ϊ�ӷ�֮��϶����Ǳ�׼��ʽ�ˣ�����һ��ʼ�Ͳ���Ҫ��׼����
        // ��β��ȥ��ǰ�����С����󱣴棬��ָ������ -С��λ��+E��������֡�
        while (i < str.size() && str[i] == '0') {
            ++i;
        }
        if (str.size() == i) {
            // �����㡣
            frac = exp = 0;
            return;
        }
        // ����β����С��
        frac = 0;
        for (; i < str.size() && isdigit(str[i]); ++i) {
            frac = frac * 10 + (str[i] - '0');
        }
        if (i == str.size()) {
            // û�е�Ҳû��e��˵������������
            exp = 0;
            frac *= sign;
            return;
        }
        // ����е㣬���������β����������ָ����
        // ��Ϊ����eǰ�棬�������е㡣
        exp = 0;
        if (str[i] == '.') {
            ++i;
            // �����ǵı�ʾ��ʽ�£�exp=-С�����ֳ���+e����
            while (i < str.size() && isdigit(str[i])) {
                frac = frac * 10 + (str[i] - '0');
                --exp;
                ++i;
            }
        }
        // β��������ϡ�
        frac *= sign;

        // ָ�����֣������e���������Ȼ���ۼӵ�exp�ϡ�
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
        // ����Ӧ��û���ַ��ˡ�
        assert(i == str.size());
    }

    // ���뵽Сָ����
    void Align(int e) {
        while (exp > e) {
            --exp;
            frac *= 10;
        }
    }

    // ��׼��ʽ�����
    // �������������ֱ�����������
    // �����С�������ѧ�������������[-]F.FFFe[-]EEEE ��
    // �������ҽ���һλ��
    void Print() {
        // ���������0��ֱ�������
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

        // ��ȥ�������0.
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
        ��Ϊ���������
        1. ��������û��e��
        2. С��������e��
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
    // �Խף����뵽��С�ס�
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
