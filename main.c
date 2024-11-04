#include "kvs.h"

int main() {
    // KVS (Skip List) 열기
    kvs_t* kvs = open();

    if (!kvs) {
        printf("Failed to open kvs\n");
        return -1;
    }

    // 파일 읽기 및 연산 수행
    FILE* query_file = fopen("query.dat", "r");
    FILE* answer_file = fopen("answer.dat", "w");

    if (!query_file || !answer_file) {
        printf("Failed to open query.dat or answer.dat\n");
        close(kvs);
        return -1;
    }

    char operation[10], key[100], value[100];
    while (fscanf(query_file, "%[^,],%[^,],%s\n", operation, key, value) != EOF) {
        if (strcmp(operation, "set") == 0) {
            // set 연산: key-value 쌍을 kvs에 삽입 또는 업데이트
            if (put(kvs, key, value) == -1) {
                fprintf(answer_file, "Failed to insert (%s, %s)\n", key, value);
            }
        } else if (strcmp(operation, "get") == 0) {
            // get 연산: key에 대한 값을 조회하고 answer.dat에 기록
            char* result = get(kvs, key);
            if (result) {
                fprintf(answer_file, "%s\n", result);  // 조회된 값을 기록
            } else {
                fprintf(answer_file, "-1\n");  // 키가 없을 때 -1을 기록
            }
        }
    }

    // 파일 닫기
    fclose(query_file);
    fclose(answer_file);

    // KVS (Skip List) 닫기
    close(kvs);

    return 0;
}

