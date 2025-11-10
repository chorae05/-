#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 10   // 최대 학생 수
#define LEN 128  // 문자열 최대 길이

// 학생 구조체 정의
typedef struct {
    char name[LEN];
    int atk, def, hp;
    char comment[LEN];  // 한줄소개
} Student;

// 문자열에서 특정 단어(oldWord)를 다른 단어(newWord)로 바꾸는 함수
void replaceWord(char* src, char* dest, const char* oldWord, const char* newWord) {
    char* start = src;      //원본문자열
    char* pos;              //찾은 단어의 시작 위치

    dest[0] = '\0'; // dest 비우기     //char* dest=결과 문자열

    // 문자열 내에서 oldWord를 반복해서 찾기
    while ((pos = strstr(start, oldWord)) != NULL) {
        strncat(dest, start, pos - start);  // oldWord 앞부분 복사
        strcat(dest, newWord);              // oldWord 대신 newWord 붙이기
        start = pos + strlen(oldWord);      // oldWord 다음 위치로 이동
    }
    strcat(dest, start);                    // 남은 부분 이어붙이기
}

int main(void) {
    

    errno_t err;

    Student stu[MAX];
    char line[LEN];
    int count = 0;

    char hakbun[20];
    char user_name[20];

    //학번과 이름 입력
    printf("학번을 입력하세요: ");
    scanf_s("%s", hakbun, (rsize_t)sizeof(hakbun));

    printf("이름을 입력하세요: ");
    scanf_s("%s", user_name, (rsize_t)sizeof(user_name));

    // students.csv 파일 열기 (읽기 모드)
    FILE* in = NULL;
    err = fopen_s(&in, "students.csv", "r");
    if (err != 0 || in == NULL) {
        printf("students.csv 파일 열기 실패!\n");
        return -1;
    }

    // 파일 한 줄씩 읽어서 구조체 배열에 저장
    while (fgets(line, sizeof(line), in) && count < MAX) {
        // 문자열 분리 (쉼표 기준)
        char* token = strtok(line, ",");
        strcpy(stu[count].name, token);

        token = strtok(NULL, ",");
        stu[count].atk = atoi(token);

        token = strtok(NULL, ",");
        stu[count].def = atoi(token);

        token = strtok(NULL, ",");
        stu[count].hp = atoi(token);

        token = strtok(NULL, ",");
        strcpy(stu[count].comment, token);

        count++;
    }
    fclose(in);


    FILE* out = NULL;
    //Test.txt 파일 열기 (쓰기 모드)
    err = fopen_s(&out, "Test.txt", "w");
    if (err != 0 || out == NULL) {
        printf("Test.txt 파일 열기 실패!\n");
        return -1;
    }

    // (1) 학번과 이름 출력
    fprintf(out, "%s : %s\n", hakbun, user_name);

    // (2) 가장 공격력이 높은 사람 찾기
    int maxAtk = stu[0].atk;
    int maxIdx = 0;
    for (int i = 1; i < count; i++) {
        if (stu[i].atk > maxAtk) {
            maxAtk = stu[i].atk;
            maxIdx = i;
        }
    }
    fprintf(out, "가장 공격력이 높은 사람: %s (ATK=%d)\n", stu[maxIdx].name, stu[maxIdx].atk);

    // (3) 3번째 사람 한줄소개 수정 (바보 → 천재)
    char result3[LEN * 2];
    replaceWord(stu[3].comment, result3, "바보", "천재구나");
    //replaceWord(원본, 결과, "찾을단어", "새단어");
    fprintf(out, "3번째의 한줄소개(수정됨): %s\n", result3);

    // (4) 8번째 사람 한줄소개 수정 (바보 → 천재)
    char result8[LEN * 2];
    replaceWord(stu[7].comment, result8, "바보", "천재");
    fprintf(out, "8번째의 한줄소개(수정됨): %s\n", result8);

    // (5) 전투 계산
    int i3 = 2, i8 = 7;
    int damage3 = stu[i8].atk - stu[i3].def;
    int damage8 = stu[i3].atk - stu[i8].def;

    if (damage3 < 0) damage3 = 0;
    if (damage8 < 0) damage8 = 0;

    int hp3 = stu[i3].hp - damage3;
    int hp8 = stu[i8].hp - damage8;

    if (damage3 == 0 && damage8 == 0)
        fprintf(out, "3번째 vs 8번째: 무승부\n");
    else if (hp3 <= 0 && hp8 <= 0)
        fprintf(out, "3번째 vs 8번째: 무승부\n");
    else if (hp3 > hp8)
        fprintf(out, "3번째 vs 8번째 승자: %s\n", stu[i3].name);
    else if (hp8 > hp3)
        fprintf(out, "3번째 vs 8번째 승자: %s\n", stu[i8].name);
    else
        fprintf(out, "3번째 vs 8번째: 무승부\n");

    // (6) 마지막 줄
    fprintf(out, "교수님 시험문제 너무 쉽습니다. 담주에 더 어렵게 내주세요\n");

    fclose(out);
    _getch();

    printf("8번째의 한줄소개(수정됨): %s\n", result8);
    printf("3번째의 한줄소개(수정됨): %s\n", result3);

    printf("Test.txt 파일 생성 완료!\n");

    return 0;
}





