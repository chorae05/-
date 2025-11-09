#include <stdio.h>    // 표준 입출력 함수: printf, fprintf, fopen_s, fclose, fgets 등
#include <stdlib.h>   // atoi, atof, exit, malloc 등 변환 및 메모리 관련 함수
#include <string.h>   // 문자열 처리 함수: strcpy_s, strtok_s, strcmp 등

typedef struct {
	char name[20];
	int kor, eng, math, avg;
}Student;

int main() {
    Student student[3];
    char line[128];
    int count = 0;
    errno_t err;

    FILE* fp1 = NULL;
    err = fopen_s(&fp1, "Korean.txt", "r");
    if (err != 0 || fp1 == NULL) {
        printf("students.csv 파일 열기 실패(쓰기): %s (errno=%d)\n", "students.csv", err);
        return -1;
    }
    printf("파일 열기 성공!!");

    while (fgets(line, sizeof(line), fp1) && count < 3) {

        char* t, * n;

        t = strtok_s(line, ",", &n);
        strcpy_s(student[count].name, sizeof(student[count].name), t);

        t = strtok_s(NULL, ",", &n);
        student[count].kor = atoi(t);

        count++;
    }
    fclose(fp1);

    FILE* fp2 = NULL;
    err = fopen_s(&fp2, "English.txt", "r");
    if (err != 0 || fp2 == NULL) {
        printf("students.csv 파일 열기 실패(쓰기): %s (errno=%d)\n", "students.csv", err);
        return -1;
    }
    printf("파일 열기 성공!!");

    char name [20];
    int score;

    while (fgets(line, sizeof(line), fp2) && score < 3) {

        char* t, * n;

        t = strtok_s(line, ",", &n);
        strcpy_s(student[score].name, sizeof(student[score].name), t);

        t = strtok_s(NULL, ",", &n);
        student[score].eng = atoi(t);

        score++;
    }
    fclose(fp2);

    FILE* fp3 = NULL;
    err = fopen_s(&fp3, "English.txt", "r");
    if (err != 0 || fp3 == NULL) {
        printf("students.csv 파일 열기 실패(쓰기): %s (errno=%d)\n", "students.csv", err);
        return -1;
    }
    printf("파일 열기 성공!!");

    char name1[20];
    int score1;

    while (fgets(line, sizeof(line), fp3) && score < 3) {

        char* t, * n;

        t = strtok_s(line, ",", &n);
        strcpy_s(student[score1].name, sizeof(student[score1].name), t);

        t = strtok_s(NULL, ",", &n);
        student[score1].math = atoi(t);

        score1++;
    }
    fclose(fp3);

    for (int i = 0; i < count; i++) {
        student[i].avg = (student[i].kor + student[i].eng + student[i].math) / 3.0;
    }



}
