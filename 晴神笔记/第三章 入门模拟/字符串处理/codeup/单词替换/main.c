#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

/*
��Ŀ����
����һ���ַ������Իس��������ַ�������<=100�������ַ��������ɸ�������ɣ�����֮����һ���ո������
���е������ִ�Сд������Ҫ�����е�ĳ�������滻����һ�����ʣ�������滻֮����ַ�����

����
�������ݡ�ÿ�������������3�У�
��1���ǰ���������ʵ��ַ��� s��
��2���Ǵ��滻�ĵ���a��(����<=100)
��3����a�����滻�ĵ���b��(����<=100)
s, a, b ��ǰ�������涼û�пո�
���
ÿ�������������ֻ�� 1 �У�
��s�����е���a�滻��b֮����ַ�����
�������� Copy
I love Tian Qin
I
You
������� Copy
You love Tian Qin
*/

#define MAXN 110

char str[MAXN], a[MAXN], b[MAXN];

int main(int argc, char* argv[]) {
    while (gets(str) && gets(a) && gets(b)) {
        int i;
        int len = strlen(str);
        char buf[MAXN];
        int k = 0;

        for (i = 0; i < len; ++i) {
            char c = str[i];
            if (isalpha(c)) { buf[k++] = c; }

            if (c == ' ' || i == len - 1) {
                // ���ʽ����߽硣
                buf[k] = 0;
                k = 0;
                printf("%s", (0 == strcmp(buf, a)) ? b : buf);
                if (c == ' ') putchar(c);
            }
        }
        putchar('\n');
    }
    return 0;
}
