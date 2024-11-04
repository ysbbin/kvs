#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define MAX_LEVEL 6  // Skip List의 최대 레벨을 설정합니다.

// 노드 구조체 정의
typedef struct node {
    char key[100];
    char* value;
    struct node* forward[MAX_LEVEL + 1];  // 각 레벨에 대한 포인터 배열
} node_t;

// Skip List 구조체 정의
typedef struct kvs {
    struct node* header;  // Skip List의 헤더 노드
    int level;            // Skip List의 현재 레벨
    int items;            // 저장된 데이터의 개수
} kvs_t;

// 함수 선언
kvs_t* open();                                      // Skip List 초기화
int close(kvs_t* kvs);                              // 모든 메모리 공간 해제
int put(kvs_t* kvs, const char* key, const char* value);  // 데이터 삽입, 실패 시 -1 반환
char* get(kvs_t* kvs, const char* key);             // 데이터 조회, 없으면 NULL 반환

