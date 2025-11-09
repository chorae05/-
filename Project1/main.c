#include <stdio.h>
#include  <stdlib.h>
#include  <string.h>
#include <windows.h>
#include <conio.h>


typedef struct {
	char name[20];
	int age, number;
	double tiyou;
}Player;

#define MAX 128

int main() {
    Player player[MAX];
    int count = 0;
    char line[100];

    printf("[입력 단계] 저장할 선수 수를 입력하세요 (최대 128): ");
    scanf_s("%d", &count);

    if (count<1 || count>MAX) {
        printf("잘못입력하셨습니다.\n");

    }

    for (int i = 0; i < count; i++) {

        printf("[선수 정보 입력] %d번째 선수입니다.\n", i + 1);

        printf("이름(공백 없이): ");
        scanf_s("%s", player[i].name, (rsize_t)sizeof(player[i].name));

        printf("나이(양의 정수): ");
        scanf_s("%d", &player[i].age);

        printf("등번호(양의 정수): ");
        scanf_s("%d", &player[i].number);

        printf("타율(0.000 ~0.999, 소수3자리 권장): ");
        scanf_s("%lf", &player[i].tiyou);

    }

    FILE* file = NULL;
    errno_t err = fopen_s(&file, "players_lg.csv", "w");
    if (err != 0 || file == NULL) {
        printf("파일을 열 수 없습니다!\n");
        return -1;
    }

    fprintf(file, "이름,나이,등번호,타율\n");

    for (int i = 0; i < count; i++)
    {
        fprintf(file, "%s,%d,%d,%.3lf\n",
            player[i].name,
            player[i].age,
            player[i].number,
            player[i].tiyou);
    }

 
    fclose(file);
    printf("[저장 완료] %d명 정보를 CSV로 기록했습니다 → %s\n", count, "players_lg.csv");
    printf("엔터를 누르면 csv를 다시 읽어옵니다.\n");
    _getch();

    FILE* fp = NULL;
    fopen_s(&fp, "players_lg.csv", "r");

    if (!fp) {
        printf("파일을 열 수 없습니다!\n");
        return -1;
    }

    int loadcount = 0;
    fgets(line, sizeof(line), fp);

    while (fgets(line, sizeof(line), fp)) {

        char* t, * n;


        t = strtok_s(line, ",", &n);
        strcpy_s(player[loadcount].name, sizeof(player[loadcount].name), t);


        t = strtok_s(NULL, ",", &n);
        player[loadcount].age = atoi(t);


        t = strtok_s(NULL, ",", &n);
        player[loadcount].number = atoi(t);


        t = strtok_s(NULL, ",", &n);
        player[loadcount].tiyou = atof(t);

        loadcount++;
    }
        fclose(fp);

        Sleep(50);
        printf("[로드 / 출력 단계] CSV에서 %d명 로드됨 → 표로 출력합니다.\n", loadcount);
        printf(" --------------------------------------------------------\n");
        printf("NAME, AGE, NUMBER, TIYOU\n");
        printf(" --------------------------------------------------------\n");
        for (int i = 0; i < loadcount; i++) {
            printf("%s, %d, %d, %.3lf\n", player[i].name, player[i].age, player[i].number, player[i].tiyou);

        }
        printf(" --------------------------------------------------------\n");
        printf("출력을 모두 완료했습니다.아무 키나 누르면 종료합니다..");

        
        
   
    return 0;
}
