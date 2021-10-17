#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

int main(int argc, char* argv[]) {
    int N;
    int ans = 0;
    int pos = 0;

    scanf("%d", &N);
    while (N--) {
        int x;
        scanf("%d", &x);
        if (x > pos) {
            // ���С�
            ans += 6 * (x - pos);
        } else if (x < pos) {
            // ����
            ans += 4 * (pos - x);
        }  // ԭ�ز�����
        pos = x;
        ans += 5;
    }
    printf("%d\n", ans);

    return 0;
}
