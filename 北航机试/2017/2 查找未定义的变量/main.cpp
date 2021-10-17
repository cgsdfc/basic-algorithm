#include <cctype>
#include <iostream>
#include <set>
#include <string>
#include <vector>
using namespace std;

// 合法的变量，不合法的变量。
set<string> defined, undef;

// 类型关键字。
// bool,char,short,int,unsigned,long,float,double
const char Type[][10] = {"bool", "char", "short", "int", "long", "unsigned", "float", "double"};
const int MAXT = 8;

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

// 合法的变量开始：字母下划线。
bool IsBegin(char c) {
    return c == '_' || isalpha(c);
}

// 合法的变量中间：字母数字下划线。
bool IsMid(char c) {
    return c == '_' || isalnum(c);
}

bool IsType(string& str) {
    for (int i = 0; i < MAXT; ++i) {
        if (!str.compare(Type[i])) { return true; }
    }
    return false;
}

void FindDefine(string& str) {
    int i = 0;
    defined.clear();
    while (i < str.size()) {
        while (i < str.size() && !IsBegin(str[i])) {
            ++i;  // 找到第一个开始字符。
        }
        if (i >= str.size()) { break; }
        string iden;
        // 注意IsBegin包括了IsMid。
        while (i < str.size() && IsMid(str[i])) {
            iden.push_back(str[i]);
            ++i;
        }
        if (!IsType(iden)) { defined.insert(iden); }
    }
}

void FindUndef(string& str) {
    int i = 0;
    undef.clear();
    while (i < str.size()) {
        while (i < str.size() && !IsBegin(str[i])) {
            i++;
        }
        if (i >= str.size()) { break; }
        string iden;
        while (i < str.size() && IsMid(str[i])) {
            iden.push_back(str[i]);
            ++i;
        }
        if (IsType(iden)) { continue; }
        if (defined.count(iden)) { continue; }
        if (undef.count(iden)) {
            continue;  // 统计过了。
        }
        undef.insert(iden);
        printf("%s ", iden.c_str());
    }
    puts("");
}

/*
用STL来做，思路是提取第一行的所有标志符，过滤掉所有的类型，插入set
然后提取第二行的所有标志符，也是过滤掉类型，查询set即可。
未定义的变量是否会重复？是否应该每个未定义变量只输出一次？

C语言的语法在这里有什么用？数组的未定义变量有什么不同？指针的有什么不同？
题目没有说明，那就当做最简单的，变量名是否出现在定义语句来处理了。
*/
typedef set<string>::iterator It;

int main(int argc, char** argv) {
    string str;
    getline(cin, str);
    FindDefine(str);
    //	for (It it=defined.begin();it!=defined.end();++it) {
    //		printf("%s\n", it->c_str());
    //	}

    getline(cin, str);
    FindUndef(str);

    return 0;
}
