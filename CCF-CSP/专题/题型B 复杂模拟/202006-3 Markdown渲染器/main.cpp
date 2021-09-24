#include <cctype>
#include <cstdio>
#include <cstring>
#include <iostream> // 不知道一行是否有上限，数组不好开。
#include <string>
#include <vector>
using namespace std;

int W; // 终端宽度。

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

// 只包含空白字符的行。
bool EmptyLine(string &str) {
  for (int i = 0; i < str.size(); ++i) {
    if (!isspace(str[i])) {
      // 非空白。
      return false;
    }
  }
  return true;
}

vector<string> Lines;
typedef vector<string> List;

struct Render {
  int N;     // 当前行数。
  bool flag; // 当前是否为第一行。
  int now;   // 当前行多少字符。

  Render() {
    N = 0;
    flag = true;
    now = 0;
  }
  void Put(char c) {
    // 输出一个字符。
    ++now;
    cout << c;
  }
  void Puts(char s[]) {
    now += strlen(s);
    cout << s;
  }
  void NewLine() {
    ++N;
    now = 0;
    cout << '\n';
  }
  void Print() { cout << N << endl; }
  void DoList(List &li) {
    //		puts("dolist");
    if (flag) {
      flag = false;
    } else {
      NewLine();
    }
    for (int i = 0; i < li.size(); ++i) {
      // 每个项目。
      Puts(" . ");
      string &str = li[i];
      int j = 0;
      while (j < str.size()) {
        if (now == W) {
          NewLine();
          Puts("   ");
        } else {
          Put(str[j]);
          ++j;
        }
      }
      NewLine();
    }
  }
  void DoPara(string &str) {
    // 渲染一个段落。
    //		puts("dopara");
    if (flag) {
      flag = false;
    } else {
      NewLine();
    }
    int i = 0;
    while (i < str.size()) {
      if (now == W) {
        // 满了，换行，清零。
        NewLine();

        // 如果剩下的字符是空格，就跳过。
        while (i < str.size() && str[i] == ' ') {
          ++i;
        }
      } else {
        Put(str[i]);
        ++i;
      }
    }
    NewLine();
  }
};

bool IsList(string &str) {
  return str.size() >= 2 && str[0] == '*' && str[1] == ' ';
}

bool IsItem(string &str) {
  return !EmptyLine(str) && str.size() >= 2 && str[0] == ' ' && str[1] == ' ';
}

Render R;

int main(int argc, char **argv) {
  //	cin.sync_with_stdio(false);

  cin >> W;
  string line;
  while (getline(cin, line)) {
    Lines.push_back(line);
  }
  int i = 0;
  while (i < Lines.size()) {
    //		printf("i %d\n",i);

    while (i < Lines.size() && EmptyLine(Lines[i])) {
      ++i; // 跳过所有空行。
    }
    if (i >= Lines.size()) {
      break;
    }
    string &str = Lines[i];
    // 处理列表。
    if (IsList(Lines[i])) {
      List li;
      while (i < Lines.size() && IsList(Lines[i])) {
        // 一个项目的首行。
        string item = Lines[i].substr(2); // 去掉 *_
        ++i;
        // 剩下的行。
        while (i < Lines.size() && IsItem(Lines[i])) {
          item.append(Lines[i].substr(2));
          ++i;
        }
        // 去掉item的首尾空格。
        string item2;
        li.push_back(item);
      }
      R.DoList(li);
    } else {
      bool flag = true; // 第一行。
      string para;      // 一个段落。
      while (i < Lines.size() && !EmptyLine(Lines[i]) && !IsList(Lines[i])) {
        if (flag) {
          flag = false;
        } else {
          para.push_back(' ');
        }
        // 去掉首尾连续空格。
        int j = 0;
        while (j < str.size() && str[j] == ' ') {
          ++j;
        }
        int k = str.size() - 1;
        while (k >= 0 && str[k] == ' ') {
          --k;
        }
        while (j <= k) {
          para.push_back(str[j]);
          ++j;
        }
        ++i;
      }
      // 得到一个新段落。
      R.DoPara(para);
    }
  }
  R.Print();

  return 0;
}
