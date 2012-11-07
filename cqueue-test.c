/** 
 * File: cqueue-test.c
 * -------------------
 * Set of tests to verify the functionality of the CQueue
 * implementation and benchmark it.
 * By: Roneil Rumburg
 */

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "cqueue.h"

//In the stress/performance tests, this is how many integers the queue is allocated to hold.
//The current size (100 million) means that this test program requires a contiguous block of around
//400 megabytes of memory (assuming ints are 32 bit)
#define STRESS_SIZE 100000000

void verify(char *action, int shouldbe, int is, const char *function, int line, bool printSuccess) {
    if(shouldbe != is)
        printf("\nERROR on operation %s:\nShould be '%d' but is '%d'\nError encountered in %s on line %d\n", action, shouldbe, is, function, line);
    else if(printSuccess)
        printf("\nSUCCESS on operation %s:\nVerified result %d matches %d in function %s on line %d\n", action, shouldbe, is, function, line);
}

void CQueueBasicTest() {
    printf("\n-----Beginning Basic Functionality Test-----\n\n");

    CQueue *cq = CQueueCreate(10);

    for(int i=0; i<10; i++) //add ints 0-9 to queue
        verify("add element", true, CQueuePut(cq, i), __func__, __LINE__, true);

    //check that count is correct
    verify("count", 10, CQueueCount(cq), __func__, __LINE__, true);

    //check that peek is correct
    verify("peek", 0, CQueuePeek(cq), __func__, __LINE__, true);

    //add one more, exceeding capacity
    verify("add element past capacity", false, CQueuePut(cq, 100), __func__, __LINE__, true);

    for(int i=0; i<5; i++) //get first 5 elements from queue
        verify("check elements when emptying queue", i, CQueueGet(cq), __func__, __LINE__, true);

    verify("count", 5, CQueueCount(cq), __func__, __LINE__, true);

    for(int i=5; i<10; i++) //add 5 more elements, to test shifting/memmove operations
        verify("add element", true, CQueuePut(cq, i), __func__, __LINE__, true);

    //test exceeding capacity again
    verify("add element past capacity", false, CQueuePut(cq, 100), __func__, __LINE__, true);

    //empty queue now
    for(int x=0; x<2; x++)
        for(int i=5; i<10; i++)
            verify("check elements when emptying queue", i, CQueueGet(cq), __func__, __LINE__, true);

    CQueueDispose(cq);

    printf("-----End Basic Functionality Test-----\n\n");
}

void CQueueStressTest() { //stress the CQueue implementation with a massive data set (and massive shift operation
    printf("-----Begin Stress Test-----\n\n");

    CQueue *cq = CQueueCreate(STRESS_SIZE);

    //saturate CQueue with STRESS_SIZE elements
    for(int i=0; i<STRESS_SIZE; i++)
        CQueuePut(cq, i);
    verify("count", STRESS_SIZE, CQueueCount(cq), __func__, __LINE__, false);

    //empty half of queue
    for(int i=0; i<STRESS_SIZE/2; i++)
        verify("empty queue", i, CQueueGet(cq), __func__, __LINE__, false);

    //refill now empty half of queue
    for(int i=0; i<STRESS_SIZE/2; i++)
        CQueuePut(cq, i);

    //empty entire queue now, verifying everything is still intact
    for(int i=STRESS_SIZE/2; i<STRESS_SIZE; i++)
        verify("empty queue", i, CQueueGet(cq), __func__, __LINE__, false);
    for(int i=0; i<STRESS_SIZE/2; i++)
        verify("empty queue", i, CQueueGet(cq), __func__, __LINE__, false);

    CQueueDispose(cq);

    printf("-----End Stress Test-----\n\n");
}

void CQueuePerformanceTest() { //benchmark the performance of CQueue implementation
    printf("-----Begin Performance Test-----\n\n");

    printf("Tests below will be run with a size of %d for each operation.\n\n", STRESS_SIZE);

    printf("Creating queue...\n");
    CQueue *cq = CQueueCreate(STRESS_SIZE);

    printf("Fully populating queue...\n");
    for(int i=0; i<STRESS_SIZE; i++)
        CQueuePut(cq, i);

    printf("Removing all elements from queue...\n");
    for(int i=0; i<STRESS_SIZE; i++)
        CQueueGet(cq);

    printf("Adding elements to fill 50 percent of queue...\n");
    for(int i=0; i<STRESS_SIZE/2; i++)
        CQueuePut(cq, i);

    printf("Removing 50 percent of elements from queue (or 25 percent of queue capacity)...\n");
    for(int i=0; i<STRESS_SIZE/4; i++)
        CQueueGet(cq);

    printf("Fully saturating queue (again, to test memmove operation speed in add)...\n");
    for(int i=0; i<(STRESS_SIZE/4)*3; i++)
        CQueuePut(cq, i);

    printf("Removing all elements from queue...\n");
    for(int i=0; i<STRESS_SIZE; i++)
        CQueueGet(cq);

    printf("Cleaning up queue...\n\n");
    CQueueDispose(cq);

    printf("-----End Performance Test-----\n\n");
}

int main(int argc, char *argv[]) {
    if(argc == 1) { //invoked with no arguments
        CQueueBasicTest();
        CQueueStressTest();
    }
    else if(argc == 2 && strcmp(argv[1], "performance") == 0)
        CQueuePerformanceTest();
    else printf("Improper Usage.\nPlease run either '%s' or '%s performance'\n", argv[0], argv[0]);
    return 0;
}
