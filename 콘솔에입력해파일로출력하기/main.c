#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>


typedef struct {
    char name[64];
    int kor, eng, math;
    double avg;
} Student;

#define MAX 128

int main() {
    int count = 0;
    char line[100];
    Student s[MAX];
    errno_t err;

    printf("학생 수를 입력하시오: ");
    scanf_s("%d", &count);

    for (int i = 0; i < count; i++) {
        printf("지금 현재 %d번째 학생입니다.\n",i+1);
        
        printf("이름: ");
        scanf_s("%s", s[i].name, (rsize_t)sizeof(s[i].name));

        printf("국어: ");
        scanf_s("%d", &s[i].kor);

        printf("영어: ");
        scanf_s("%d", &s[i].eng);

        printf("수학: ");
        scanf_s("%d", &s[i].math);

        s[i].avg = (s[i].kor + s[i].eng + s[i].math) / 3.0;
        printf("\n%d번째 학생의 평균은 %.2lf점입니다.\n", i+1, s[i].avg);
    }

    int top = 0;
    for (int i = 0; i < count; i++)
        if (s[i].avg > s[top].avg) {
            top = i;
        }
        

    FILE* in = NULL;
    err = fopen_s(&in, "result.txt", "w");
    if (err != 0 || in == NULL) {
        printf("result.txt 파일을 열 수 없습니다!\n");
        return -1;
    }

    fprintf(in, "이름, 국어, 영어, 수학, 평균\n");

    for (int i = 0; i < count; i++)
    {
        fprintf(in, "%s,%d,%d,%d,%.2lf\n",
            s[i].name,
            s[i].kor,
            s[i].eng,
            s[i].math,
            s[i].avg);
    }


    fprintf(in, "가장평균이 높은 학생 : %s(평균 : %.2lf)", s[top].name, s[top].avg);

    fclose(in);
    _getch();

    FILE* fp = NULL;
    fopen_s(&fp, "result.txt", "r");

    if (!fp) {
        printf("result.txt 파일을 열 수 없습니다!\n");
        return -1;
    }

    int loadcount = 0;
    fgets(line, sizeof(line), fp);

    while (fgets(line, sizeof(line), fp)) {


        char* t, * n;


        t = strtok_s(line, ",", &n);
        strcpy_s(s[loadcount].name, sizeof(s[loadcount].name), t);


        t = strtok_s(NULL, ",", &n);
        s[loadcount].kor = atoi(t);


        t = strtok_s(NULL, ",", &n);
        s[loadcount].eng = atoi(t);


        t = strtok_s(NULL, ",", &n);
        s[loadcount].math = atoi(t);

        
        t = strtok_s(NULL, ",", &n);
        s[loadcount].avg = atof(t);


        loadcount++;
    }
    printf("이름, 국어, 영어, 수학, 평균");
    printf("\n------------------------------------------------------\n");
    for (int i = 0; i < loadcount; i++) {
        printf("%s,  %d,  %d,  %d,  %.2lf\n",
            s[i].name, s[i].kor, s[i].eng, s[i].math, s[i].avg);
    }
    printf("------------------------------------------------------");



    fclose(fp);


      
    return 0;
}