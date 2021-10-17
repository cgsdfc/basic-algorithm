#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */
typedef long long LL;
typedef struct Fraction {
    LL up, down;
} Fraction;

LL gcd(LL a, LL b) {
    return !b ? a : gcd(b, a % b);
}

Fraction Reduce(Fraction f) {
    if (f.down < 0) {
        f.up = -f.up;
        f.down = -f.down;
    }
    if (f.up == 0) {
        f.down = 1;
    } else {
        LL d = gcd(abs(f.up), f.down);
        f.up /= d;
        f.down /= d;
    }
    return f;
}

Fraction Add(Fraction f1, Fraction f2) {
    Fraction res;
    res.up = f1.up * f2.down + f2.up * f1.down;
    res.down = f1.down * f2.down;
    return Reduce(res);
}

void Print(Fraction f) {
    if (f.down == 1) {
        printf("%lld\n", f.up);
    } else if (abs(f.up) > f.down) {
        printf("%lld %lld/%lld\n", f.up / f.down, abs(f.up) % f.down, f.down);
    } else {
        printf("%lld/%lld\n", f.up, f.down);
    }
}

int main(int argc, char* argv[]) {
    int N;
    Fraction ans = {0, 1};

    //	freopen("./in.txt","r",stdin);

    scanf("%d", &N);
    while (N--) {
        Fraction f;
        scanf("%lld/%lld", &f.up, &f.down);
        f = Reduce(f);
        //		Print(f);
        ans = Add(ans, f);
    }

    Print(ans);
    return 0;
}
