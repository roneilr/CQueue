/** 
 * File: cqueue.c
 * --------------
 * Implementation of interface described in "cqueue.h"
 * By: Roneil Rumburg
 */


#include "cqueue.h"
#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>


/**
 * Struct used internally to represent the queue
 */
struct CQueueImplementation {
    int *data;
    int curPos; // current position in array
    int count; // number of elements currently in queue
    int capacity; // capacity defined by client
};


/**
 * Indexing helper function.
 * Takes a queue and a 0-based index into the queue and returns the address of that
 * index in the queue.
 */
static inline int *get_address(const CQueue *cq, int index) {
    assert(cq->capacity > index);

    if (cq->curPos + index < cq->capacity)
        return cq->data + cq->curPos + index;
    else return cq->data + cq->curPos + index - cq->capacity; // circle back to front
}


CQueue *CQueueCreate(int capacity) {
    assert(capacity > 0);

    CQueue *returnVal = malloc(sizeof(CQueue));
    returnVal->data = malloc(capacity*sizeof(int));
    returnVal->curPos = 0; returnVal->count = 0; returnVal->capacity = capacity;

    return returnVal;
}

void CQueueDispose(CQueue *cq) {
    free(cq->data);
    free(cq);
}

int CQueueCount(const CQueue *cq) {
    return cq->count;
}

bool CQueuePut(CQueue *cq, const int elem) {
    if(cq->count == cq->capacity)
        return false;

    int *addr = get_address(cq, cq->count++);
    *addr = elem;

    return true;
}

int CQueueGet(CQueue *cq) {
    assert(cq->count > 0);

    int *addr = get_address(cq, 0); // index 0

    if (++cq->curPos == cq->capacity) // circle back to front if needed
        cq->curPos = 0;
    cq->count--;

    return *addr;
}

int CQueuePeek(const CQueue *cq) {
    assert(cq->count > 0);

    int *addr = get_address(cq, cq->curPos);
    return *addr;
}
