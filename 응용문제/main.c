#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

typedef struct {
	char name[234];
	int atk, def, hp;
}Students;

int main() {
	Students groupA[10];
    Students groupB[10];
	char line[100];
	int count = 0;
	char hakbun[20];
	char user_name[20];
	errno_t err;

	printf("학번을 입력하세요: ");
	scanf_s("%s", hakbun, (rsize_t)sizeof(hakbun));

	printf("이름을 입력하세요: ");
	scanf_s("%s", user_name, (rsize_t)sizeof(user_name));

    FILE* fp1 = NULL;
    err = fopen_s(&fp1, "groupA.csv", "r");
    if (err != 0 || fp1 == NULL) {
        printf("groupA.csv 파일 열기 실패(쓰기): %s (errno=%d)\n", "groupA.csv", err);
        return -1;
    }
    printf("파일 열기 성공!!\n");

    while (fgets(line, sizeof(line), fp1) && count < 10) {

        char* t, * n;

        t = strtok_s(line, ",", &n);
        strcpy_s(groupA[count].name, sizeof(groupA[count].name), t);


        t = strtok_s(NULL, ",", &n);
        groupA[count].atk = atoi(t);


        t = strtok_s(NULL, ",", &n);
        groupA[count].def = atoi(t);


        t = strtok_s(NULL, ",", &n);
        groupA[count].hp = atoi(t);

        count++;
    }
    fclose(fp1);

    //각 그룹의 평균 공격력과 평균 방어력을 계산하여 콘솔에 출력한다.

    int total_atk = 0;
    int total_def = 0;

    for (int i = 0; i < count; i++) {
        total_atk = total_atk + groupA[i].atk;
        total_def = total_def + groupA[i].def;
    }
    double avg_atk = total_atk / 5.0;
    double avg_def = total_def / 5.0;

    printf("\ngroup A 그룹 평균 ATK: %.2lf\ngroup A 그룹 평균 DEF: %.2lf\n", avg_atk, avg_def);

    int top_atk=0;
    for (int i = 0; i < count; i++) {
        if (groupA[i].atk > groupA[top_atk].atk)
            top_atk = i;
    }
        


    int count22 = 0;

    FILE* fp2 = NULL;
    err = fopen_s(&fp2, "groupB.csv", "r");
    if (err != 0 || fp2 == NULL) {
        printf("groupB.csv 파일 열기 실패(쓰기): %s (errno=%d)\n", "groupB.csv", err);
        return -1;
    }
    printf("파일 열기 성공!!\n");

    while (fgets(line, sizeof(line), fp2) && count22 < 10) {

        char* t, * n;

        t = strtok_s(line, ",", &n);
        strcpy_s(groupB[count22].name, sizeof(groupB[count22].name), t);


        t = strtok_s(NULL, ",", &n);
        groupB[count22].atk = atoi(t);


        t = strtok_s(NULL, ",", &n);
        groupB[count22].def = atoi(t);


        t = strtok_s(NULL, ",", &n);
        groupB[count22].hp = atoi(t);

        count22++;
    }
    fclose(fp2);

    int total_atk_B = 0;
    int total_def_B = 0;

    for (int i = 0; i < count22; i++) {
        total_atk_B = total_atk_B + groupB[i].atk;
        total_def_B = total_def_B + groupB[i].def;
    }
    double avg_atk_B = total_atk_B / (double)count22;
    double avg_def_B = total_def_B / (double)count22;

    printf("\ngroup B 그룹 평균 ATK: %.2lf\n", avg_atk_B);
    printf("group B 그룹 평균 DEF: %.2lf\n", avg_def_B);

    int top_def=0;
    for (int i = 0; i < count22; i++) {
        if (groupB[i].def > groupB[top_def].def)
            top_def = i;
    }

    FILE* file = NULL;
    err = fopen_s(&file, "Result.txt", "w");
    if (err != 0 || file == NULL) {
        printf("파일을 열 수 없습니다!\n");
        return -1;
    }

    fprintf(file, "%s:%s\n", hakbun, user_name );
    fprintf(file, "\ngroupA 대표: %s (ATK=%d, DEF=%d, HP=%d)\n", groupA[top_atk].name, groupA[top_atk].atk, groupA[top_atk].def, groupA[top_atk].hp);
    fprintf(file, "groupB 대표: %s (ATK=%d, DEF=%d, HP=%d)\n", groupB[top_def].name, groupB[top_def].atk, groupB[top_def].def, groupB[top_def].hp);
    if (groupA[top_atk].atk > groupB[top_def].def) {
        fprintf(file, "승자: %s\n", groupA[top_atk].name);
    }
    else if (groupA[top_atk].atk < groupB[top_def].def) {
        fprintf(file, "승자: %s\n", groupB[top_def].name);
    }
    else fprintf(file, "무승부\n");
    fclose(file);

}        

