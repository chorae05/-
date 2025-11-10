#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

int main(void) {

    errno_t err;
    char line[256];

    FILE* in = NULL;
    FILE* out = NULL;


    err = fopen_s(&in, "input.txt", "r");
    if (err != 0 || in == NULL) {
        printf("input.txt 파일 열기 실패(읽기): %s (errno=%d)\n", "input.txt", err);
        return -1;
    }
    printf("input.txt 파일 열기 성공!!\n");

    err = fopen_s(&out, "output.txt", "w");
    if (err != 0 || out == NULL) {
        printf("output.txt 파일 열기 실패(쓰기): %s (errno=%d)\n", "output.txt", err);
        fclose(in);
        return -1;
    }
    printf("output.txt 파일 열기 성공!!\n");

    while (fgets(line, sizeof(line), in)) {

        char buf[128];
        strcpy(buf, line);                    

        char result[256] = "";                
        char* start = buf;                  


        for (char* q = strstr(start, "gay"); q != NULL; q = strstr(start, "gay")) {
            strncat(result, start, q - start); 
            strcat(result, "***");             
            start = q + 3;                    
        }

        strcat(result, start);                 


        fprintf(out, "%s", result);
        printf("replace 'gay'->'***': \"%s\"\n", result);
    }


    fclose(in);
    fclose(out);
    printf("변환 완료! output.txt 파일을 확인하세요.\n");

    return 0;
}
