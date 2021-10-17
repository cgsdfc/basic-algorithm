#include <cassert>
#include <cstdio>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>
using namespace std;

// typedef vector<int> IDs;
map<string, set<int>> Title, Author, KW, Pub, Year;

void Print(map<string, set<int>>& mp, string& key) {
    if (mp.find(key) == mp.end()) {
        printf("Not Found\n");
        return;
    }
    set<int>& st = mp[key];
    for (set<int>::iterator it = st.begin(); it != st.end(); ++it) {
        printf("%07d\n", *it);
    }
}

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

// 用cin读入关键字的方法。
void ReadKeywords(int id) {
    string key;
    while (cin >> key) {
        KW[key].insert(id);
        char c = getchar();
        if (c == '\n') break;
    }
}

int main(int argc, char** argv) {
    /*
    注意，freopen 也可以对cin，cout进行重定向。
    并且，cin，cout和scanf，printf混用，也没问题。
    */
#ifndef ONLINE_JUDGE
    freopen("./in.txt", "r", stdin);
#endif

    int N;
    scanf("%d", &N);
    while (N--) {
        int id;
        scanf("%d", &id);
        getchar();

        string str;
        getline(cin, str);  // Title
        Title[str].insert(id);

        getline(cin, str);  // Author
        Author[str].insert(id);

        getline(cin, str);  // Keywords
        int i = 0;
        // 解析KW
        while (i < str.size()) {
            string word;
            while (i < str.size() && str[i] != ' ') {
                word.push_back(str[i]);
                ++i;
            }
            KW[word].insert(id);
            if (i < str.size() && str[i] == ' ') { ++i; }
        }

        getline(cin, str);  // Publisher
        Pub[str].insert(id);

        getline(cin, str);  // Year
        Year[str].insert(id);
    }

    int M;
    scanf("%d", &M);
    while (M--) {
        int q;
        scanf("%d: ", &q);
        string str;
        getline(cin, str);

        printf("%d: %s\n", q, str.c_str());

        switch (q) {
            case 1: Print(Title, str); break;
            case 2: Print(Author, str); break;
            case 3: Print(KW, str); break;
            case 4: Print(Pub, str); break;
            case 5: Print(Year, str); break;
        }
    }
    return 0;
}
