#include <cstdio>

const int Row = 20;
const int Col = 5;

// -1��ʾ�ѱ�Ԥ����
int seat[Row][Col];

// ���ι�Ʊ���������
#define MAXN 10

// һ�ι�Ʊ�ı�ŷ��䡣
struct {
    int data[MAXN];
    int len;
} ans;

bool Find(int n, int& row, int& col) {
    for (int i = 0; i < Row; ++i) {
        // ö��ÿһ����������λ���С�
        int j = 0;
        while (j < Col) {
            while (j < Col && -1 == seat[i][j]) {
                ++j;
            }
            int k = j;
            while (k < Col && -1 != seat[i][k]) {
                ++k;
            }
            int len = k - j;
            if (len >= n) {
                // ���÷���������seat=true.
                row = i;
                col = j;
                //				printf("row %d col %d\n", row, col);

                return true;
            }
            j = k;
        }
    }
    return false;
}

// Ϊn��Ʊ�����š�
void Do(int n) {
    ans.len = 0;
    // �����Ƿ����������n����λ��
    int row, col;
    if (Find(n, row, col)) {
        // ��n��λ�ñ�ǡ�
        for (int j = col; j < col + n; ++j) {
            ans.data[ans.len++] = seat[row][j];
            seat[row][j] = -1;
        }
    } else {
        for (int i = 0; i < Row; ++i) {
            for (int j = 0; j < Col; ++j) {
                if (seat[i][j] != -1) {
                    ans.data[ans.len++] = seat[i][j];
                    seat[i][j] = -1;
                    if (ans.len == n) { return; }
                }
            }
        }
    }
}

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

void Init() {
    int id = 1;
    for (int i = 0; i < Row; ++i) {
        for (int j = 0; j < Col; ++j) {
            seat[i][j] = id++;
        }
    }
    //	for (int i=0;i<Row;++i) {
    //		for (int j=0;j<Col;++j) {
    //			printf("%d ", seat[i][j]);
    //		}
    //		printf("\n");
    //	}
}

int main(int argc, char** argv) {
    Init();
    int N;
    scanf("%d", &N);
    while (N--) {
        int p;
        scanf("%d", &p);
        Do(p);
        for (int i = 0; i < ans.len; ++i) {
            printf("%d%s", ans.data[i], i == ans.len - 1 ? "\n" : " ");
        }
    }

    return 0;
}
