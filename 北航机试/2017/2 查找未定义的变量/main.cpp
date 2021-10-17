#include <cctype>
#include <iostream>
#include <set>
#include <string>
#include <vector>
using namespace std;

// �Ϸ��ı��������Ϸ��ı�����
set<string> defined, undef;

// ���͹ؼ��֡�
// bool,char,short,int,unsigned,long,float,double
const char Type[][10] = {"bool", "char", "short", "int", "long", "unsigned", "float", "double"};
const int MAXT = 8;

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

// �Ϸ��ı�����ʼ����ĸ�»��ߡ�
bool IsBegin(char c) {
    return c == '_' || isalpha(c);
}

// �Ϸ��ı����м䣺��ĸ�����»��ߡ�
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
            ++i;  // �ҵ���һ����ʼ�ַ���
        }
        if (i >= str.size()) { break; }
        string iden;
        // ע��IsBegin������IsMid��
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
            continue;  // ͳ�ƹ��ˡ�
        }
        undef.insert(iden);
        printf("%s ", iden.c_str());
    }
    puts("");
}

/*
��STL������˼·����ȡ��һ�е����б�־�������˵����е����ͣ�����set
Ȼ����ȡ�ڶ��е����б�־����Ҳ�ǹ��˵����ͣ���ѯset���ɡ�
δ����ı����Ƿ���ظ����Ƿ�Ӧ��ÿ��δ�������ֻ���һ�Σ�

C���Ե��﷨��������ʲô�ã������δ���������ʲô��ͬ��ָ�����ʲô��ͬ��
��Ŀû��˵�����Ǿ͵�����򵥵ģ��������Ƿ�����ڶ�������������ˡ�
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
