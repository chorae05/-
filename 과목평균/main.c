#include <stdio.h>    // 표준 입출력 함수: printf, fprintf, fopen_s, fclose, fgets 등
#include <stdlib.h>   // atoi, atof, exit, malloc 등 변환 및 메모리 관련 함수
#include <string.h>   // 문자열 처리 함수: strcpy_s, strtok_s, strcmp 등
#include <locale.h>  // 헤더 추가

typedef struct {
	char name[64];
    int kor, eng, math;
    double avg;
}Student;

int main() {
   

	int count = 0;
	char line[128];
	Student s[10];
	errno_t err;

    FILE* fp1 = NULL;
    err = fopen_s(&fp1, "Korean.txt", "r");
    if (err != 0 || fp1 == NULL) {
        printf("Korean.txt 파일 열기 실패(쓰기): %s (errno=%d)\n", "Korean.txt", err);
        return -1;
    }
    printf("파일 열기 성공!!");

    // 첫 줄(헤더) 건너뛰기
    fgets(line, sizeof(line), fp1);

    while (fgets(line, sizeof(line), fp1)) {

        line[strcspn(line, "\r\n")] = 0; // 줄 끝 개행 제거

        char* t, * n;


        t = strtok_s(line, ",", &n);
        strcpy_s(s[count].name, sizeof(s[count].name), t);


        t = strtok_s(NULL, ",", &n);
        s[count].kor = atoi(t);

        count++;
    }
    fclose(fp1);
	//-----------------------------------------------------------

    FILE* fp2 = NULL;
    err = fopen_s(&fp2, "English.txt", "r");
    if (err != 0 || fp2 == NULL) {
        printf("English 파일 열기 실패(쓰기): %s (errno=%d)\n", "English.txt", err);
        return -1;
    }
    printf("파일 열기 성공!!");

    int count22 = 0;

    while (fgets(line, sizeof(line), fp2)) {

        line[strcspn(line, "\r\n")] = 0; // 줄 끝 개행 제거


        char* t, * n;

        t = strtok_s(line, ",", &n);
        strcpy_s(s[count22].name, sizeof(s[count22].name), t);


        t = strtok_s(NULL, ",", &n);
        s[count22].eng = atoi(t);

        count22++;
    }
    fclose(fp2);
	//-----------------------------------------------------------
	
    FILE* fp3 = NULL;
    err = fopen_s(&fp3, "math.txt", "r");
    if (err != 0 || fp3 == NULL) {
        printf("math.txt 파일 열기 실패(쓰기): %s (errno=%d)\n", "math.txt", err);
        return -1;
    }
    printf("파일 열기 성공!!");

    int count33 = 0;

    while (fgets(line, sizeof(line), fp3)) {

        line[strcspn(line, "\r\n")] = 0; // 줄 끝 개행 제거


        char* t, * n;

        t = strtok_s(line, ",", &n);
        strcpy_s(s[count33].name, sizeof(s[count33].name), t);


        t = strtok_s(NULL, ",", &n);
        s[count33].math = atoi(t);

        count33++;
    }
    fclose(fp3);
    //평균내는 법
    for (int i = 0; i < count; i++) {
        s[i].avg = (s[i].kor + s[i].eng + s[i].math) / 3.0;
    }
    //TotalResult.txt에 이름, 세 과목 점수, 평균 출력

    //마지막에 “가장 평균 높은 학생” + 교수님 멘트까지 작성

    FILE* out = NULL;
    err = fopen_s(&out, "TotalResult.txt", "w");
    if (err != 0 || out == NULL) {
        printf("파일을 열 수 없습니다!\n");
        return -1;
    }

    fprintf(out, "이름,국어,영어,수학,평균\n");

    for (int i = 0; i < count; i++)
    {
        fprintf(out,"%s,%d,%d,%d,%.1lf\n",
            s[i].name,
            s[i].kor,
            s[i].eng,
            s[i].math,
            s[i].avg);
    }

     int hight_avg = 0;
    for (int i = 1; i < count; i++) {
        if (s[i].avg > s[hight_avg].avg)
            hight_avg = i;
    }
    fprintf(out, "가장 평균 높은 학생:%s (평균: %.3lf)\n", s[hight_avg].name, s[hight_avg].avg);
    fprintf(out, "교수님 문제가 너무 쉽습니다.\n");
    fclose(out);
    _getch();
    Sleep(100);
	printf("\n평균 가장 높은 학생->\n이름: %s\n평균 :%.3lf\n", s[hight_avg].name, s[hight_avg].avg);
    


	return 0;

}