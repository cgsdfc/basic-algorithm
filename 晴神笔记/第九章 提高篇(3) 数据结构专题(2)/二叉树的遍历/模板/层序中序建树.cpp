#include <cstdio>

using namespace std;

/*
����������

����˼�룺
1. ����ĵ�һ��Ԫ���ǵ�ǰ�ĸ�R��
2. �������У�����R������������������������
3. �����������������������򣬰Ѳ��򻮷�Ϊ�������Ĳ�����������Ĳ���
ע�������ص㣺������ԭ�����е�˳�򣬵���������һ��������Ԫ���������
�͵õ�����������Ĳ���

����ݹ��㷨��һ��Ҫ�õ������Ķ�Ӧ�Ĳ��������
*/

struct Node {
    int data;
    Node* lchild;
    Node* rchild;

    Node(int v) {
        data = v;
        lchild = rchild = NULL;
    }
};

#define MAXN 100

int in[MAXN];     // �������С�
int layer[MAXN];  // �������С�

// ������Ϊ�������������������ģ����Բ���Ҫ�����µĿռ䣬
// �������Ĳ����������ģ�Ҫ�ٳ����ŵ��µ����飬����layer��len���ǵ�ǰ
// �����Ĳ���inL��inRָʾ��ǰ����������
Node* Create(int inL, int inR, int layer[], int len) {
    // ����Ϊ�գ��������
    if (len <= 0) { return NULL; }

    int v = layer[0]; // �������Ԫ�ؾ��Ǹ���
    Node* root = new Node(v);
    int k;
    // �ҵ����������λ�ã��������ܵõ�����������
    for (int i = inL; i <= inR; ++i) {
        if (in[i] == v) {
            k = i;
            break;
        }
    }

    // ���������Ĳ������С�
    int layerL[MAXN], lenL = 0;
    int layerR[MAXN], lenR = 0;
    // ����������������kָʾ�����õ������Ĳ���
    // ��һ��Ԫ�ز��Ǹ��������������������г��֣����������������Ĳ���
    // ����������������Ĳ���
    for (int i = 1; i < len; ++i) {
        int x = layer[i];
        bool isL = false;
        // ���x��������������������x���������������������������
        for (int j = inL; j < k; ++j) {
            if (in[j] == x) {
                isL = true;
                break;
            }
        }
        if (isL) {
            layerL[lenL++] = x;
        } else {
            layerR[lenR++] = x;
        }
    }
    // ������������������Ͳ��򶼵õ��ˡ�
    root->lchild = Create(inL, k - 1, layerL, lenL);
    root->rchild = Create(k + 1, inR, layerR, lenR);
    return root;
}
