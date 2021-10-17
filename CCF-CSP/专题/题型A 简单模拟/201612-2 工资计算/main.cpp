#include <cstdio>
/*
˰ǰ����S��˰����T��T=f(S)����f����������
С���Ĺ�˾ÿ���¸�С�������ʣ���С���õ��Ĺ���Ϊ�����������˰֮��Ĺ��ʡ�
������һ���µ�˰ǰ���ʣ��۳�����һ���δ��˰ǰ�Ĺ��ʣ�ΪSԪ������Ӧ���ĸ�������˰�����¹�ʽ���㣺
����1��
��������˰������Ϊ3500Ԫ����S������3500���򲻽�˰��3500Ԫ���ϵĲ��ֲż����������˰����A=S-3500Ԫ��
����2�� A�в�����1500Ԫ�Ĳ��֣�˰��3%��
����3�� A�г���1500Ԫδ����4500Ԫ�Ĳ��֣�˰��10%��
����4�� A�г���4500Ԫδ����9000Ԫ�Ĳ��֣�˰��20%��
����5�� A�г���9000Ԫδ����35000Ԫ�Ĳ��֣�˰��25%��
����6�� A�г���35000Ԫδ����55000Ԫ�Ĳ��֣�˰��30%��
����7�� A�г���55000Ԫδ����80000Ԫ�Ĳ��֣�˰��35%��
����8�� A�г���80000Ԫ�Ĳ��֣�˰��45%��
�������磬���С����˰ǰ����Ϊ10000Ԫ����A=10000-3500=6500Ԫ��
���в�����1500Ԫ����Ӧ��˰1500��3%=45Ԫ��
����1500Ԫ������4500Ԫ����Ӧ��˰(4500-1500)��10%=300Ԫ��
����4500Ԫ����Ӧ��˰(6500-4500)��20%=400Ԫ���ܹ���˰745Ԫ��˰������Ϊ9255Ԫ��
*/

const int P[][2] = {{0, 3}, {1500, 10}, {4500, 20}, {9000, 25}, {35000, 30}, {55000, 35}, {80000, 45}};
const int lenP = sizeof(P) / sizeof(P[0]);

// ��˰ǰ���ʣ�����˰���ʡ�
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
һ���ؼ���������
��Ŀ��֤S�����ٵ���������ö�ٵ����ݱ��������ٵġ�
*/
void Search(int left, int right, int T) {
    while (left <= right) {
        int mid = (left + right) / 2;
        int t = f(mid * 100);  // ���١�
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
��������T��С����10��˳���������ᳬʱ��
���ض��ֲ��ҡ�
*/

int main(int argc, char** argv) {
    int T;
    scanf("%d", &T);
    // ���ֲ��ҡ�
    Search(1, MAXS / 100, T);
    return 0;

    // ���Բ��ҡ�
    int S = 100;
    while (f(S) != T) {
        S += 100;
    }
    printf("%d\n", S);
    return 0;
}
