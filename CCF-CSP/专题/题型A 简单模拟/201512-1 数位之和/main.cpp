#include <cctype>
#include <cstdio>
/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

int main(int argc, char** argv) {
    int ch;
    int ans = 0;

    while ((ch = getchar()) != EOF) {
        if (isdigit(ch)) { ans += ch - '0'; }
    }
    printf("%d\n", ans);

    return 0;
}
