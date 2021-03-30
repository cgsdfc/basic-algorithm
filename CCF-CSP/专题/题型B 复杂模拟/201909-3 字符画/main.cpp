#include <iostream>
#include <sstream>
#include <cstdio>
#include <cstring>
#include <cassert>
using namespace std;

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int M, N; // 行数，列数 
int P, Q; // 小块的行数，列数。 

// 先输出为字符串，再转化为转义序列。 
ostringstream output;

struct Color {
	int data[3];
	Color(){
		// 默认是黑色，即全零。 
		memset(data, 0, sizeof(data));
	}
	
	friend bool operator==(const Color& a, const Color& b) {
		return 0==memcmp(a.data, b.data, sizeof(a.data));
	}
	friend bool operator!=(const Color& a, const Color& b) {
		return !(a==b);
	}
};

const Color black; // 默认值

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

Color bg; // 当前背景色。
 
// 改变背景色。 
void ChangeBg(Color& cl) {
	bg=cl;
	output<<ESC<<"[48;2";
	for (int i=0;i<3;++i) {
		output<<";"<<cl.data[i];
	}
	output<<"m";
}

// 重置背景色。 
void ResetBg() {
	bg=black;
	output<<ESC<<"[0m";
}

#define MAXS 10

void Read() {
	// 把原始像素输入。
	for (int i=0;i<M;++i) {
		for (int j=0;j<N;++j) {
			char buf[MAXS];
			scanf("%s",buf);
			Color& cl=origin[i][j];
			Parse(buf, strlen(buf), cl);
		}
	}
}

// 以i，j为左上角元素的，P Q为宽高的小图片的平均值。 
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
		ans.data[k] /= P*Q; // 小图片共有这么多个像素。 
	}
	return ans;
}

// 计算所有色块。 即求出原始位图的分块的平均值，按照它们原始的位置放入新的位图。 
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
	bg=black; // 背景为黑色。

	// 把池化后的图片输出为转义序列、空格和回车。
	for (int i=0;i<M/P;++i) {
		for (int j=0;j<N/Q;++j) {
			Color& cl=now[i][j];
			if (cl != bg) {
				// 当前颜色没有变化时，不要输出任何转义序列。
				if (cl == black) {
					// 如果与默认值完全相同 。 
					ResetBg();
				} else {
					ChangeBg(cl); 
				}
			}
			output << " "; // 输出表示色块的空格。 
		}
		// 输出完一行后，恢复终端的颜色。 
		if (bg != black) {
			ResetBg();
		}
		output << "\n";
	}
}

void Write() {
	// 把字符串输出为转义序列。
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
	// 宽就是列数，高就是行数，输入的顺序是宽高。 
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
