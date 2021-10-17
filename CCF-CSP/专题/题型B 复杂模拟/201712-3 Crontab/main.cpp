#include <cassert>
#include <cstdio>
#include <cstring>
#include <string>
#include <utility>
#include <vector>
using namespace std;

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */
#define MAXL 105
char line[MAXL];

bool IsLeap(int year) {
    return (year % 400 == 0) || (year % 4 == 0 && year % 100 != 0);
}

const int Day[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

const char MonName[][5] = {"",    "jan", "feb", "mar", "apr", "may", "jun",
                           "jul", "aug", "sep", "oct", "nov", "dec"};
const char WeekName[][5] = {"sun", "mon", "tue", "wed", "thu", "fri", "sat"};

int MonthDay(int year, int mon) {
    // 注意，闰年的二月加一天。
    return Day[mon] + (mon == 2 && IsLeap(year));
}

int GetWeek(int y, int m, int d) {
    int yy = 1970;
    int mm = 1;
    int dd = 1;
    int ww = 4;
    // 注意，这里出bug了，条件是或，不是与。
    while (yy < y || mm < m || dd < d) {
        ++dd;
        ww = (ww + 1) % 7;
        if (dd == MonthDay(yy, mm) + 1) {
            dd = 1;
            ++mm;
        }
        if (mm == 13) {
            mm = 1;
            ++yy;
        }
    }
    return ww;
}

struct Time {
    int y, mon, d, h, min;
    int w;  // week

    void Read() {
        scanf("%04d%02d%02d%02d%02d", &y, &mon, &d, &h, &min);
        w = GetWeek(y, mon, d);
        //		printf("w %d\n", w);
    }
    void Print() {
        printf("%04d%02d%02d%02d%02d", y, mon, d, h, min);
    }
    friend bool operator==(const Time& a, const Time& b) {
        return a.y == b.y && a.mon == b.mon && a.d == b.d && a.h == b.h && a.min == b.min;
    }
    void inc() {
        // 自增1分钟。
        min++;
        if (min == 60) {
            min = 0;
            h++;
        }
        if (h == 24) {
            h = 0;
            ++d;
            w = (w + 1) % 7;
        }
        if (d == MonthDay(y, mon) + 1) {
            d = 1;
            ++mon;
        }
        if (mon == 13) {
            mon = 1;
            ++y;
        }
    }
};

enum {
    STAR,
    EQL,  // equal
    RNG,  // range.
};
const char Name[][10] = {"star", "eql", "rng"};

typedef pair<int, int> Range;

struct Cond {
    int type;
    int eql;  // EQL.
    vector<Range> rng;

    bool Match(int val) {
        int i;
        switch (type) {
            case STAR: return true;
            case EQL: return eql == val;
            default:
                for (i = 0; i < rng.size(); ++i) {
                    Range p = rng[i];
                    if (p.first <= val && val <= p.second) { return true; }
                }
                return false;
        }
    }
};

#define MAXC 5

struct Node {
    // 所有的条件。
    Cond conds[MAXC];
    char cmd[MAXL];

    Node() {}
    bool Match(const Time& t) {
        return conds[0].Match(t.min) && conds[1].Match(t.h) && conds[2].Match(t.d) && conds[3].Match(t.mon) &&
               conds[4].Match(t.w);
    }
};

vector<Node> tab;

// 把从i开始的字符串转换为数字，考虑数字和缩写混合的情况。
int ParseNum(char str[], int& i, int len) {
    if (isdigit(str[i])) {
        int n = 0;
        while (i < len && isdigit(str[i])) {
            n = n * 10 + (str[i] - '0');
            ++i;
        }
        return n;
    }
    string buf;
    while (i < len && isalpha(str[i])) {
        buf.push_back(tolower(str[i]));
        ++i;
    }
    for (int i = 1; i <= 12; ++i) {
        if (buf == MonName[i]) { return i; }
    }
    for (int i = 0; i <= 6; ++i) {
        if (buf == WeekName[i]) { return i; }
    }
    return -1;
}

void ParseCond(Cond& cd, char str[], int len) {
    if (len == 1 && str[0] == '*') {
        cd.type = STAR;
        return;
    }
    bool rng = false;
    // 看是否为单独取值。
    for (int i = 0; i < len; ++i) {
        if (str[i] == ',' || str[i] == '-') {
            rng = true;
            break;
        }
    }
    if (!rng) {
        // eql
        cd.type = EQL;
        int i = 0;
        cd.eql = ParseNum(str, i, len);
        assert(i == len);
        return;
    }
    cd.type = RNG;
    // 逗号分割的列表。
    int i = 0;
    while (i < len) {
        int b = ParseNum(str, i, len);
        int e = b;
        if (str[i] == '-') {
            ++i;
            e = ParseNum(str, i, len);
        }
        Range r = {b, e};
        cd.rng.push_back(r);
        if (i >= len) { break; }
        if (str[i] == ',') { ++i; }
    }
}

void Parse(Node& node) {
    for (int i = 0; i < MAXC; ++i) {
        char str[MAXL];
        scanf("%s", str);
        ParseCond(node.conds[i], str, strlen(str));
    }
    scanf("%s", node.cmd);
}

int N;

void Print() {
    for (int i = 0; i < N; ++i) {
        printf("%s", tab[i].cmd);
        for (int j = 0; j < MAXC; ++j) {
            Cond& cd = tab[i].conds[j];
            int type = cd.type;
            printf(" %s", Name[type]);
            if (type == EQL) {
                printf(" %d", cd.eql);
            } else if (type == RNG) {
                for (int k = 0; k < cd.rng.size(); ++k) {
                    Range r = cd.rng[k];
                    printf(" <%d,%d>", r.first, r.second);
                }
            }
        }
        puts("");
    }
}

int main(int argc, char** argv) {
    scanf("%d", &N);
    Time a, b;
    a.Read();
    b.Read();

    tab.resize(N);
    for (int i = 0; i < N; ++i) {
        Parse(tab[i]);
    }

    for (; !(a == b); a.inc()) {
        for (int i = 0; i < N; ++i) {
            if (tab[i].Match(a)) {
                a.Print();
                printf(" %s\n", tab[i].cmd);
            }
        }
    }
    return 0;
}
