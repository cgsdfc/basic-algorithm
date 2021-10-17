#include <iostream>

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

const int D[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

bool Leap(int y) {
    return (y % 400 == 0) || (y % 4 == 0 && y % 100 != 0);
}

int Days(int y, int m) {
    return D[m] + (m == 2 && Leap(y));
}

int main(int argc, char** argv) {
    int y, d;
    scanf("%d%d", &y, &d);
    int mm = 1, dd = 1;

    // 当d=1时，循环0次。
    while (--d) {
        ++dd;
        if (dd == Days(y, mm) + 1) {
            dd = 1;
            ++mm;
        }
    }
    printf("%d\n%d\n", mm, dd);

    return 0;
}
