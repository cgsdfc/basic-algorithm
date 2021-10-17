#include <iostream>
#include <map>
using namespace std;

map<int, int> count;

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

/*
不用map的解法：
令不相同的数互相抵消，则最后剩下的肯定是占半数以上的数。
*/

void main2() {
    int M, N;
    int count = 0;
    int ans;

    scanf("%d%d", &M, &N);
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            int x;
            scanf("%d", &x);
            if (count == 0) {
                count = 1;
                ans = x;
            } else {
                if (ans == x) {
                    ++count;
                } else {
                    --count;
                }
            }
        }
    }
    printf("%d\n", ans);
}

int main(int argc, char** argv) {
    main2();
    return 0;

    int M, N;
    scanf("%d%d", &M, &N);
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            int x;
            scanf("%d", &x);
            count[x]++;
        }
    }
    int total = M * N;
    for (map<int, int>::iterator it = count.begin(); it != count.end(); ++it) {
        int x = it->first;
        int cnt = it->second;
        if (2 * cnt > total) {
            printf("%d\n", x);
            break;
        }
    }
    return 0;
}
