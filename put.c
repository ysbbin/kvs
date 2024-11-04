#include "kvs.h"

int put(kvs_t* kvs, const char* key, const char* value) {
    if (!kvs || !key || !value) {
        return -1;  // NULL 매개변수가 있을 경우 실패 반환
    }

    node_t* update[MAX_LEVEL + 1];  // 삽입 위치를 추적할 포인터 배열
    node_t* current = kvs->header;

    // 삽입 위치 탐색
    for (int i = kvs->level; i >= 0; i--) {
        while (current->forward[i] && strcmp(current->forward[i]->key, key) < 0) {
            current = current->forward[i];
        }
        update[i] = current;
    }
    current = current->forward[0];  // 최종 위치 도달

    // key가 이미 존재하는 경우, value 업데이트
    if (current && strcmp(current->key, key) == 0) {
        free(current->value);  // 기존 value 메모리 해제
        current->value = (char*)malloc(strlen(value) + 1);
        if (!current->value) {
            return -1;
        }
        strcpy(current->value, value);
        return 0;
    }

    // key가 존재하지 않으면 새로운 노드 삽입
    int new_level = 0;
    while (rand() % 2 && new_level < MAX_LEVEL) {
        new_level++;
    }

    // Skip List 레벨이 증가하면 헤더 업데이트
    if (new_level > kvs->level) {
        for (int i = kvs->level + 1; i <= new_level; i++) {
            update[i] = kvs->header;
        }
        kvs->level = new_level;
    }

    // 새로운 노드 생성 및 초기화
    node_t* new_node = (node_t*)malloc(sizeof(node_t));
    if (!new_node) {
        return -1;
    }
    strcpy(new_node->key, key);
    new_node->value = (char*)malloc(strlen(value) + 1);
    if (!new_node->value) {
        free(new_node);
        return -1;
    }
    strcpy(new_node->value, value);

    // 새 노드를 각 레벨에 삽입
    for (int i = 0; i <= new_level; i++) {
        new_node->forward[i] = update[i]->forward[i];
        update[i]->forward[i] = new_node;
    }

    kvs->items++;  // 데이터 개수 증가
    return 0;
}

