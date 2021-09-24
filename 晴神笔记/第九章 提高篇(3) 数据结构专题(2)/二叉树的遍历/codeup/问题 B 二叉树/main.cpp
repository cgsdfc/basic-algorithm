#include <iostream>

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

/*
直接遍历以M为根的子树，计数节点数，
虽然可能存在某种规律，可以计算出来，（因为是完全二叉树）
但是在计算量不大的情况下，直接模拟是比较容易正确的思路。
*/

int N; // 节点数。
int M; // 子树根节点。

// void DFS(int root, int& tot) {
//	if (root > N) return;
//	++tot;
//	DFS(2*root, tot);
//	DFS(2*root+1, tot);
//}
//
// int main(int argc, char** argv) {
//	int M;
//	while (scanf("%d%d", &M, &N) != EOF && M && N) {
//		int tot=0;
//		DFS(M, tot);
//		printf("%d\n", tot);
//	}
//	return 0;
//}

/*
DFS 直接就超时了。
还是要利用完全二叉树的性质。
*/
// 是否复杂度logN
int BFS() {
  int left, right; // 当前层的最左和最右。
  left = right = M;
  int ans = 0; // 节点数。

  // 左边存在，则此层存在。
  while (left <= N) {
    if (right <= N) {
      // 右边存在，则此层完整的存在。
      ans += right - left + 1;
    } else {
      // 左边存在，右边不存在，则到达了整棵树的缺口处，
      // 完全二叉树只可能在最低层存在缺口。
      ans += N - left + 1;
    }
    // 下一层。
    left *= 2;
    right = right * 2 + 1;
  }
  return ans;
}

int main() {
  while (scanf("%d%d", &M, &N) != EOF && M && N) {
    int ans = BFS();
    printf("%d\n", ans);
  }
  return 0;
}
