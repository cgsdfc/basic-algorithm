#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

#define MAXN 25

typedef struct Big {
    int d[MAXN];
    int len;
} Big;

Big Mult(Big a, int b) {
    int i;
    Big c = {};
    int carry = 0;
    for (i = 0; i < a.len; ++i) {
        int temp = b * a.d[i] + carry;
        c.d[c.len++] = temp % 10;
        carry = temp / 10;
    }
    while (carry) {
        c.d[c.len++] = carry % 10;
        carry /= 10;
    }
    // 题目保证a为正整数，而b=2.
    return c;
}

Big From(char str[], int len) {
    int i;
    Big c;
    c.len = len;
    for (i = 0; i < len; ++i) {
        c.d[i] = str[len - 1 - i] - '0';
    }
    return c;
}

/*
所谓a，b的数字只是排列不同，就是每一个不同的数字，a，b都有相同的数量。
*/
int Judge(Big a, Big b) {
    int an[10] = {}, bn[10] = {};
    int i;
    if (a.len != b.len) return 0;
    for (i = 0; i < a.len; ++i) {
        an[a.d[i]]++;
        bn[b.d[i]]++;
    }
    return memcmp(an, bn, sizeof(an)) == 0;
}

void Print(Big c) {
    int i;
    for (i = c.len - 1; i >= 0; --i) {
        printf("%d", c.d[i]);
    }
    printf("\n");
}

int main(int argc, char* argv[]) {
    char str[MAXN];
    Big a = {}, b = {};
    int ans;

    scanf("%s", str);
    a = From(str, strlen(str));
    b = Mult(a, 2);
    ans = Judge(a, b);
    puts(ans ? "Yes" : "No");
    Print(b);

    return 0;
}
