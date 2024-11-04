#include "kvs.h"

char* get(kvs_t* kvs, const char* key) {
    if (!kvs || !key) {
        return NULL;  // kvs나 key가 NULL인 경우 NULL 반환
    }

    // Skip List에서 key 탐색
    node_t* current = kvs->header;
    for (int i = kvs->level; i >= 0; i--) {
        while (current->forward[i] && strcmp(current->forward[i]->key, key) < 0) {
            current = current->forward[i];
        }
    }
    current = current->forward[0];  // 찾고자 하는 key 위치에 도달

    // key가 존재하는 경우 value 반환, 그렇지 않으면 NULL 반환
    if (current && strcmp(current->key, key) == 0) {
        char* value = (char*)malloc(strlen(current->value) + 1);
        if (!value) {
            printf("Failed to allocate memory for value\n");
            return NULL;
        }
        strcpy(value, current->value);
        return value;
    }

    return NULL;  // key가 존재하지 않는 경우
}

