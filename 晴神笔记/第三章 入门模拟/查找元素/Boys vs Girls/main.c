#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch,
 * system("pause") or input loop */

#define MAXS 15

typedef struct Stu {
    char name[MAXS];
    char sex;
    char id[MAXS];
    int grade;
} Stu;

typedef struct Info {
    int num;
    int gr;
    Stu stu;
} Info;

Info M = {0, 101, {}};
Info F = {0, -1, {}};

void Print(Info* i) {
    if (i->num) {
        printf("%s %s\n", i->stu.name, i->stu.id);
    } else {
        printf("Absent\n");
    }
}

int main(int argc, char* argv[]) {
    int n;

    //	freopen("./in.txt", "r", stdin);

    scanf("%d", &n);

    while (n--) {
        Stu stu;

        scanf("%s %c %s %d", stu.name, &stu.sex, stu.id, &stu.grade);
        //		printf("%c\n", stu.sex);

        if (stu.sex == 'M') {
            ++M.num;
            if (stu.grade < M.gr) {
                M.gr = stu.grade;
                M.stu = stu;
            }
        } else if (stu.sex == 'F') {
            ++F.num;
            if (stu.grade > F.gr) {
                F.gr = stu.grade;
                F.stu = stu;
            }
        }
    }
    Print(&F);
    Print(&M);
    if (F.num && M.num) {
        printf("%d\n", F.gr - M.gr);
    } else {
        printf("NA\n");
    }

    return 0;
}
