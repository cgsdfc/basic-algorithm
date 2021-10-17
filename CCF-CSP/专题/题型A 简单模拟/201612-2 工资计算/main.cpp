#include <cstdio>
/*
税前工资S，税后工资T，T=f(S)，则f是增函数。
小明的公司每个月给小明发工资，而小明拿到的工资为交完个人所得税之后的工资。
假设他一个月的税前工资（扣除五险一金后、未扣税前的工资）为S元，则他应交的个人所得税按如下公式计算：
　　1）
个人所得税起征点为3500元，若S不超过3500，则不交税，3500元以上的部分才计算个人所得税，令A=S-3500元；
　　2） A中不超过1500元的部分，税率3%；
　　3） A中超过1500元未超过4500元的部分，税率10%；
　　4） A中超过4500元未超过9000元的部分，税率20%；
　　5） A中超过9000元未超过35000元的部分，税率25%；
　　6） A中超过35000元未超过55000元的部分，税率30%；
　　7） A中超过55000元未超过80000元的部分，税率35%；
　　8） A中超过80000元的部分，税率45%；
　　例如，如果小明的税前工资为10000元，则A=10000-3500=6500元，
其中不超过1500元部分应缴税1500×3%=45元，
超过1500元不超过4500元部分应缴税(4500-1500)×10%=300元，
超过4500元部分应缴税(6500-4500)×20%=400元。总共缴税745元，税后所得为9255元。
*/

const int P[][2] = {{0, 3}, {1500, 10}, {4500, 20}, {9000, 25}, {35000, 30}, {55000, 35}, {80000, 45}};
const int lenP = sizeof(P) / sizeof(P[0]);

// 由税前工资，计算税后工资。
int f(int S) {
    if (S <= 3500) return S;
    int A = S - 3500;
    for (int i = 0; i < lenP; ++i) {
        int left = P[i][0];
        int right = A;
        if (i != lenP - 1 && P[i + 1][0] < A) { right = P[i + 1][0]; }
        if (left >= right) break;
        int rate = P[i][1];
        int cost = (right - left) * rate / 100;
        S -= cost;
    }
    return S;
}

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

#define MAXT 100000
#define MAXS 154400

void GetMaxS() {
    int S = 0;
    while (1) {
        int T = f(S);
        if (T > MAXT) break;
        printf("S %d T %d\n", S, T);
        S += 100;
    }
}

/*
一个关键的条件：
题目保证S是整百的数，所以枚举的数据必须是整百的。
*/
void Search(int left, int right, int T) {
    while (left <= right) {
        int mid = (left + right) / 2;
        int t = f(mid * 100);  // 整百。
                               //		printf("t %d mid %d\n", t, mid);

        if (t == T) {
            printf("%d\n", mid * 100);
            return;
        }
        if (T < t) {
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }
}

/*
由于数据T较小，才10万，顺序搜索不会超时，
不必二分查找。
*/

int main(int argc, char** argv) {
    int T;
    scanf("%d", &T);
    // 二分查找。
    Search(1, MAXS / 100, T);
    return 0;

    // 线性查找。
    int S = 100;
    while (f(S) != T) {
        S += 100;
    }
    printf("%d\n", S);
    return 0;
}
