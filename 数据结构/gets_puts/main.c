#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

/*
gets, puts, fgets, fputs 的行为。

gets，puts是一对，gets在输出时自动添加换行，puts在输入时自动删除换行 。
fgets，fputs是一对，他们对换行时原样输出和输入，即fputs不会自动添加换行，
fgets也不会吃掉输入的换行。 
*/

int main(int argc, char *argv[]) {
	char str[] = "Hello World";
	puts(str);
	puts(str);
	printf("\n");
	fputs(str, stdout);
	fputs(str, stdout);
	
//	gets, fgets 的行为类似。 
	return 0;
}
