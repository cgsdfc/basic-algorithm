#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int N, C;

#define MAXN 100005

typedef struct Student {
	int id;
	char name[10];
	int grade;
} Student;

Student data[MAXN];

int CMP(const void* _a, const void* _b) {
	Student* a=(Student*)_a;
	Student* b=(Student*)_b;
	int cmp;
	
	switch (C) {
		case 1:
			return a->id-b->id;
		case 2:
			cmp=strcmp(a->name, b->name);
			if (cmp) return cmp;
			return a->id-b->id;
		case 3:
			cmp=a->grade-b->grade;
			if (cmp) return cmp;
			return a->id-b->id;
		default:
			return 999;
	}
}

int main(int argc, char *argv[]) {
	int i;
	
	scanf("%d%d",&N,&C);
	for (i=0;i<N;++i) {
		scanf("%d%s%d",&data[i].id,&data[i].name,&data[i].grade);
	}
	qsort(data, N, sizeof(Student), CMP);
	for (i=0;i<N;++i) {
		printf("%06d %s %d\n", data[i].id,data[i].name,data[i].grade);
	}
	return 0;
}
