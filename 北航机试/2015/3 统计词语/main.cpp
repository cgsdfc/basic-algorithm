#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstring>
using namespace std;

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

/*
统计多行文本中出现的单词，按序无重复输出。
注意不需要统计词频，只需要去重然后排序。

算法复杂度：O(M+NlogN)，M是总字符数，N是总单词数。
*/

const int MAXL = 100000 + 5;  // 一行。
const int MAXN = 1000 + 5;    // 单词总数。
const int MAXS = 100 + 5;     // 单词长度。

char line[MAXL];

// 全部输入的单词。
char words[MAXN][MAXS];
// 单词分配id。
int index;

// 每个单词的id，排序时只对id排序。
int id[MAXN];

bool cmp(int a, int b) {
    return strcmp(words[a], words[b]) < 0;
}

// 增加一个单词。
void Add(char str[]) {
    strcpy(words[index], str);
    id[index] = index;
    ++index;
}

void ParseLine(char str[], int len) {
    // 一个单词的buf。
    char buf[MAXS];
    int blen = 0;

    int i = 0;
    while (i < len) {
        // 单词是小写字母组成。
        while (i < len && !islower(str[i])) {
            ++i;
        }
        if (i >= len) { break; }  // 是这里保证了buf非空。
        blen = 0;
        while (i < len && islower(str[i])) {
            buf[blen++] = str[i++];
        }
        buf[blen] = 0;
        Add(buf);
    }
}

int main(int argc, char** argv) {
    // 读入行直到EOF。
    while (gets(line)) {
        ParseLine(line, strlen(line));
    }
    sort(id, id + index, cmp);
    // 去重输出。
    int i = 0;
    while (i < index) {
        int v = id[i];
        puts(words[v]);
        int j = i;
        // 跳过相同的单词。
        while (j < index && !strcmp(words[v], words[id[j]])) {
            ++j;
        }
        i = j;
    }

    return 0;
}
