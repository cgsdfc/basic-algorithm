#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

// 最多有多少10进制位
#define MAXN 100

/*
课本的Bign表示的是非负数，所有操作都是有假设的，
比如add假设两个数是非负的，即不包括减法；sub假设两个数是非负并且a大于等于b，
即结果是非负的。

这里我加了一个neg，表示是否为负数，在课本算法的基础上实现了考虑的负数的操作。
课本的算法用小写字母，考虑了负数的算法用大写字母。
*/
typedef struct Bign {
    int d[MAXN];  // 各十进制位，高位在高，低位在低，与日常书写顺序刚刚相反。
    int len;      // 有效位数。
    int neg;      // 是否负数。
} Bign;

// 初始化Bign，可以调Init，或者用 Bign a={};
// 因为大整数是结构体，最好在定义的时候就初始化。
#define BIGN_INIT \
    {}

/*
把字符串形式的数字，即书写顺序（高位在前，低位在后），
转为Bign（高位在后，低位在前）。
关键是逆序写入。

注意：这里假设了str是非负的，并且没有多余的前导零。并且位数不超过MAXN。
*/
Bign change(char str[]) {
    // 注意必须清零，因为add等都会访问超过len的元素。
    Bign a = {};
    int i;

    a.len = strlen(str);
    for (i = 0; i < a.len; ++i) {
        a.d[i] = str[a.len - i - 1] - '0';
    }
    return a;
}

/*
非负数相加。
*/
Bign add(Bign a, Bign b) {
    Bign c = {};
    int carry = 0;  // 进位
    int i;

    for (i = 0; i < a.len || i < b.len; ++i) {
        int temp = a.d[i] + b.d[i] + carry;
        carry = temp / 10;
        c.d[c.len++] = temp % 10;
    }
    if (carry != 0) { c.d[c.len++] = carry; }
    return c;
}

Bign Reduce(Bign c) {
    /*
    去掉前导零。注意至少保留一位的逻辑。
    */
    while (c.len - 1 >= 1 && c.d[c.len - 1] == 0) {
        c.len--;
    }
    return c;
}

/*
非负数相减，并且保证结果是非负数。
*/
Bign sub(Bign a, Bign b) {
    Bign c = {};
    int i;

    for (i = 0; i < a.len || i < b.len; ++i) {
        if (a.d[i] < b.d[i]) {
            // 需要借位
            a.d[i + 1]--;
            a.d[i] += 10;
        }
        c.d[c.len++] = a.d[i] - b.d[i];
    }
    return Reduce(c);
}

/*
比较两个非负的大整数。
1. 先比较长度。
2. 从高到低比较各位，按照字典序。
*/
int compare(Bign a, Bign b) {
    if (a.len > b.len)
        return 1;  // a大
    else if (a.len < b.len)
        return -1;  // a小
    else {
        int i;
        for (i = a.len - 1; i >= 0; i--) {
            if (a.d[i] > b.d[i])
                return 1;  // 只要有一位a大，则a大。
            else if (a.d[i] < b.d[i])
                return -1;  // 只要有一位a小，则a小。
            // 分不出大小，继续看下一位。
        }
        return 0;
    }
}

int IsZero(Bign c) {
    return c.len == 1 && c.d[0] == 0;
}

/*
高精度和低精度的乘法。
两数都是非负数。
*/
Bign mult(Bign a, int b) {
    Bign c = {};
    int carry = 0;
    int i;

    for (i = 0; i < a.len; ++i) {
        int temp = b * a.d[i] + carry;
        c.d[c.len++] = temp % 10;
        carry = temp / 10;
    }
    while (carry) {
        c.d[c.len++] = carry % 10;
        carry /= 10;
    }
    /*
    乘法的结果可能是0，所以要去掉前导零。
    */
    return Reduce(c);
}

/*
高精度和低精度的除法。
两数都是非负数。特别的，除数不能为0.
商是高精度，余数是低精度。
*/
Bign divide(Bign a, int b, int* rem) {
    Bign c = {};  // 商。
    int r = 0;    // 余数。
    int i;

    c.len = a.len;  // 被除数的每一位是和商的每一位一一对应的。
    // 与其他三种运算不同，除法是从高位到低位。
    for (i = a.len - 1; i >= 0; i--) {
        r = r * 10 + a.d[i];  // 和上一位遗留的余数组合，成为临时被除数。
        if (r < b) {
            // 不够除，商0.
            c.d[i] = 0;
        } else {
            c.d[i] = r / b;  // 商
            r = r % b;       // 获得新的余数。
        }
    }
    *rem = r;
    return Reduce(c);
}

/*
打印一个高精度，假设为非负数。
*/
void print(Bign a) {
    // 从高到低打印。
    int i;
    for (i = a.len - 1; i >= 0; i--) {
        printf("%d", a.d[i]);
    }
}

/*
输入一个高精度。
假设条件和change一样。
*/
Bign read(void) {
    char buf[MAXN + 1];

    scanf("%s", buf);
    return change(buf);
}

/*
能处理负数的高精度运算。
*/

Bign Sub(Bign a, Bign b) {
    if (a.neg != b.neg) { // 异号相减
        Bign c = add(a, b);
        c.neg = a.neg;
        return c;
    } else {
        int cmp = compare(a, b);
        Bign c = cmp >= 0 ? sub(a, b) : sub(b, a);
        if (cmp < 0) {
            // 两数相减，被减数大于减数则为正，等于则为0，小于则为负。
            c.neg = 1;
        }
        return c;
    }
}

Bign Add(Bign a, Bign b) {
    if (a.neg == b.neg) {
        // 同号相加。
        Bign c = add(a, b);
        c.neg = a.neg;
        return c;
    } else {
        // 异号相减。
        int cmp = compare(a, b);
        Bign c = cmp >= 0 ? sub(a, b) : sub(b, a);
        if (cmp != 0) {
            // 如果两个绝对值不同，符号不同的数相加，
            // 则和的符号是绝对值大的数的符号。
            c.neg = cmp > 0 ? a.neg : b.neg;
        }
        return c;
    }
}

Bign Mult(Bign a, int b) {
    Bign c = mult(a, abs(b));
    if (IsZero(c)) return c;
    // c非零，则a，b都非零
    if ((a.neg && b > 0) || (!a.neg && b < 0)) { c.neg = 1; }
    return c;
}

// 考虑到负数除法的取余比较复杂，暂时不实现。

int main(int argc, char* argv[]) {
    Bign a = {};
    Bign c = {};
    int b;
    int r;

    a = read();
    scanf("%d", &b);
    c = mult(a, b);
    //	printf("r %d\n", r);
    print(c);
    return 0;
}
