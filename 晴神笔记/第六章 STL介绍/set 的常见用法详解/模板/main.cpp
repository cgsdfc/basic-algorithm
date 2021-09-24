#include <iostream>
#include <set>
using namespace std;

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

void SetIter() {
  set<int> st;
  st.insert(3);
  st.insert(5);
  st.insert(2);
  st.insert(3);
  for (set<int>::iterator it = st.begin(); it != st.end(); it++) {
    printf("%d\n", *it);
  }
}

void SetFind() {
  set<int> st;
  for (int i = 1; i <= 3; ++i) {
    st.insert(i);
  }
  set<int>::iterator it = st.find(2);
  printf("%d\n", *it);
}

int main(int argc, char **argv) {
  SetFind();
  return 0;
}
