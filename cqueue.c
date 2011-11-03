/** 
 * File: cqueue.c
 * --------------
 * Implementation of interface described in "cqueue.h"
 * By: Roneil Rumburg
 */

#include "cqueue.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

//Define struct used internally to represent the queue
struct CQueueImplementation {
	int *data;
	int curPos; //current position in array
	int count; //number of elements currently in queue
	int capacity; //capacity defined by client
};


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
	if(cq->curPos + cq->count >= cq->capacity) {
		/* less than cq->capacity elements are in the queue, but there is no space at
		 * the end to add more things. This moves memory at the end back to the start
		 * to make space for the new element(s) being added (more efficient to do this
		 * occasionally than with every CQueueGet call) */
		memmove(cq->data, cq->data + cq->curPos, cq->count*sizeof(int));
		cq->curPos=0;
	}
	cq->data[cq->count++]=elem;
	return true;
}

int CQueueGet(CQueue *cq) {
	if(cq->count == 0) return EMPTYQUEUE;
	cq->count--;
	return cq->data[cq->curPos++];//instead of actually removing element here, advance start of queue
}

int CQueuePeek(const CQueue *cq) {
	if(cq->count == 0) return EMPTYQUEUE;
	else return cq->data[cq->curPos];
}
