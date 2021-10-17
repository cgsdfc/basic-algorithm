#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

// 输入的整数的位数。
#define MAXS 1005

// 转换为2进制后的最大位数。
#define MAXN 5000

typedef struct Big {
    int d[MAXN];
    int len;
} Big;

char str[MAXS];
Big A;

Big From(char str[], int len) {
    int i;
    Big c = {};
    c.len = len;
    for (i = 0; i < len; ++i) {
        c.d[i] = str[len - 1 - i] - '0';
    }
    return c;
}

Big Div(Big a, int b, int* rem) {
    Big c = {};
    int i;
    int r = 0;
    c.len = a.len;
    for (i = a.len - 1; i >= 0; --i) {
        r = r * 10 + a.d[i];
        if (r < b) {
            c.d[i] = 0;
        } else {
            c.d[i] = r / b;
            r %= b;
        }
    }
    while (c.len - 1 >= 1 && c.d[c.len - 1] == 0) {
        c.len--;
    }
    *rem = r;
    return c;
}

Big ToBin(Big a) {
    Big c = {};
    while (!(a.len == 1 && a.d[0] == 0)) {
        int r;
        a = Div(a, 2, &r);
        c.d[c.len++] = r;
    }
    return c;
}

Big Add(Big a, Big b) {
    Big c = {};
    int carry = 0;
    int i;
    for (i = 0; i < a.len || i < b.len; ++i) {
        int temp = a.d[i] + b.d[i] + carry;
        c.d[c.len++] = temp % 10;
        carry = temp / 10;
    }
    if (carry) { c.d[c.len++] = carry; }
    return c;
}

Big Mult(Big a, int b) {
    Big c = {};
    int carry = 0;
    int i;
    for (i = 0; i < a.len; ++i) {
        int temp = a.d[i] * b + carry;
        c.d[c.len++] = temp % 10;
        carry = temp / 10;
    }
    while (carry) {
        c.d[c.len++] = carry % 10;
        carry /= 10;
    }
    return c;
}

// 把二进制的a倒序转换为十进制。
Big ToDec(Big a) {
    Big c = {};
    Big p = {};
    int i;

    // c=0;
    c.len = 1;
    c.d[0] = 0;
    // p=1;
    p.len = 1;
    p.d[0] = 1;

    /*
    位权从小到大生成，因此实现了高位和低位的逆转。
    */
    for (i = a.len - 1; i >= 0; --i) {
        if (a.d[i]) {
            // c+=p;
            c = Add(c, p);
        }
        // p*=2;
        p = Mult(p, 2);
    }
    return c;
}

void Print(Big a) {
    int i;
    for (i = a.len - 1; i >= 0; --i) {
        printf("%d", a.d[i]);
    }
    printf("\n");
}

int main(int argc, char* argv[]) {
    while (scanf("%s", str) != EOF) {
        A = From(str, strlen(str));
        //		Print(A);

        A = ToBin(A);
        //		Print(A);

        A = ToDec(A);
        Print(A);
    }
    return 0;
}
