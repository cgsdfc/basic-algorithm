#include <iostream>
#include <string>
using namespace std;

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

int main(int argc, char** argv) {
    /*
    cin输入字符串，和scanf("%s", buf)一样，以空格或换行为分界线。
    */
    string str;
    cin >> str;
    cout << str;
    return 0;
}
