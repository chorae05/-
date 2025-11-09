#include <stdio.h>  
#include <stdlib.h>
#include <string.h>
#include <conio.h>

typedef struct {
	char name[20];
	int atk, def, HP;
}Student;

int main() {
    Student student[10];
    int id;
    char user_name[20];
    char line[100];
    int count = 0;
    errno_t err;

    printf("학번: ");
    scanf_s("%d", &id);

    printf("이름: ");
    scanf_s("%s", user_name, (rsize_t)sizeof(user_name));

    //파일 열기
    FILE* fp1 = NULL;
    err = fopen_s(&fp1, "students.csv", "r");
    if (err != 0 || fp1 == NULL) {
        printf("students.csv 파일 열기 실패(쓰기): %s (errno=%d)\n", "students.csv", err);
        return -1;
    }
    printf("파일 열기 성공!!");

    while (fgets(line, sizeof(line), fp1) && count < 10) {

        char* t, * n;

        t = strtok_s(line, ",", &n);
        strcpy_s(student[count].name, sizeof(student[count].name), t);


        t = strtok_s(NULL, ",", &n);
       student[count].atk = atoi(t);


        t = strtok_s(NULL, ",", &n);
        student[count].def = atoi(t);


        t = strtok_s(NULL, ",", &n);
        student[count].HP = atoi(t);

        count++;
    }
    fclose(fp1);


    //test.txt 파일에 쓰기
    FILE* fp2 = NULL;
    err = fopen_s(&fp2, "Test.txt", "w");
    if (err != 0 || fp2 == NULL) {
        printf(" test. txt 파일 열기 실패(쓰기): %s (errno=%d)\n", "Test.txt", err);
        return 1;
    }
    printf("테스트 파일 열기 성공");

    int fightmax = 0;
    for (int i = 0; i < count; i++) {
        if (student[i].atk > student[fightmax].atk)
            fightmax = i;
    }
    fprintf(fp2, "%d : %s\n", id, user_name);
    fprintf(fp2, "가장 공격력이 높은 사람: %s (ATK=%d)\n", student[fightmax].name, student[fightmax].atk);
    fprintf(fp2, "3번째: %s HP=%d\n", student[3].name, student[3].HP);
    fprintf(fp2, "8번째: %s HP=%d\n", student[8].name, student[8].HP);
    if (student[3].atk > student[8].atk) {
        fprintf(fp2, "3번째 vs 8번째 승자: %s\n", student[3].name);
    }
    else if (student[3].atk < student[8].atk) {
        fprintf(fp2, "3번째 vs 8번째 승자: %s\n", student[8].name);
    }
    else fprintf(fp2, "3번째 vs 8번째 승자: 무승부\n");

    fprintf(fp2, "교수님 시험문제 너무 쉽습니다. 담주에 더 어렵게 내주세요\n");

    fclose(fp2);

    return 0;
}

