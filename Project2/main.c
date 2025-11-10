#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct {
	char name[64];
	int atk, def, hp;
	char comment[100];
}Student;

void replaceWord(const char* src, char* dest, const char* oldWord, const char* newWord) {
	if (!src || !dest || !oldWord || !newWord) return; // 안전 검사

	const char* pos = src;
	const char* match;
	dest[0] = '\0';  // 문자열 비우기

	while ((match = strstr(pos, oldWord)) != NULL) {
		size_t copyLen = match - pos;
		strncat(dest, pos, copyLen);  // 앞부분 복사 (길이 지정)
		strcat(dest, newWord);        // 새 단어 붙이기

		pos = match + strlen(oldWord); // oldWord 다음부터 다시 검색

		// dest가 너무 커질 위험 방지
		if (strlen(dest) > 480) break;
	}

	strcat(dest, pos); // 남은 부분 붙이기
}

int main() {
	char line[100];
	int count = 0;
	Student s[100];
	errno_t err;
	
	printf("학생 몇 명을 입력받을 건가요? : ");
	scanf_s("%d", &count);

	for (int i = 0; i < count; i++) {

		printf("\n[%d번째 학생]\n", i + 1);

		printf("학생의 이름은 무엇인가요? : \n");
		scanf_s("%s", s[i].name, (rsize_t)sizeof(s[i].name));

		printf("학생의 공격력은? : \n");
		scanf_s("%d", &s[i].atk);

		printf("학생의 방어력은? : \n");
		scanf_s("%d", &s[i].def);

		printf("학생의 체력은? : \n");
		scanf_s("%d", &s[i].hp);
		getchar(); // 숫자 입력 후 남은 개행 제거

		printf("학생의 다짐은 무엇인가요? : \n");
		fgets(s[i].comment, sizeof(s[i].comment), stdin);

		s[i].comment[strcspn(s[i].comment, "\n")] = '\0';
	}


	FILE* fp2 = NULL;
	err = fopen_s(&fp2, "students.csv", "w");
	if (err != 0 || fp2 == NULL) {
		printf(" students.csv 파일 열기 실패(쓰기): %s (errno=%d)\n", "students.csv", err);
		return 1;
	}
	printf("students.csv 테스트 파일 열기 성공\n");

	fprintf(fp2, "이름,공격력,방어력,HP,소개글\n");

	for (int i = 0; i < count; i++) {
		fprintf(fp2, "%s,%d,%d,%d,%s\n", s[i].name, s[i].atk, s[i].def, s[i].hp, s[i].comment);
	}
	fclose(fp2);



	FILE* file = NULL;
	 err = fopen_s(&file, "students.csv", "r");
	if (err != 0 || file == NULL) {
		printf("파일을 열 수 없습니다!\n");
		return -1;
	}

	count = 0; // 초기화 꼭 필요

	// 첫 줄(헤더) 건너뛰기
	fgets(line, sizeof(line), file);

	// 한 줄씩 읽기
	while (fgets(line, sizeof(line), file)) {

		line[strcspn(line, "\n")] = 0;

		char* token;
		char* next;

		token = strtok_s(line, ",", &next);
		strcpy_s(s[count].name, sizeof(s[count].name), token);

		token = strtok_s(NULL, ",", &next);
		s[count].atk = atoi(token);

		token = strtok_s(NULL, ",", &next);
		s[count].def = atoi(token);

		token = strtok_s(NULL, ",", &next);
		s[count].hp = atoi(token);

		token = strtok_s(NULL, ",", &next);
		strcpy_s(s[count].comment, sizeof(s[count].comment), token);


		count++;
	}

	fclose(file);


	FILE* fp3 = NULL;
	err = fopen_s(&fp3, "Result.txt", "w");
	if (err != 0 || fp3 == NULL) {
		printf("Result.txt 파일 열기 실패(쓰기): %s (errno=%d)\n", "Result.txt", err);
		return 1;
	}
	printf("Result.txt 테스트 파일 열기 성공\n");


	fprintf(fp3, "이름,공격력,방어력,HP,소개글\n");
	for (int i = 0; i < count; i++) {
		fprintf(fp3, "%s,%d,%d,%d,%s\n", s[i].name, s[i].atk, s[i].def, s[i].hp, s[i].comment);
	}
	fclose(fp3);
	printf("Result.txt 생성 완료!\n");

	fclose(fp3);

	// (3) 3번째 사람 한줄소개 수정 (바보 → 천재)
	char result0[300];
	replaceWord(s[0].comment, result0, "바보", "천재구나");
	//replaceWord(원본, 결과, "찾을단어", "새단어");
	printf( "1번째의 한줄소개(수정됨): %s\n", result0);

	// (4) 8번째 사람 한줄소개 수정 (바보 → 천재)
	char result1[300];
	replaceWord(s[1].comment, result1, "바보", "천재");
	printf( "2번째의 한줄소개(수정됨): %s\n", result1);



	

	
	return 0;





}
