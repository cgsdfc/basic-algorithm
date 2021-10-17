#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstring>
using namespace std;

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

/*
ͳ�ƶ����ı��г��ֵĵ��ʣ��������ظ������
ע�ⲻ��Ҫͳ�ƴ�Ƶ��ֻ��Ҫȥ��Ȼ������

�㷨���Ӷȣ�O(M+NlogN)��M�����ַ�����N���ܵ�������
*/

const int MAXL = 100000 + 5;  // һ�С�
const int MAXN = 1000 + 5;    // ����������
const int MAXS = 100 + 5;     // ���ʳ��ȡ�

char line[MAXL];

// ȫ������ĵ��ʡ�
char words[MAXN][MAXS];
// ���ʷ���id��
int index;

// ÿ�����ʵ�id������ʱֻ��id����
int id[MAXN];

bool cmp(int a, int b) {
    return strcmp(words[a], words[b]) < 0;
}

// ����һ�����ʡ�
void Add(char str[]) {
    strcpy(words[index], str);
    id[index] = index;
    ++index;
}

void ParseLine(char str[], int len) {
    // һ�����ʵ�buf��
    char buf[MAXS];
    int blen = 0;

    int i = 0;
    while (i < len) {
        // ������Сд��ĸ��ɡ�
        while (i < len && !islower(str[i])) {
            ++i;
        }
        if (i >= len) { break; }  // �����ﱣ֤��buf�ǿա�
        blen = 0;
        while (i < len && islower(str[i])) {
            buf[blen++] = str[i++];
        }
        buf[blen] = 0;
        Add(buf);
    }
}

int main(int argc, char** argv) {
    // ������ֱ��EOF��
    while (gets(line)) {
        ParseLine(line, strlen(line));
    }
    sort(id, id + index, cmp);
    // ȥ�������
    int i = 0;
    while (i < index) {
        int v = id[i];
        puts(words[v]);
        int j = i;
        // ������ͬ�ĵ��ʡ�
        while (j < index && !strcmp(words[v], words[id[j]])) {
            ++j;
        }
        i = j;
    }

    return 0;
}
