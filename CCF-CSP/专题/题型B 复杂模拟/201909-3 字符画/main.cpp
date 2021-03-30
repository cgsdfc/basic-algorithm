#include <iostream>
#include <sstream>
#include <cstdio>
#include <cstring>
#include <cassert>
using namespace std;

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int M, N; // ���������� 
int P, Q; // С��������������� 

// �����Ϊ�ַ�������ת��Ϊת�����С� 
ostringstream output;

struct Color {
	int data[3];
	Color(){
		// Ĭ���Ǻ�ɫ����ȫ�㡣 
		memset(data, 0, sizeof(data));
	}
	
	friend bool operator==(const Color& a, const Color& b) {
		return 0==memcmp(a.data, b.data, sizeof(a.data));
	}
	friend bool operator!=(const Color& a, const Color& b) {
		return !(a==b);
	}
};

const Color black; // Ĭ��ֵ

#define MAXM 1950
#define MAXN 1100

typedef Color BitMap[MAXM][MAXN];
BitMap origin, now;

void Parse(const char str[], int len, Color& cl) {
	if (len==7) {
		sscanf(str, "#%02x%02x%02x",
			&cl.data[0],&cl.data[1],&cl.data[2]);
		return;
	}
	if (len==4) {
		string s="#";
		for (int i=1;i<len;++i) {
			s.append(2, str[i]);
		}
		return Parse(s.c_str(), s.length(), cl);
	}
	// len==2.
	string s="#";
	s.append(6, str[1]);
	Parse(s.c_str(), s.length(), cl);
}

const char ESC=27;
//const char ESC='#';

Color bg; // ��ǰ����ɫ��
 
// �ı䱳��ɫ�� 
void ChangeBg(Color& cl) {
	bg=cl;
	output<<ESC<<"[48;2";
	for (int i=0;i<3;++i) {
		output<<";"<<cl.data[i];
	}
	output<<"m";
}

// ���ñ���ɫ�� 
void ResetBg() {
	bg=black;
	output<<ESC<<"[0m";
}

#define MAXS 10

void Read() {
	// ��ԭʼ�������롣
	for (int i=0;i<M;++i) {
		for (int j=0;j<N;++j) {
			char buf[MAXS];
			scanf("%s",buf);
			Color& cl=origin[i][j];
			Parse(buf, strlen(buf), cl);
		}
	}
}

// ��i��jΪ���Ͻ�Ԫ�صģ�P QΪ��ߵ�СͼƬ��ƽ��ֵ�� 
Color Average(int i, int j) {
	Color ans;
	
	for (int ii=i;ii<i+P;++ii) {
		for (int jj=j;jj<j+Q;++jj) {
			Color& cl=origin[ii][jj];
			for (int k=0;k<3;++k) {
				ans.data[k] += cl.data[k];
			}
		}
	}
	for (int k=0;k<3;++k) {
		ans.data[k] /= P*Q; // СͼƬ������ô������ء� 
	}
	return ans;
}

// ��������ɫ�顣 �����ԭʼλͼ�ķֿ��ƽ��ֵ����������ԭʼ��λ�÷����µ�λͼ�� 
void Pooling() {
	for (int i=0;i<M;i+=P) {
		for (int j=0;j<N;j+=Q) {
//			printf("(%d,%d)\n",i,j);
			Color cl=Average(i, j);
			now[i/P][j/Q]=cl;
		}
	}
}

 
void Render() {
	bg=black; // ����Ϊ��ɫ��

	// �ѳػ����ͼƬ���Ϊת�����С��ո�ͻس���
	for (int i=0;i<M/P;++i) {
		for (int j=0;j<N/Q;++j) {
			Color& cl=now[i][j];
			if (cl != bg) {
				// ��ǰ��ɫû�б仯ʱ����Ҫ����κ�ת�����С�
				if (cl == black) {
					// �����Ĭ��ֵ��ȫ��ͬ �� 
					ResetBg();
				} else {
					ChangeBg(cl); 
				}
			}
			output << " "; // �����ʾɫ��Ŀո� 
		}
		// �����һ�к󣬻ָ��ն˵���ɫ�� 
		if (bg != black) {
			ResetBg();
		}
		output << "\n";
	}
}

void Write() {
	// ���ַ������Ϊת�����С�
	string str=output.str();
//	puts(str.c_str());
	for (int i=0;i<str.length();++i) {
		int ch=str[i];
//		if (ch == ESC) {
//			ch=27;
//		}
		printf("\\x%02X", ch);
	}
}

void Print(BitMap& b, int m, int n) {
	for (int i=0;i<m;++i) {
		for (int j=0;j<n;++j) {
			for (int k=0;k<3;++k) {
				printf("%d;", b[i][j].data[k]);
			}
			putchar(' ');
		}
		putchar('\n');
	}
}

int main(int argc, char** argv) {
	// ������������߾��������������˳���ǿ�ߡ� 
	scanf("%d%d%d%d",&N,&M,&Q,&P);
	Read();
//	puts("orig");
//	Print(origin, M, N);
	
	Pooling();
//	puts("now");
//	Print(now, P, Q);
	 
	Render();
	Write();
	
	return 0;
}
