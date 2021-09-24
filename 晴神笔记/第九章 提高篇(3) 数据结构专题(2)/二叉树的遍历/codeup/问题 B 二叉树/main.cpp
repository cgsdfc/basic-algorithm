#include <iostream>

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

/*
ֱ�ӱ�����MΪ���������������ڵ�����
��Ȼ���ܴ���ĳ�ֹ��ɣ����Լ������������Ϊ����ȫ��������
�����ڼ��������������£�ֱ��ģ���ǱȽ�������ȷ��˼·��
*/

int N; // �ڵ�����
int M; // �������ڵ㡣

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
DFS ֱ�Ӿͳ�ʱ�ˡ�
����Ҫ������ȫ�����������ʡ�
*/
// �Ƿ��Ӷ�logN
int BFS() {
  int left, right; // ��ǰ�����������ҡ�
  left = right = M;
  int ans = 0; // �ڵ�����

  // ��ߴ��ڣ���˲���ڡ�
  while (left <= N) {
    if (right <= N) {
      // �ұߴ��ڣ���˲������Ĵ��ڡ�
      ans += right - left + 1;
    } else {
      // ��ߴ��ڣ��ұ߲����ڣ��򵽴�����������ȱ�ڴ���
      // ��ȫ������ֻ��������Ͳ����ȱ�ڡ�
      ans += N - left + 1;
    }
    // ��һ�㡣
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
