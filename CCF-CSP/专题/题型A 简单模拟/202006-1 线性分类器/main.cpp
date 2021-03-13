#include <cstdio>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int N; // ��ĸ�����
int M; // ��ѯ������

struct Point {
	int X, Y;
	char type;
};

#define MAXN 1005

Point p[MAXN];

int the[3]; // ֱ�ߵ�����������

// ���������ֱ�߷��̡� 
int Eval(Point& a) {
	return the[0]+the[1]*a.X+the[2]*a.Y;
}

/*
����ÿһ���㣬Ҫô�����㣬ҪôС���㣬
Ҫô��A��Ҫô��B��
���ڶ��Դ��������A��С�������B���������������ض�
���෴������������������B��С�������A������
����ȫ���㣬����Ҫôȫ��������Ҫôȫ��������������������ȷ�ķ�������
*/ 
bool Check(Point& a) {
	int v=Eval(a);
	return ('A'==a.type && v>0) || ('B'==a.type && v<0);
}

// �ж���ǰֱ���Ƿ��������ָ�����㡣 
bool Judge() {
	bool flag=Check(p[0]);
	for (int i=1;i<N;++i) {
		if (Check(p[i]) != flag) {
			// ���಻һ�¡� 
			return false;
		}
	}
	return true;
}

int main(int argc, char** argv) {
	scanf("%d%d",&N,&M);
	for (int i=0;i<N;++i) {
		// ����N���㡣
		char str[5];
		scanf("%d%d%s", &p[i].X, &p[i].Y, str);
		p[i].type=str[0];
	}
	for (int i=0;i<M;++i) {
		// ����M��ֱ�ߡ�
		for (int j=0;j<3;++j) {
			scanf("%d", &the[j]);
		}
		bool ans=Judge();
		puts(ans?"Yes":"No");
	}
	
	return 0;
}
