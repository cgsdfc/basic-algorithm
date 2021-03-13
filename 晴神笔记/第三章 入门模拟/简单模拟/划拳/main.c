#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]) {
	int a1, a2, b1, b2;
	int n;
	int fail1, fail2;
	
	fail1=fail2=0;
	scanf("%d",&n);
	while (n--) {
		int sum;
		// ¼×º° ¼×»® ÒÒº° ÒÒ»® 
		scanf("%d%d%d%d", &a1,&a2,&b1,&b2);
		sum=a1+b1; // ¼×º°¼ÓÒÒº°
		if (a2 == sum && b2 != sum) {
			// ¼×Ó®
			fail2++; 
		} else if (a2 != sum && b2 == sum) {
			// ÒÒÓ®
			++fail1; 
		}
	}
	printf("%d %d\n", fail1, fail2);
	
	return 0;
}
