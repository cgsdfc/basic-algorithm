#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */
/*
���밴���ֵ������У���Ϊ����ʤ������ͬʱ������ֵ�����С�ġ�

B=�� =0
C=ʯͷ=1
J=����=2
*/

enum {
    TIE = 0,
    WIN1 = 1,
    WIN2 = 2,
};

int Win(int a, int b) {
    if (a == b) return TIE;
    if ((a + 1) % 3 == b) return WIN1;
    return WIN2;
}

int To(char c) {
    switch (c) {
        case 'B': return 0;
        case 'C': return 1;
        case 'J': return 2;
    }
}

char From(int i) {
    assert(0 <= i && i <= 2);
    char chars[] = "BCJ";
    return chars[i];
}

char Max(int a[]) {
    const int n = 3;
    int val = -1;
    int pos = 0;
    int i;
    for (i = 0; i < n; ++i) {
        if (a[i] > val) {
            val = a[i];
            pos = i;
        }
    }
    return From(pos);
}

int main(int argc, char* argv[]) {
    int n;
    int T;
    //	ͳ��ƽ�֣���Ӯ����Ӯ�Ĵ�����
    int wins[3] = {};
    //	ͳ�Ƽ���ÿ�ֳ���Ӯ�Ĵ�����
    int cnt1[3] = {};
    int cnt2[3] = {};

    scanf("%d", &n);
    T = n;
    while (T--) {
        char a[2], b[2];
        int res;
        int an, bn;

        scanf("%s%s", a, b);
        an = To(a[0]);
        bn = To(b[0]);
        res = Win(an, bn);
        wins[res]++;

        if (res == WIN1) {
            cnt1[an]++;
        } else if (res == WIN2) {
            cnt2[bn]++;
        }
    }

    // ��ʤ������䣬��ʤ�������䡣
    printf("%d %d %d\n", wins[WIN1], wins[TIE], wins[WIN2]);
    printf("%d %d %d\n", wins[WIN2], wins[TIE], wins[WIN1]);
    printf("%c %c\n", Max(cnt1), Max(cnt2));

    return 0;
}
