#include <cctype>
#include <cstdio>
#include <cstring>
#include <iostream> // ��֪��һ���Ƿ������ޣ����鲻�ÿ���
#include <string>
#include <vector>
using namespace std;

int W; // �ն˿�ȡ�

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

// ֻ�����հ��ַ����С�
bool EmptyLine(string &str) {
  for (int i = 0; i < str.size(); ++i) {
    if (!isspace(str[i])) {
      // �ǿհס�
      return false;
    }
  }
  return true;
}

vector<string> Lines;
typedef vector<string> List;

struct Render {
  int N;     // ��ǰ������
  bool flag; // ��ǰ�Ƿ�Ϊ��һ�С�
  int now;   // ��ǰ�ж����ַ���

  Render() {
    N = 0;
    flag = true;
    now = 0;
  }
  void Put(char c) {
    // ���һ���ַ���
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
      // ÿ����Ŀ��
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
    // ��Ⱦһ�����䡣
    //		puts("dopara");
    if (flag) {
      flag = false;
    } else {
      NewLine();
    }
    int i = 0;
    while (i < str.size()) {
      if (now == W) {
        // ���ˣ����У����㡣
        NewLine();

        // ���ʣ�µ��ַ��ǿո񣬾�������
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
      ++i; // �������п��С�
    }
    if (i >= Lines.size()) {
      break;
    }
    string &str = Lines[i];
    // �����б�
    if (IsList(Lines[i])) {
      List li;
      while (i < Lines.size() && IsList(Lines[i])) {
        // һ����Ŀ�����С�
        string item = Lines[i].substr(2); // ȥ�� *_
        ++i;
        // ʣ�µ��С�
        while (i < Lines.size() && IsItem(Lines[i])) {
          item.append(Lines[i].substr(2));
          ++i;
        }
        // ȥ��item����β�ո�
        string item2;
        li.push_back(item);
      }
      R.DoList(li);
    } else {
      bool flag = true; // ��һ�С�
      string para;      // һ�����䡣
      while (i < Lines.size() && !EmptyLine(Lines[i]) && !IsList(Lines[i])) {
        if (flag) {
          flag = false;
        } else {
          para.push_back(' ');
        }
        // ȥ����β�����ո�
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
      // �õ�һ���¶��䡣
      R.DoPara(para);
    }
  }
  R.Print();

  return 0;
}
