#include <iostream>

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

/*
�������Ĳ���/����/ɾ��/���/��С �����Ĵ�Cʵ�֣�
���Բο������ݽṹ�� Ŀ¼�µĴ��롣
��Cʵ�ֵ�һ���ص�����÷���ֵ������C++�����ô��Ρ�
*/

/*
���ڶ��������һ�������ֵ�������Ǳ�ţ���̬д����һ�����ƾ�û���ˣ�
��Ȼ��̬д��û���ڴ�й©��
*/

/*
��̬д��������ͨ�Ķ�������࣬���Ǳر�newNode������
��Ϊ�ڵ��Ǹ��ݼ�ֵ����ġ�
*/
#define MAXN 100

int index; // Index �ȽϺã�index��STL������

struct Node {
    int data;  // ��ֵ��
    int lchild;
    int rchild;
} node[MAXN];

// �ڵ���亯����Ҳ�ǳ�ʼ��������
/*
ע�⣬�ڵ�ɾ�������޷��ٴ����õģ����һ����ĿҪ��
��ɾ���ڵ㣬Ȼ���ֲ���ڵ㣬������Σ����ܵ��½ڵ�ľ���
�� index ���� MAXN�����������ĿҪ��Ķ������������������
��Ҫ���Ƕ�̬д���ˡ������Ŀֻ�в���Ͳ��Ҳ�������ô��̬д����ȫ
����Ӧ����
*/
int NewNode(int data) {
    node[index].data = data;
    node[index].lchild = node[index].rchild = -1;
    return index++;
}

/*
��root�в���x�����ؽڵ��š��ݹ�д����
*/
int search(int root, int x) {
    if (root == -1) {
        // ����˵������ʧ�ܡ�
        return -1;
    }
    if (node[root].data == x) {
        // ���ҳɹ���
        return root;
    }
    // �������������������ݹ顣
    if (x < node[root].data) {
        // data�൱��һ��·�꣬data��xС������ߣ��������ұߡ�
        return search(node[root].lchild, x);
    } else {
        return search(node[root].rchild, x);
    }
}

/*
�����ɾ���㷨�Ͳ��Ҷ�����ϵ����Ϊ����Ҫ�ҵ�Ԫ�ز����ڵ�λ�ý��в��룬
ɾ��Ҫ�ҵ�Ԫ�����ڵ�λ�ý���ɾ����
���Բ����ɾ�����в��ҵĿ�ܡ�

ͬʱ����Ϊ�����ɾ�����Ƕ����Ľṹ���޸ģ�����rootҪ�����á�
*/

/*
����x������ɹ�����true������ʧ�ܣ�Ԫ���Ѵ��ڣ�����false��
�������Ҫ�������ʧ�ܵ���������Է���void��
*/
bool insert(int& root, int x) {
    if (root == -1) {
        // ����ʧ�ܾ��ǲ����λ�á�
        root = NewNode(x);
        return true;
    }
    if (node[root].data == x) {
        // Ԫ���Ѵ��ڡ�
        return false;
    }
    // ���ҡ�
    if (x < node[root].data) {
        return insert(node[root].lchild, x);
    } else {
        return insert(node[root].rchild, x);
    }
}

/*
ɾ��Ԫ��x�����Ԫ�ز����ڷ���false�����򷵻�true��
ɾ�������Ƚϸ��ӡ�

ɾ����Ҫ�����ڣ���ɾ��Ԫ��x��ǰ���ͺ�̣���
1. x��ǰ����С��x�����Ԫ�أ���x�������������ֵ��
2. x�ĺ�̼�����x����СԪ�أ���x������������Сֵ��
x��ǰ���ͺ�̣�������ڣ��������Դ���x��λ�ö�ά��BST�����ʡ�

�㷨��
1. ���ҵ�x���ڵĽڵ㡣
2. ���x��Ҷ�ӣ�ֱ���ÿա�
3. ���x����ǰ������̣����ҵ�ǰ������ǰ����ֵ����x��Ȼ��ݹ�ɾ��ǰ����
*/

/*
�����ֵ��һֱ���ҡ�
����Сֵ��һֱ����
*/
int findMax(int root) {
    while (node[root].rchild != -1) {
        root = node[root].rchild;
    }
    return root;
}

bool deleteNode(int& root, int x) {
    if (root == -1) {
        // Ԫ�ز����ڡ�
        return false;
    }
    if (node[root].data < x) { return deleteNode(node[root].lchild, x); }
    if (node[root].data > x) { return deleteNode(node[root].rchild, x); }
    // �ҵ���x��
    if (node[root].lchild == -1 && node[root].rchild == -1) {
        // ����Ҷ�ӡ�
        root = -1;  // ֱ��ɾ����
        return true;
    }
    if (node[root].lchild != -1 && node[root].rchild != -1) {
        // �������Ӷ��У�������ǰ��/��̴��档
        // ���Խ���ɾ��ǰ��/��̡�
        // ��ǰ����
        int pre = findMax(node[root].lchild);
        // ǰ�������ݸ���xԪ�ء�
        node[root].data = node[pre].data;
        // ɾǰ����
        return deleteNode(node[root].lchild, node[pre].data);
    }
    if (node[root].lchild != -1) {
        // ֻ�����ӡ������Ӵ���root��
        root = node[root].lchild;
    } else {
        // ֻ���Һ��ӡ�
        root = node[root].rchild;
    }
    return true;
}

int main(int argc, char** argv) {
    return 0;
}
