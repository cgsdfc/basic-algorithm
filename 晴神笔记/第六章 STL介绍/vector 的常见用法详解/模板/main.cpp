//#include <iostream>
#include <stdio.h>
#include <vector>
using namespace std;

/*
vector ÓÃ·¨Ä£°å¡£
*/

void Init(vector<int> &vi) {
  for (int i = 1; i <= 5; ++i) {
    vi.push_back(i);
  }
}

void VectorSize() {
  vector<int> vi;
  Init(vi);
  printf("%d\n", vi.size());
}

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

int main(int argc, char **argv) {
  vector<int> vi;
  for (int i = 1; i <= 5; ++i) {
    vi.insert(vi.end(), i);
  }
  for (vector<int>::iterator it = vi.begin(); it != vi.end(); ++it) {
    printf("%d\n", *it);
  }
  return 0;
}
