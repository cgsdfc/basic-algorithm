#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

/*
gets, puts, fgets, fputs ����Ϊ��

gets��puts��һ�ԣ�gets�����ʱ�Զ���ӻ��У�puts������ʱ�Զ�ɾ������ ��
fgets��fputs��һ�ԣ����ǶԻ���ʱԭ����������룬��fputs�����Զ���ӻ��У�
fgetsҲ����Ե�����Ļ��С� 
*/

int main(int argc, char *argv[]) {
	char str[] = "Hello World";
	puts(str);
	puts(str);
	printf("\n");
	fputs(str, stdout);
	fputs(str, stdout);
	
//	gets, fgets ����Ϊ���ơ� 
	return 0;
}
