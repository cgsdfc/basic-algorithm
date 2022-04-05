#include <cstdio>
#include <cstring>
/*
ȥ����䣬C�Ķ������ǿ��Բ���ǰ׺�����õġ�
*/
using namespace std;
/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

#define MAXN 25

struct Node {
    int data;
    /*
    flag ��ʾ���Ԫ���Ѿ����ڶ������е�Ԫ�ز�����ˡ�
    һ�κϷ��Ĳ����ǣ�·��������Ԫ�ض���������ˣ���������Ԫ��û�б��������
    ����ڶ������е�ȫ��Ԫ�صĲ��붼�ǺϷ��ģ���ô�ڶ������к͵�һ�������γ���ͬ��
    BST��
    �ж�֮ǰҪ��flagȫ��false����
    */
    bool flag;
    int lchild, rchild;
} node[MAXN];

int N;
// index �� strings.h �Ŀ⺯����
int Index;

int NewNode(int v) {
    node[Index].data = v;
    node[Index].lchild = node[Index].rchild = -1;
    node[Index].flag = false;
    return Index++;
}

void Reset(int root) {
    if (root != -1) {
        node[root].flag = false;
        Reset(node[root].lchild);
        Reset(node[root].rchild);
    }
}

// �����ر���
void Insert(int& root, int x) {
    if (root == -1) {
        root = NewNode(x);
        return;
    }
    if (node[root].data == x) { return; }
    if (x < node[root].data) {
        Insert(node[root].lchild, x);
    } else {
        Insert(node[root].rchild, x);
    }
}

int Create() {
    char str[20];
    scanf("%s", str);
    int len = strlen(str);
    int root = -1;

    for (int i = 0; i < len; ++i) {
        Insert(root, str[i] - '0');
    }
    return root;
}

// �ж�һ�β����Ƿ�Ϸ���
bool Check(int root, int x) {
    if (root == -1) {
        // û��x��λ�á�
        return false;
    }
    if (node[root].data == x) {
        // �ҵ���x��
        if (node[root].flag) {
            // x�����˶�Ρ�
            return false;
        } else {
            node[root].flag = true;
            return true;
        }
    } else {
        // ������;��
        if (!node[root].flag) {
            /*
            Ϊʲô��;�ڵ��������true�Ͳ��У�
            �����;��һ��false����ȱ�ڣ���ô��ʾ���ȱ�ڵ�Ԫ��
            ��û�г��֣������ʱ�Ȳ���x����ȷλ�ã��Ⱥ����ٲ���ȱ�ڵ�Ԫ�أ�
            ��Υ����BST�����ԭ����Ϊ���������Ĳ���˳�򣬺������Ľڵ㲻���ܷ�����
            ��Ϊǰ�����Ľڵ�ĸ��ڵ㡣��ֻ������Ϊ���ӽڵ㡣
            ����������������������˵���ڵڶ�������ʵ���ؽ��������Ĺ����У�x����Ϊȱ�ڵĸ��ڵ㣬
            �����Ǻ��ӽڵ㡣

            ���仰˵�����ڶ��������뽨�����С��Ȳ����Ϊ���ף������Ϊ���ӡ����ص㣬
            һ���ڵ��ڲ���֮ǰ������ȫ�����Ƚڵ���붼�Ѿ������ˡ�
            */
            return false;
        }
        // �����ݹ��顣
        if (x < node[root].data) {
            return Check(node[root].lchild, x);
        } else {
            return Check(node[root].rchild, x);
        }
    }
}

// �ж����к�BST�Ƿ��Ӧ��
bool Judge(int root, char str[], int len) {
    for (int i = 0; i < len; ++i) {
        if (!Check(root, str[i] - '0')) { return false; }
    }
    return true;
}

// �ж��������������Ƿ��Ӧͬһ�Ŷ�����������
// ���Խ���������Ȼ���жϣ�������ķ����ǽ�һ������Ȼ������һ����������ѯ�������
int main(int argc, char** argv) {
    int N;
    while (scanf("%d", &N), N) {
        Index = 0;
        int root = Create();
        while (N--) {
            char str[20];
            scanf("%s", str);
            bool ans = Judge(root, str, strlen(str));
            puts(ans ? "YES" : "NO");
            Reset(root);
        }
    }
    return 0;
}
