#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

typedef struct Record {
	char name[12];
	char id[12];
	int grade;
} Record;

int CMP(const void*_a, const void*_b) {
	Record* a=(Record*)_a, *b=(Record*)_b;
	return b->grade-a->grade;
}

int main(int argc, char *argv[]) {
	Record* rec;
	Record* valid;
	int num;
	int N;
	int g1,g2;
	int i;
	
	scanf("%d",&N);
	rec=(Record*)malloc(sizeof(Record)*N);
	valid=(Record*)malloc(sizeof(Record)*N);
	num=0;
	
	for (i=0;i<N;++i) {
		scanf("%s%s%d",rec[i].name,rec[i].id,&rec[i].grade);
	}
	scanf("%d%d",&g1,&g2);
	
	for (i=0;i<N;++i) {
		if (g1<=rec[i].grade&&rec[i].grade<=g2) {
			valid[num++]=rec[i];
		}
	}
	
	qsort(valid, num, sizeof(Record), CMP);
	for (i=0;i<num;++i) {
		printf("%s %s\n", valid[i].name,valid[i].id);
	}
	if (!num) {
		puts("NONE");
	}
	free(rec);
	free(valid);
	
	return 0;
}
