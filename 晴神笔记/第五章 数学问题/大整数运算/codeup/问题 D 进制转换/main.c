#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

#define MAXN 100

typedef struct Big {
	int d[MAXN];
	int len;
} Big;

// 输入字母为大写。 
int FromChar(char c) {
	if ('0'<=c&&c<='9') return c-'0';
	if ('A'<=c&&c<='Z') return c-'A'+10;
	return -1;
}

// 输出字母为小写。 
char ToChar(int d) {
	if (0<=d&&d<=9) return '0'+d;
	if (10<=d&&d<=35) return 'a'+d-10;
	return '*';
}

Big Mult(Big a, int b) {
	Big c={};
	int carry=0;
	int i;
	for (i=0;i<a.len;++i) {
		int temp=carry+a.d[i]*b;
		c.d[c.len++]=temp%10;
		carry=temp/10;
	}
	while (carry) {
		c.d[c.len++]=carry%10;
		carry /= 10;
	}
	return c;
}

Big Add(Big a, int b) {
	int i;
	int carry;
	Big c={};
	
	carry=b;
	for (i=0;i<a.len;++i) {
		int temp=a.d[i]+carry;
		c.d[c.len++]=temp%10;
		carry=temp/10;
	}
	if (carry) {
		c.d[c.len++]=carry;
	}
	return c;
}

Big To(char str[], int len, int radix) {
	Big ans={};
	int i;
	
	// ans=a0;
	ans.d[0]=FromChar(str[0]);
	ans.len=1;
	for (i=1;i<len;++i) {
		int d=FromChar(str[i]);
		// ans=ans*radix+ai;
		ans=Add(Mult(ans, radix), d);
	}
	return ans;
}

Big Div(Big a, int b, int* rem) {
	Big c={};
	int i;
	int r=0;
	
	c.len=a.len;
	for (i=a.len-1;i>=0;--i) {
		r=r*10+a.d[i];
		if (r < b) {
			c.d[i]=0;
		} else {
			c.d[i]=r/b;
			r%=b;
		}
	}
	while (c.len-1>=1 && c.d[c.len-1]==0) {
		--c.len;
	}
	*rem=r;
	return c;
}

int From(Big a, char str[], int radix) {
	int len=0;
	
	while (!(a.len==1&&a.d[0]==0)) { // while (a)
		int r;
		// d=a%radix; a/=radix;
		a=Div(a, radix, &r);
		str[len++]=ToChar(r);
	}
	str[len]=0;
	return len;
}

void Print(Big c) {
	int i;
	for (i=c.len-1;i>=0;--i) {
		printf("%d", c.d[i]);
	}
	printf("\n");
}

/*
注意把乘法，加法，除法写熟练。
加法是高精度加低精度，注意这是课本没有的，令carry=b即可。
*/
 
int main(int argc, char *argv[]) {
	int M,N;
	char str[MAXN];
	
	while (scanf("%d%d%s", &M, &N, str) != EOF) {
		Big a={};
		int len;
		int i;
		
//		printf("M %d N %d str %s\n", M, N, str);
		
		a=To(str, strlen(str), M);
//		printf("a ");
//		Print(a);
		 
		len=From(a, str, N);
		for (i=len-1;i>=0;--i) {
			printf("%c", str[i]);
		}
		printf("\n");
	}
	
	return 0;
}
