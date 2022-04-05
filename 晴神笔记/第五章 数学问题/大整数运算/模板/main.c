#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

// ����ж���10����λ
#define MAXN 100

/*
�α���Bign��ʾ���ǷǸ��������в��������м���ģ�
����add�����������ǷǸ��ģ���������������sub�����������ǷǸ�����a���ڵ���b��
������ǷǸ��ġ�

�����Ҽ���һ��neg����ʾ�Ƿ�Ϊ�������ڿα��㷨�Ļ�����ʵ���˿��ǵĸ����Ĳ�����
�α����㷨��Сд��ĸ�������˸������㷨�ô�д��ĸ��
*/
typedef struct Bign {
    int d[MAXN];  // ��ʮ����λ����λ�ڸߣ���λ�ڵͣ����ճ���д˳��ո��෴��
    int len;      // ��Чλ����
    int neg;      // �Ƿ�����
} Bign;

// ��ʼ��Bign�����Ե�Init�������� Bign a={};
// ��Ϊ�������ǽṹ�壬����ڶ����ʱ��ͳ�ʼ����
#define BIGN_INIT \
    {}

/*
���ַ�����ʽ�����֣�����д˳�򣨸�λ��ǰ����λ�ں󣩣�
תΪBign����λ�ں󣬵�λ��ǰ����
�ؼ�������д�롣

ע�⣺���������str�ǷǸ��ģ�����û�ж����ǰ���㡣����λ��������MAXN��
*/
Bign change(char str[]) {
    // ע��������㣬��Ϊadd�ȶ�����ʳ���len��Ԫ�ء�
    Bign a = {};
    int i;

    a.len = strlen(str);
    for (i = 0; i < a.len; ++i) {
        a.d[i] = str[a.len - i - 1] - '0';
    }
    return a;
}

/*
�Ǹ�����ӡ�
*/
Bign add(Bign a, Bign b) {
    Bign c = {};
    int carry = 0;  // ��λ
    int i;

    for (i = 0; i < a.len || i < b.len; ++i) {
        int temp = a.d[i] + b.d[i] + carry;
        carry = temp / 10;
        c.d[c.len++] = temp % 10;
    }
    if (carry != 0) { c.d[c.len++] = carry; }
    return c;
}

Bign Reduce(Bign c) {
    /*
    ȥ��ǰ���㡣ע�����ٱ���һλ���߼���
    */
    while (c.len - 1 >= 1 && c.d[c.len - 1] == 0) {
        c.len--;
    }
    return c;
}

/*
�Ǹ�����������ұ�֤����ǷǸ�����
*/
Bign sub(Bign a, Bign b) {
    Bign c = {};
    int i;

    for (i = 0; i < a.len || i < b.len; ++i) {
        if (a.d[i] < b.d[i]) {
            // ��Ҫ��λ
            a.d[i + 1]--;
            a.d[i] += 10;
        }
        c.d[c.len++] = a.d[i] - b.d[i];
    }
    return Reduce(c);
}

/*
�Ƚ������Ǹ��Ĵ�������
1. �ȱȽϳ��ȡ�
2. �Ӹߵ��ͱȽϸ�λ�������ֵ���
*/
int compare(Bign a, Bign b) {
    if (a.len > b.len)
        return 1;  // a��
    else if (a.len < b.len)
        return -1;  // aС
    else {
        int i;
        for (i = a.len - 1; i >= 0; i--) {
            if (a.d[i] > b.d[i])
                return 1;  // ֻҪ��һλa����a��
            else if (a.d[i] < b.d[i])
                return -1;  // ֻҪ��һλaС����aС��
            // �ֲ�����С����������һλ��
        }
        return 0;
    }
}

int IsZero(Bign c) {
    return c.len == 1 && c.d[0] == 0;
}

/*
�߾��Ⱥ͵;��ȵĳ˷���
�������ǷǸ�����
*/
Bign mult(Bign a, int b) {
    Bign c = {};
    int carry = 0;
    int i;

    for (i = 0; i < a.len; ++i) {
        int temp = b * a.d[i] + carry;
        c.d[c.len++] = temp % 10;
        carry = temp / 10;
    }
    while (carry) {
        c.d[c.len++] = carry % 10;
        carry /= 10;
    }
    /*
    �˷��Ľ��������0������Ҫȥ��ǰ���㡣
    */
    return Reduce(c);
}

/*
�߾��Ⱥ͵;��ȵĳ�����
�������ǷǸ������ر�ģ���������Ϊ0.
���Ǹ߾��ȣ������ǵ;��ȡ�
*/
Bign divide(Bign a, int b, int* rem) {
    Bign c = {};  // �̡�
    int r = 0;    // ������
    int i;

    c.len = a.len;  // ��������ÿһλ�Ǻ��̵�ÿһλһһ��Ӧ�ġ�
    // �������������㲻ͬ�������ǴӸ�λ����λ��
    for (i = a.len - 1; i >= 0; i--) {
        r = r * 10 + a.d[i];  // ����һλ������������ϣ���Ϊ��ʱ��������
        if (r < b) {
            // ����������0.
            c.d[i] = 0;
        } else {
            c.d[i] = r / b;  // ��
            r = r % b;       // ����µ�������
        }
    }
    *rem = r;
    return Reduce(c);
}

/*
��ӡһ���߾��ȣ�����Ϊ�Ǹ�����
*/
void print(Bign a) {
    // �Ӹߵ��ʹ�ӡ��
    int i;
    for (i = a.len - 1; i >= 0; i--) {
        printf("%d", a.d[i]);
    }
}

/*
����һ���߾��ȡ�
����������changeһ����
*/
Bign read(void) {
    char buf[MAXN + 1];

    scanf("%s", buf);
    return change(buf);
}

/*
�ܴ������ĸ߾������㡣
*/

Bign Sub(Bign a, Bign b) {
    if (a.neg != b.neg) { // ������
        Bign c = add(a, b);
        c.neg = a.neg;
        return c;
    } else {
        int cmp = compare(a, b);
        Bign c = cmp >= 0 ? sub(a, b) : sub(b, a);
        if (cmp < 0) {
            // ������������������ڼ�����Ϊ����������Ϊ0��С����Ϊ����
            c.neg = 1;
        }
        return c;
    }
}

Bign Add(Bign a, Bign b) {
    if (a.neg == b.neg) {
        // ͬ����ӡ�
        Bign c = add(a, b);
        c.neg = a.neg;
        return c;
    } else {
        // ��������
        int cmp = compare(a, b);
        Bign c = cmp >= 0 ? sub(a, b) : sub(b, a);
        if (cmp != 0) {
            // �����������ֵ��ͬ�����Ų�ͬ������ӣ�
            // ��͵ķ����Ǿ���ֵ������ķ��š�
            c.neg = cmp > 0 ? a.neg : b.neg;
        }
        return c;
    }
}

Bign Mult(Bign a, int b) {
    Bign c = mult(a, abs(b));
    if (IsZero(c)) return c;
    // c���㣬��a��b������
    if ((a.neg && b > 0) || (!a.neg && b < 0)) { c.neg = 1; }
    return c;
}

// ���ǵ�����������ȡ��Ƚϸ��ӣ���ʱ��ʵ�֡�

int main(int argc, char* argv[]) {
    Bign a = {};
    Bign c = {};
    int b;
    int r;

    a = read();
    scanf("%d", &b);
    c = mult(a, b);
    //	printf("r %d\n", r);
    print(c);
    return 0;
}
