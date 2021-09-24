#include <algorithm>
#include <iostream>
#include <string>
using namespace std;

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

/*
注意：
1. permutation 的拼写，不会可以用输入法。

2. 固定模板：
        1. str 已经是第一个排列，即字典序从小到大的有序序列。
        2. 用 do-while，循环的条件是 next_permutation。
        3. 在do-while中输出str，则效果是按字典序从小到大输出str元素的全部排列。

3. 这个函数的返回值：
        1.
返回true，则输入的排列存在下一个排列，并且输入的序列被原地修改为下一个排列。
        2.
返回false，则输入的排列是最后一个排列，因而不存在下一个排列，但是输入序列被
        原地修改为第一个排列，即回到原点。
*/

int main(int argc, char **argv) {
  string str;
  while (cin >> str) {
    do {
      printf("%s\n", str.c_str());
    } while (next_permutation(str.begin(), str.end()));
    printf("\n");
  }
  return 0;
}