/*#define _CRT_SECURE_NO_WARNINGS  // Visual Studio에서 fgets, strcpy 등의 보안 경고를 무시하도록 설정
#include <stdio.h>               // printf, fgets 같은 입출력 함수 사용
#include <string.h>              // strcpy, strstr, strcat, strncat 등 문자열 함수 사용
#include <stdlib.h>              // NULL 같은 상수 사용

int main(void)
{
    char input[100];                                 // 사용자 입력을 저장할 배열 (문자열)
    fgets(input, sizeof(input), stdin);               // 한 줄 입력 받기 (공백 포함)

    char buf[128];                                   // 원본 문자열을 복사해서 가공할 버퍼
    strcpy(buf, input);                              // input 내용을 buf로 복사 (원본 보존)

    char out[128] = "";                              // 결과 문자열을 저장할 공간 (처음엔 빈 문자열)
    char* start = buf;                               // 문자열 탐색 시작 위치 (처음엔 문장의 맨 앞)

    // strstr로 "gay" 단어를 찾고, 없을 때(NULL)까지 반복
    for (char* q = strstr(start, "gay"); q != NULL; q = strstr(start, "gay"))
    {
        strncat(out, start, q - start);              // 'gay' 앞부분을 out에 복사 (q - start는 글자 개수)
        strcat(out, "***");                            // 'gay' 대신 '*' 한 글자 붙이기
        start = q + 3;                               // 'gay' (3글자) 건너뛰고 그 뒤부터 다시 탐색 시작
    }

    strcat(out, start);                              // 마지막 남은 부분(마지막 gay 뒤쪽)을 out에 이어붙이기

    printf("replace 'gay'->'*': \"%s\"\n", out);     // 결과 문자열 출력
    return 0;                                        // 프로그램 정상 종료
}
*/











/*#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>   // 오늘의 주인공
#include <stdlib.h>


int main(void)
{
    char input[100];
    fgets(input, sizeof(input), stdin); //stdin은 키보드로 입력받겠다는 뜻


    // 간단한 하이라이트: 'o'를 '*'로 모두 바꾸기(파괴적)
    char buf[128];  //수정본을 바꾸기 위해 변수를 만듦
    strcpy(buf, input);
    for (char* q = strstr(buf, "gay"); q != NULL; q = strstr(q + 1, "gay"))
    {
        strncpy(q, "****", 3);
    }
    printf("replace 'gay'->'*': \"%s\"\n", buf);


    return 0;
}
*/