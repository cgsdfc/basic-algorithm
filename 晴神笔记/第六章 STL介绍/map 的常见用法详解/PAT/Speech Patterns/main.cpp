#include <cctype>
#include <cstdio>
#include <iostream>
#include <map>
#include <string>
using namespace std;

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

map<string, int> count;

int main(int argc, char **argv) {
  // OJ的C++不让我们用gets
  string str;
  getline(cin, str);
  int i = 0;
  while (i < str.size()) {
    // 先跳过非法字符串。
    while (i < str.size() && !isalnum(str[i])) {
      ++i;
    }
    // 如果没有了，就不用继续。
    if (i == str.size()) {
      break;
    }
    string word;
    while (i < str.size() && isalnum(str[i])) {
      // 注意不区分大小写。
      word.push_back(tolower(str[i]));
      ++i;
    }
    count[word]++;
  }
  // count按照字典序排序，只要求int最大的string即可。
  int max = -1;
  string word;
  for (map<string, int>::iterator it = count.begin(); it != count.end(); ++it) {
    //		printf("%s %d\n", it->first.c_str(), it->second);

    if (it->second > max) {
      max = it->second;
      word = it->first;
    }
  }
  printf("%s %d\n", word.c_str(), max);

  return 0;
}
