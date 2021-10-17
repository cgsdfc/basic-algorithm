#include <algorithm>
#include <cstdio>
using namespace std;

// 三种红绿灯的持续时间。
int r, y, g;
int N;  // N段路。
/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */
typedef long long ll;

// 一个 红绿灯的状态，当前什么颜色，还剩多少秒。
struct Light {
    int color;
    ll time;
};

// 计算出发时状态的li，经过t后是什么状态。
Light Now(Light li, ll t) {
    while (t > 0) {
        ll dur = min(t, li.time);
        t -= dur;
        li.time -= dur;
        if (!li.time) {
            switch (li.color) {
                case 1:  // Red
                    li.color = 3;
                    li.time = g;
                    break;
                case 2:  // Yellow
                    li.color = 1;
                    li.time = r;
                    break;
                case 3:  // Green
                    li.color = 2;
                    li.time = y;
                    break;
            }
        }
    }
    return li;
}

int main(int argc, char** argv) {
    scanf("%d%d%d", &r, &y, &g);
    scanf("%d", &N);
    ll ans = 0;
    while (N--) {
        int k;
        ll t;
        scanf("%d%lld", &k, &t);
        if (!k) {
            // 一段路。
            ans += t;
            continue;
        }
        // 出发时的状态。
        Light li = {k, t};
        Light now = Now(li, ans);
        //		printf("li %d %d now %d %d\n", li.color, li.time, now.color,
        // now.time);

        if (now.color == 1) {
            // 红灯要等。
            ans += now.time;
        }
    }
    printf("%lld\n", ans);

    return 0;
}
