#include "kvs.h"

int close(kvs_t* kvs) {
    if (!kvs) {
        return -1;  // kvs가 NULL일 경우 오류 반환
    }

    // Skip List의 모든 노드 해제
    node_t* current = kvs->header->forward[0];  // 헤더 다음 첫 번째 노드부터 시작
    while (current) {
        node_t* next = current->forward[0];  // 다음 노드를 미리 저장
        free(current->value);  // 노드의 value 메모리 해제
        free(current);  // 노드 메모리 해제
        current = next;  // 다음 노드로 이동
    }

    // 헤더 노드 해제
    free(kvs->header);

    // kvs 구조체 메모리 해제
    free(kvs);

    return 0;
}

