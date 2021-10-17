#include <cstdio>
#include <map>
using namespace std;

// 可以散列，也可以直接map
int N;
map<int, int> mp;

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

int main(int argc, char** argv) {
    scanf("%d", &N);
    while (N--) {
        int x;
        scanf("%d", &x);
        mp[x]++;
    }
    int ans;
    int val = -1;
    for (map<int, int>::iterator it = mp.begin(); it != mp.end(); ++it) {
        if (it->second > val) {
            val = it->second;
            ans = it->first;
        }
    }
    printf("%d\n", ans);

    return 0;
}
