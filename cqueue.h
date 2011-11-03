/** 
 * File: cqueue.h
 * --------------
 * Defines the interface for the CQueue type.
 * By: Roneil Rumburg
 */

#ifndef _cqueue_h
#define _cqueue_h

#include <stdbool.h>
#include <limits.h>

/**
 * Value: EMPTYQUEUE
 * -----------------
 * EMPTYQUEUE is the special value returned by CQueueGet and
 * CQueuePeek when called on an empty CQueue. Can also be used
 * by the client if necessary.
 */
#define EMPTYQUEUE INT_MIN

/**
 * Type: CQueue
 * ------------
 * Define the type 'CQueue' incompletely, so that items of type CQueue
 * cannot be dereferenced by the client (simulating private data).
 * 'struct CQueueImplementation' is defined in the implementation so
 * its structure is only known inside of the implementation.
 */
typedef struct CQueueImplementation CQueue;

/** 
 * Function: CQueueCreate
 * Usage: CQueue *cq = CQueueCreate(10);
 * -------------------------------------
 * Creates an empty CQueue of the given capacity and returns a pointer
 * to it. CQueueCreate uses heap memory, so the client must call CQueueDispose
 * to deallocate this memory when finished using it. Throws an assert if
 * capacity is less than or equal to 0. Operates in constant time.
 */
CQueue *CQueueCreate(int capacity);

/**
 * Function: CQueueDispose
 * Usage: CQueueDispose(cq);
 * --------------------------
 * Deallocates all of the given CQueue's memory. Operates in constant time.
 */
void CQueueDispose(CQueue *cq);

/**
 * Function: CQueueCount
 * Usage: int count = CQueueCount(cq);
 * ------------------------------------
 * Returns the number of integers currently in the given CQueue. Operates in
 * constant time.
 */
int CQueueCount(const CQueue *cq);

/**
 * Function: CQueuePut
 * Usage: bool success = CQueuePut(cq, 100);
 * -----------------------------------------
 * Adds the given integer to the end of the queue if there is space in the queue
 * (returning true), otherwise returns false to indicate that capacity is full.
 * Usually operates in constant-time, but sometimes operates in O(N) time if the
 * CQueue has already been used heavily (see readme for more information about
 * this particular case).
 */
bool CQueuePut(CQueue *cq, const int elem);

/**
 * Function: CQueueGet
 * Usage: int value = CQueueGet(cq);
 * ---------------------------------
 * Pops the first element from the queue and returns it to the client.
 * Returns EMPTYQUEUE if the given queue is empty, so the client should
 * be careful if they may add elements with the same value as EMPTYQUEUE.
 * Operates in constant time.
 */
int CQueueGet(CQueue *cq);

/**
 * Function: CQueuePeek
 * Usage: int value = CQueuePeek(cq);
 * ----------------------------------
 * Returns the first element from the queue to the client without modifying
 * the queue. Returns EMPTYQUEUE if the given queue is empty, so the client
 * should be careful if they may add elements with the same value as EMPTYQUEUE.
 * Operates in constant time.
 */
int CQueuePeek(const CQueue *cq);

#endif
