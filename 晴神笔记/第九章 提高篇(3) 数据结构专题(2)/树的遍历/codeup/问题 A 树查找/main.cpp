#include <algorithm>
#include <cstdio>
using namespace std;

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

#define MAXN 1005
int N;
int data[MAXN];  // ��ȫ��������
int D;           // ��ѯ�Ĳ�Ρ�

int main(int argc, char** argv) {
    while (scanf("%d", &N) != EOF && N != 0) {
        for (int i = 1; i <= N; ++i) {
            scanf("%d", &data[i]);
        }
        scanf("%d", &D);
        // ��D��ĵ�һ���ڵ���2^d-1 ������һ�������ڣ���˲㲻���ڡ�
        int first = 1 << (D - 1);
        if (first > N) {
            printf("EMPTY\n");
        } else {
            /*
            ��D������ʱ��ǡ��first���ڵ㣬
            ���ǲ��ܳ���first��N���ܽڵ�����
            */
            int n = min(first, N - first + 1);
            for (int i = 0; i < n; ++i) {
                printf("%d%s", data[first + i], i == n - 1 ? "\n" : " ");
            }
        }
    }
    return 0;
}
