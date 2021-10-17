#include <algorithm>  // find
#include <cstdio>
#include <vector>

using namespace std;

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

#define MAXN 1005
int N, M;

/*
N��ѧ������1--N��ţ�����M��������
��vectorģ�⣬���Ӷ�ΪO(MN)��
*/

// vector<int> vi;
// typedef vector<int>::iterator It;

int A[MAXN];

int Find(int x) {
    for (int i = 0; i < N; ++i) {
        if (x == A[i]) return i;
    }
    return -1;
}

void Insert(int x, int pos, int off) {
    /*
    �ҵ�x��������λ���ƶ�off��
    */
    if (off > 0) {
        // ����ơ�
        while (off--) {
            A[pos] = A[pos + 1];
            pos++;
        }
    } else {
        // ��ǰ�ơ�
        while (off++) {
            A[pos] = A[pos - 1];
            --pos;
        }
    }
    A[pos] = x;
}

int main(int argc, char** argv) {
    scanf("%d%d", &N, &M);
    for (int i = 1; i <= N; ++i) {
        A[i - 1] = i;
    }
    while (M--) {
        int p, q;
        scanf("%d%d", &p, &q);
        // ѧ��Ϊp��q���ƶ���λ������
        int pos = Find(p);
        Insert(p, pos, q);
    }
    for (int i = 0; i < N; ++i) {
        printf("%d%s", A[i], i == N - 1 ? "\n" : " ");
    }

    return 0;
}
