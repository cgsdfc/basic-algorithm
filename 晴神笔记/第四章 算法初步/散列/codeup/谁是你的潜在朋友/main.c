#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

// ������/������200
#define MAXN 210

// ��i������ϲ���ı��顣
int reader[MAXN];

// ÿ�����ж��ٹ�ͬ���ߡ�
// ����ͬ��������1ʱ����ʾû�����ѣ�������N-1�����ѡ�
int book[MAXN];

int main(int argc, char* argv[]) {
    int N, M;

    while (scanf("%d%d", &N, &M) != EOF) {
        int i;
        memset(book, 0, sizeof(book));
        memset(reader, 0, sizeof(book));

        for (i = 1; i <= N; ++i) {
            int b;
            // ����iϲ����b��
            scanf("%d", &b);
            reader[i] = b;
            // ע�⣡������Ҫ�ѱ������㡣
            book[b]++;
        }
        for (i = 1; i <= N; ++i) {
            int b = reader[i];
            int bs = book[b];
            if (bs > 1) {
                printf("%d\n", bs - 1);
            } else if (bs == 1) {
                puts("BeiJu");
            }
        }
    }
    return 0;
}
