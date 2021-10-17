#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */
/*
必须按照字典序排列，因为当获胜次数相同时，输出字典序最小的。

B=布 =0
C=石头=1
J=剪刀=2
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
    //	统计平手，甲赢，乙赢的次数。
    int wins[3] = {};
    //	统计甲乙每种出法赢的次数。
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

    // 乙胜利则甲输，甲胜利则乙输。
    printf("%d %d %d\n", wins[WIN1], wins[TIE], wins[WIN2]);
    printf("%d %d %d\n", wins[WIN2], wins[TIE], wins[WIN1]);
    printf("%c %c\n", Max(cnt1), Max(cnt2));

    return 0;
}
