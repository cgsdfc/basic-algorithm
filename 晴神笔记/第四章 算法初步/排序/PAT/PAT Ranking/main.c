#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

/*
Input Specification:
Each input file contains one test case. For each case, 
the first line contains a positive number N (≤100), 
the number of test locations. Then N ranklists follow,
 each starts with a line containing a positive integer K (≤300), 
 the number of testees, and then K lines containing the registration number
  (a 13-digit number) and the total score of each testee. All the numbers in a line are separated by a space.

Output Specification:
For each test case, first print in one line the total number of testees.
 Then print the final ranklist in the following format:

registration_number final_rank location_number local_rank
The locations are numbered from 1 to N. The output must be sorted in nondecreasing order of the final ranks.
 The testees with the same score must have the same rank,
  and the output must be sorted in nondecreasing order of their registration numbers.
*/

typedef struct Student {
	char id[15];
	int score;
	int final_rank;
	int loc;
	int local_rank;
} Student;

#define MAXN 30010

Student stu[MAXN];
int N;

int CMP(const void* _a, const void* _b) {
	Student* a=(Student*)_a;
	Student* b=(Student*)_b;
	if (a->score != b->score) {
		return b->score - a->score;
	}
	return strcmp(a->id, b->id);
}

int main(int argc, char *argv[]) {
	int n;
	int i;
	int r;
	
	scanf("%d",&n);
	for (i=0;i<n;++i) {
		int k;
		int j;
		int r;
		Student* base;
		
		/*
		输入本考场的信息。记录基本信息。
		*/ 
		scanf("%d",&k);
		for (j=0;j<k;++j) {
			scanf("%s%d", stu[N].id, &stu[N].score);
			stu[N].loc=i+1;
			++N;
		}
		base=stu+N-k;
		qsort(base, k, sizeof(Student), CMP);
		
		/*
		计算local rank。
		*/ 
		r=1;
		for (j=0;j<k;++j) {
			if (j > 0 && base[j].score != base[j-1].score) {
				r=j+1;
			}
			base[j].local_rank=r;
		}
	}
	
	/*
	所有考生录入完毕，开始计算final rank。
	*/
	printf("%d\n",N);
	qsort(stu, N, sizeof(Student), CMP);
	r=1;
	for (i=0;i<N;++i) {
		if (i > 0 && stu[i].score != stu[i-1].score) {
			r=i+1;
		}
		stu[i].final_rank=r;
		// registration_number final_rank location_number local_rank
		printf("%s %d %d %d\n", stu[i].id, stu[i].final_rank, stu[i].loc, stu[i].local_rank);
	}
	
	return 0;
}

/*
2
5
1234567890001 95
1234567890005 100
1234567890003 95
1234567890002 77
1234567890004 85
4
1234567890013 65
1234567890011 25
1234567890014 100
1234567890012 85
*/

