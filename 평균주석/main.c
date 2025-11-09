#include <stdio.h>   // printf, fprintf, fopen_s, fclose, fgets 같은 입출력 함수 사용
#include <stdlib.h>  // atoi (문자열→숫자 변환), exit 등 함수 사용
#include <string.h>  // strcpy_s, strtok_s (문자열 자르기 함수 등) 사용

// ----------------------------
// 구조체 정의: 한 명의 학생을 표현
// ----------------------------
typedef struct {
    char name[20];  // 이름
    int kor;        // 국어 점수
    int eng;        // 영어 점수
    int math;       // 수학 점수
    double avg;     // 평균 점수
} Student;

// ----------------------------
// 메인 함수 시작
// ----------------------------
int main(void)
{
    Student s[10];       // 학생 정보 최대 10명 저장할 수 있는 배열
    char line[128];      // 파일에서 한 줄을 읽어올 공간
    int count = 0;       // 학생 수를 셀 변수
    errno_t err;         // 파일 열기 결과 확인용 변수 (fopen_s용)

    // ==========================================================
    //  Korean.txt (국어 점수 파일) 읽기
    // ==========================================================
    FILE* fp1 = NULL;  // 파일 포인터 (파일의 위치를 가리킴)
    err = fopen_s(&fp1, "Korean.txt", "r");  // "r" = 읽기 모드로 열기

    if (err != 0 || fp1 == NULL) {           // 파일이 없거나 열기 실패 시
        printf("Korean.txt 파일 열기 실패!\n");
        return -1;                           // 프로그램 강제 종료
    }

    // 한 줄씩 파일을 읽어온다 (예: "홍길동,85\n")
    while (fgets(line, sizeof(line), fp1) && count < 10) {
        char* t;    // 잘라낸 문자열을 잠시 저장할 포인터
        char* n;    // 남은 문자열 위치를 기억할 포인터 (strtok_s용)

        //  이름 자르기
        t = strtok_s(line, ",", &n);                         // 콤마(,) 기준으로 첫 번째 단어 자름
        strcpy_s(s[count].name, sizeof(s[count].name), t);   // 이름을 구조체에 복사

        //  점수 자르기
        t = strtok_s(NULL, ",", &n); // 다음 콤마 뒤의 값 (점수 부분)
        s[count].kor = atoi(t);      // 문자열을 숫자로 바꿔 저장 (ex. "85" → 85)

        count++;  // 학생 한 명 완성 → 학생 수 1 증가
    }
    fclose(fp1);  // 파일 닫기 (중요! 닫지 않으면 저장 안 되거나 오류 발생)

    // ==========================================================
    //  English.txt (영어 점수 파일) 읽기
    // ==========================================================
    FILE* fp2 = NULL;
    err = fopen_s(&fp2, "English.txt", "r"); // 영어 점수 파일 열기
    if (err != 0 || fp2 == NULL) {
        printf("English.txt 파일 열기 실패!\n");
        return -1;
    }

    int idx2 = 0;  // 영어 점수를 저장할 때 사용할 인덱스
    while (fgets(line, sizeof(line), fp2) && idx2 < count) {
        char* t, * n;

        // 이름은 파일에 있지만 이미 알고 있으니 생략
        t = strtok_s(line, ",", &n);  // 이름 건너뛰기

        // 영어 점수 읽기
        t = strtok_s(NULL, ",", &n);
        s[idx2].eng = atoi(t);  // 문자열 → 숫자 변환

        idx2++;
    }
    fclose(fp2); // 영어 파일 닫기

    // ==========================================================
    //  Math.txt (수학 점수 파일) 읽기
    // =========================================================
    FILE* fp3 = NULL;
    err = fopen_s(&fp3, "Math.txt", "r");
    if (err != 0 || fp3 == NULL) {
        printf("Math.txt 파일 열기 실패!\n");
        return -1;
    }

    int idx3 = 0;  // 수학 점수 저장용 인덱스
    while (fgets(line, sizeof(line), fp3) && idx3 < count) {
        char* t, * n;

        // 이름 건너뛰기
        t = strtok_s(line, ",", &n);

        // 수학 점수 읽기
        t = strtok_s(NULL, ",", &n);
        s[idx3].math = atoi(t);

        idx3++;
    }
    fclose(fp3); // 수학 파일 닫기

    // ==========================================================
    //  평균 계산
    // ==========================================================
    for (int i = 0; i < count; i++) {
        s[i].avg = (s[i].kor + s[i].eng + s[i].math) / 3.0; // 세 과목 평균
    }

    // ==========================================================
    //  평균이 가장 높은 학생 찾기
    // ==========================================================
    int top = 0;  // 첫 번째 학생을 기준으로 시작
    for (int i = 1; i < count; i++) {
        if (s[i].avg > s[top].avg)  // 더 높은 평균이 있으면 갱신
            top = i;
    }

    // ==========================================================
    //  결과 파일에 출력 (TotalResult.txt)
    // ==========================================================
    FILE* fout = NULL;
    err = fopen_s(&fout, "TotalResult.txt", "w"); // "w" = 쓰기 모드
    if (err != 0 || fout == NULL) {
        printf("TotalResult.txt 파일 열기 실패!\n");
        return -1;
    }

    // 파일 상단에 제목 쓰기
    fprintf(fout, "이름,국어,영어,수학,평균\n");

    // 각 학생의 점수 기록
    for (int i = 0; i < count; i++) {
        fprintf(fout, "%s,%d,%d,%d,%.1lf\n",
            s[i].name, s[i].kor, s[i].eng, s[i].math, s[i].avg);
    }

    // 평균 1등 학생 출력
    fprintf(fout, "\n가장 평균이 높은 학생: %s (%.1lf점)\n", s[top].name, s[top].avg);

    // 마지막 문장 (교수님 스타일)
    fprintf(fout, "교수님 시험문제 너무 쉽습니다. 담주엔 더 어렵게 내주세요.\n");

    fclose(fout); // 결과 파일 닫기

    printf(" 결과 파일(TotalResult.txt) 저장 완료!\n");
    return 0;
}
