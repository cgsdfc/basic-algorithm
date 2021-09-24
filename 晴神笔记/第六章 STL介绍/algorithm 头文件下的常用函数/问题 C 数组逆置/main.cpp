#include <algorithm>
#include <iostream>
/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */
using namespace std;

int main(int argc, char **argv) {
  string str;
  while (getline(cin, str)) {
    reverse(str.begin(), str.end());
    // 行输入必须getline，因为c++禁止了gets。
    printf("%s\n", str.c_str());
  }
  return 0;
}
