#include "kvs.h"

kvs_t* open() {
    // Skip List 구조체 생성
    kvs_t* kvs = (kvs_t*)malloc(sizeof(kvs_t));

    if (kvs) {
        // 헤더 노드 초기화
        kvs->header = (node_t*)malloc(sizeof(node_t));
        if (!kvs->header) {
            free(kvs);  // 헤더 노드 초기화 실패 시 kvs 메모리 해제 후 반환
            return NULL;
        }

        // 헤더 노드 초기화: key는 비워두고 모든 forward 포인터를 NULL로 설정
        kvs->header->key[0] = '\0';
        kvs->header->value = NULL;
        for (int i = 0; i <= MAX_LEVEL; i++) {
            kvs->header->forward[i] = NULL;
        }

        // Skip List 초기화
        kvs->level = 0;
        kvs->items = 0;

        printf("Open: kvs has %d items\n", kvs->items);
    }

    return kvs;
}

