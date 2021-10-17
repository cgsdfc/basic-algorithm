#include <algorithm>
#include <cstdio>
using namespace std;

// ���ֺ��̵Ƶĳ���ʱ�䡣
int r, y, g;
int N;  // N��·��
/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */
typedef long long ll;

// һ�� ���̵Ƶ�״̬����ǰʲô��ɫ����ʣ�����롣
struct Light {
    int color;
    ll time;
};

// �������ʱ״̬��li������t����ʲô״̬��
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
            // һ��·��
            ans += t;
            continue;
        }
        // ����ʱ��״̬��
        Light li = {k, t};
        Light now = Now(li, ans);
        //		printf("li %d %d now %d %d\n", li.color, li.time, now.color,
        // now.time);

        if (now.color == 1) {
            // ���Ҫ�ȡ�
            ans += now.time;
        }
    }
    printf("%lld\n", ans);

    return 0;
}
