#define _CRT_SECURE_NO_WARNINGS  // Visual Studio에서 fgets, strcpy 등의 보안 경고를 무시하도록 설정
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